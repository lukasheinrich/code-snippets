from fabric.api import env
from fabric.operations import run, put
from fabric.tasks import execute

env.hosts = ['nyu']
env.use_ssh_config = True

def copy():
    run('mkdir -p ~/fromfabric')
    put('./zenodo_testfile.txt','~/fromfabric')
    
execute(copy,hosts = ['nyu'])