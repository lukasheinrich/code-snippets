import json
import yaml
import glob

for x in  glob.glob("*.yaml"):
  with open(x) as f:
    with open(x.replace('.yaml','.json'),'w') as out:
      json.dump(yaml.load(f),out,sort_keys=True,indent=2, separators=(',', ': '))