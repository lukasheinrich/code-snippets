class StepBase(object):
  def __inif__(self):
    self.dependencies = []
    self.attributes = []
    self.scheduler = None
    self.spec = None

class SingleNodeStep(StepBase):
  """a step that only schedules a single type of node"""
  schema = 'single_node_step'
  @classmethod
  def fromYaml(cls,yaml):
    s = cls()
    assert(yaml['schema'] == cls.schema)
    definition = yaml['definition']
    self.node_spec = definition['node_spec']