import cap
import importlib
import subprocess
import adage.backends


class RECAST_Task(object):
  def __init__(self,func):
    self.func = func
    self.node = None
    self.context = None

  def __repr__(self):
    return '<RECAST name: {}>'.format(self.node['name'])

  def __call__(self):
    return self.func(self.node,self.context)
  
  def set(self,node,context):
    self.node = node
    self.context = context

def RCST(func):
  def sig(*args,**kwargs):
    instance = RECAST_Task(func)
    instance.set(*args,**kwargs)
    return instance
  func.s = sig
  return func

class RECAST_Rule(object):
  def __init__(self,stepinfo,workflow,allrules,global_context):
    self.stepinfo = stepinfo
    self.global_context = global_context
    self.workflow = workflow
    self.allrules = allrules

  def applicable(self,dag):
    depstats = []
    for x in self.stepinfo['dependencies']:
      deprule = self.allrules[x]
      if not 'scheduled_nodes' in deprule.stepinfo:
        depstats += [False]
      else:
        depstats += [all([x.successful() for x in deprule.stepinfo['scheduled_nodes']])]
    
    return all(depstats)

  def apply(self,dag):
    self.schedule(dag)

  def schedule(self,dag):
    sched = self.stepinfo['scheduler']
    modulename,funcname = sched['name'].split(':')
    mod = importlib.import_module(modulename)
    func = getattr(mod,funcname)
    args = sched['args']
    kwargs = sched['kwargs']
    func(self.workflow,self.stepinfo,dag,self.global_context,*args,**kwargs)
    
class RECAST_Result(object):
  def __init__(self,resultobj,task):
    self.resultobj = resultobj
    self.task = task
    self.result = None
    
  def ready(self):
    return self.resultobj.ready()
  def successful(self):
    return self.resultobj.successful()
  def get(self):
    if self.result:
      return self.result
    result = {
      'RECAST_metadata':{
        'outputs':self.publish(self.task.node)
      },
      'taskresult':self.resultobj.get()
    }
    self.result = result
    return self.result

  def publish(self,node):
    spec = cap.load_spec(node['spec'])
    publ = spec['publisher']
    modulename,funcname = publ['name'].split(':')
    mod = importlib.import_module(modulename)
    func = getattr(mod,funcname)
    args = publ['args']
    kwargs = publ['kwargs']
    return func(node,*args,**kwargs)
  

class RECAST_Backend(adage.backends.MultiProcBackend):
  def submit(self,task):
    return RECAST_Result(super(RECAST_Backend,self).submit(task),task)

  def ready(self,result):
    ready =  super(RECAST_Backend,self).ready(result)
    return ready
    
  def result_of(self,result):
    return result.get()

def build_command(node):
  attr = node['attributes']
  spec = cap.load_spec(node['spec'])
  cmd  =  spec['definition']['name']
  args = [ attr[a['name']] for a in spec['definition']['arguments']]
  args = ' '.join([ ' '.join(a) if type(a)==list else a for a in args])
  command = '{cmd} {args}'.format(cmd = cmd, args = args)
  return command

@RCST
def runNode(json,global_context):
  command = build_command(json)
  spec = cap.load_spec(json['spec'])
  environment = spec['environment']['definition']
  
  container = environment['docker_container']
  
  report = '''--------------
run in docker container: {container}
with env: {env}
command: {command}
--------------
'''.format( container = container,
            command = command,
            env = environment['env'] if environment['env'] else 'default env'
          )
  
  in_docker_cmd = 'echo {command}'.format(command = command)
  
  print report
  try:
    subprocess.check_call('docker run -v {0}:/workdir ubuntu sh -c \'echo {1} && echo $(hostname) > /workdir/{1}.hostname && {in_docker_cmd}\'  '.format(global_context['workdir'],json['name'],in_docker_cmd = in_docker_cmd), shell = True)
    subprocess.check_call('docker rm $(cat {0}/{1}.hostname)'.format(global_context['workdir'],json['name']), shell = True)
  except subprocess.CalledProcessError:
    print 'subprocess failed'
    raise RuntimeError
  