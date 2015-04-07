#!/bin/zsh

QUEUE=$1

source ~/env.sh
source ~/ssh_agent.sh
ssh-add 
source ~/plugin_home/venv/bin/activate

cd plugin_home/recast_plugin
source setup_analysis.sh #script to setup recast environment
celery worker -A recastbackend.productionapp:app -l info -Q $QUEUE