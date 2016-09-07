#!/bin/bash
jeditaskid=$1
export ATLAS_LOCAL_ROOT_BASE="/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase"
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh --quiet
lsetup panda --quiet
/recast_auth/getmyproxy.sh &> /dev/null
python getstatus.py $jeditaskid 2>&1 | grep PANDASTATUS|sed 's|PANDASTATUS: ||'
