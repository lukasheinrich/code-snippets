def submit_to_grid(pathena_cmd):
    import subprocess
    import shlex
    out = subprocess.Popen(shlex.split(pathena_cmd),stdout = subprocess.PIPE, stderr = subprocess.PIPE).communicate()
    jobid=int(out[1].splitlines()[-1].split()[-1].split('=')[-1])
    return jobid

def get_status(grid_jobid):
    import pandatools.Client
    out = pandatools.Client.getJediTaskDetails({'jediTaskID':grid_jobid},True,True,True)
    return out[1]['status']
