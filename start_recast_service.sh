#!/bin/zsh

set -e

PLUGINHOMEDIR=$1

QUEUE=$2

source ~/env.sh

ssh-agent > ssh_agent.sh
source ~/ssh_agent.sh
ssh-add 

source ~/"$PLUGINHOMEDIR/venv/bin/activate"

cd "$PLUGINHOMEDIR"/recast_plugin
source setup_analysis.sh #script to setup recast environment
celery worker -A recastbackend.productionapp:app -l debug -Q $QUEUE --detach --logfile celery.log --pidfile celery.pid
