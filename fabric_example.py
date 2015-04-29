import fabric
from fabric.api import env
from fabric.operations import run, put

env.hosts = ['nyu']
env.use_ssh_config = True

def copy():
    run('mkdir -p ~/fromfabric')
    put('./zenodo_testfile.txt','~/fromfabric')
    
from fabric.tasks import execute
execute(copy,hosts = ['nyu'])