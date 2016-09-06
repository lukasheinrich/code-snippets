def submit_to_grid(pathena_cmd):
    import subprocess
    import shlex
    out = subprocess.Popen(shlex.split(pathena_cmd),stdout = subprocess.PIPE, stderr = subprocess.PIPE).communicate()
    jobid=int(out[1].splitlines()[-1].split()[-1].split('=')[-1])
    print 'created new task with id: {}'.format(jobid)
    return jobid

def get_status(grid_jobid):
    import pandatools.Client
    out = pandatools.Client.getJediTaskDetails({'jediTaskID':grid_jobid},True,True,True)
    return out[1]['status']

def blocking_grid(pathena_cmd,firstinterval = 60, checkinterval = 60):
    import time
    taskid = submit_to_grid(pathena_cmd)
    time.sleep(firstinterval)
    terminal_states = ['done','failed','broken']
    while True:
        time.sleep(checkinterval)
        status = get_status(taskid)
        print 'status of task {} is: {}'.format(taskid,status)
        if status in terminal_states:
            print 'terminal state reached. breaking'
            break

def main():
    import sys
    cmd = sys.argv[1]
    blocking_grid(cmd)

if __name__ == '__main__':
    main()
