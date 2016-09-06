import sys
import json
x = sys.stdin.read()
jobid=int(x.splitlines()[-1].split()[-1].split('=')[-1])
json.dump({'jobid':jobid},open(sys.argv[1],'w'))
