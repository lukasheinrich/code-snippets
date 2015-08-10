#!/bin/zsh
set -e

PLUGINHOMEDIR=$1

source ~/env.sh
source ~/ssh_agent.sh

kill $SSH_AGENT_PID || echo 'could not find ssh agent process to kill, continue..'

source ~/"$PLUGINHOMEDIR/venv/bin/activate"

cd "$PLUGINHOMEDIR"/recast_plugin
source setup_analysis.sh #script to setup recast environment

echo "killing celery process $(cat celery.pid)"
#send SIGQUIT to celery top worker process
(cat celery.pid | xargs kill -3)
