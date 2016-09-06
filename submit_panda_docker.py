import json
import subprocess
import shlex
def submit_panda(pathena_cmd,release,workarea):
    outputfile = '{}/yadage_pathena.json'.format(workarea)
    cmd = "docker run -v {work}:{work} -w {work} -v {auth}:/recast_auth -v {cvmfs}:/cvmfs -it lukasheinrich/panda_helper /code/resources/submit.sh '{command}' {outputjson} {release}"
    filled = cmd.format(
        work = workarea,
        auth = '/home/recast/recast_auth',
        cvmfs = '/cvmfs',
        command = pathena_cmd,
        outputjson = outputfile,
        release = release
    )
    print 'running full docker command: {}'.format(filled)
    subprocess.check_call(shlex.split(filled))
    return json.load(open(outputfile))
