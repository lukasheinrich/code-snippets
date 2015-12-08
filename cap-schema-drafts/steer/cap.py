import json
def load_spec(spec):
  with open('capdata/{}.json'.format(spec)) as f:
    return json.load(f)