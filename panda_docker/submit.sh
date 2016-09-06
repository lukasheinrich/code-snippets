#!/bin/bash
pathena_cmd=$1
outputjson=$2
release=$3

export ATLAS_LOCAL_ROOT_BASE="/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase"
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh --quiet
lsetup asetup
lsetup panda
/recast_auth/getmyproxy.sh
asetup "$release,here"
eval $pathena_cmd 2>&1 | python /code/resources/writejobjson.py "$outputjson"
