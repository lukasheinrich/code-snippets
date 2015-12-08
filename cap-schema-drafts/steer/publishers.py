def list_from_attribute_file(node_instance,attribute,outputname):
  outputs = {}
  with open(node_instance['attributes'][attribute]) as f:
    outputs[outputname] = [x.strip() for x in f.readlines() if x.strip()]
  return outputs
    
def from_attributes(node_instance,**kwargs):
  outputs = {}
  for k,v in kwargs.iteritems():
    outputs[k] = [node_instance['attributes'][v]]
  return outputs