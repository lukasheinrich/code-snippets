import json
import cap
import adage
import foradage
from foradage import runNode
  
def single_node_from_context(workflow,step,dag,context,nodename):
  stepspec = cap.load_spec(step['spec'])
  
  
  node = {
    'name':nodename,
    'attributes': {k:v.format(**context) for k,v in step['attributes'].iteritems()},
    'spec':stepspec['definition']['node_spec']
  }

  node = adage.mknode(dag,task = runNode.s(node,context), nodename = nodename)
  step['scheduled_nodes'] = [node]
  
def map_from_dep_output(workflow,step,dag,context,nodename_template,dependency,outputkey,to_input,to_output,output_template):
  stepspec = cap.load_spec(step['spec'])

  dep = [x for x in workflow if x['name'] == dependency][0]

  step['scheduled_nodes'] = []
  index = 0
  for x in dep['scheduled_nodes']:
    rcmeta = x.result_of()['RECAST_metadata']
    for this_index,y in enumerate(rcmeta['outputs'][outputkey]):
      copy = context.copy()
      copy.update(index = index)
      
      attr = {}
      attr[to_input] = y
      attr[to_output] = output_template.format(**copy)
      
      used_inputs = {x.task.node['name'] :[(outputkey,this_index)]}
      
      node = {
        'name': nodename_template.format(**copy),
        'attributes': attr,
        'spec':stepspec['definition']['node_spec'],
        'used_inputs':used_inputs
      }
      
      nodeobj = adage.mknode(dag,task = runNode.s(node,context), nodename = node['name'])
      dag.addEdge(x,nodeobj)
      step['scheduled_nodes'] += [nodeobj]
      index += 1

def reduce_from_dep_output(workflow,step,dag,context,nodename,dependency,outputkey,to_input):
  stepspec = cap.load_spec(step['spec'])
  dep = [x for x in workflow if x['name'] == dependency][0]
  step['scheduled_nodes'] = []

  new_inputs = []
  used_inputs = {}
  index = 0
  for x in dep['scheduled_nodes']:
    used_inputs[x.task.node['name']] = []
    for i,y in enumerate(x.result_of()['RECAST_metadata']['outputs'][outputkey]):
      new_inputs += [y]
      used_inputs[x.task.node['name']] += [(outputkey,i)]

  print 'to_input : {} new input: {}'.format(to_input,new_inputs)

  attributes = {k:v.format(**context) for k,v in step['attributes'].iteritems()}
  attributes[to_input] = new_inputs

  node = {
    'name':nodename,
    'attributes':attributes,
    'spec':stepspec['definition']['node_spec'],
    'used_inputs':used_inputs
  }
  
  node = adage.mknode(dag,runNode.s(node,context), nodename = nodename)
  step['scheduled_nodes'] = [node]
  for x in dep['scheduled_nodes']:
    dag.addEdge(x,node)
