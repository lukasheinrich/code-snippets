import sys
taskid = sys.argv[1]
def get_status(grid_jobid):
    import pandatools.Client
    out = pandatools.Client.getJediTaskDetails({'jediTaskID':grid_jobid},True,True,True)
    return out[1]['status']
import json
sys.stdout.write('PANDASTATUS: {0}'.format(json.dumps({'status':get_status(taskid)})))
