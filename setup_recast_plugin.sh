#!/bin/zsh

set -e

GITREPO=$1

mkdir plugin_home
cd plugin_home

source ~/env.sh

virtualenv venv
source venv/bin/activate

pip install https://github.com/recast-hep/recast-backend/zipball/master --process-dependency-links
git clone $GITREPO recast_plugin
cd recast_plugin
./mk_analysis.sh #one-time installation (compilation of code etc)
pip install -e . --process-dependency-links