#!/bin/zsh
#
# This is the bootsrap script for a new user to setup an
# environment for physics analysis on top of a fresh
# CernVM image: ucernvm-prod.1.18-2.cernvm.x86_64.iso (CernVM 3.3.0.6)
# Tested on this minimal contextualization:
# https://cernvm-online.cern.ch/context/view/261a48a9385b46dd81fc0da18a68a88d/plain
#


# fail immediately on any error
set -e

#compile with gcc48
source /opt/rh/devtoolset-2/enable
echo 'source /opt/rh/devtoolset-2/enable' >> $HOME/env.sh

#### INSTALL PYTHON 2.7
mkdir -p ~/tools && cd $HOME/tools
curl https://www.python.org/ftp/python/2.7.8/Python-2.7.8.tgz | tar -xzvf -
cd Python-2.7.8
./configure --prefix=$HOME/tools/local --enable-shared
make -j4
make install
cd ~/tools

export PATH=$HOME/tools/local/bin:$PATH
echo 'export PATH=$HOME/tools/local/bin:$PATH' >> $HOME/env.sh

export LD_LIBRARY_PATH=$HOME/tools/local/lib:$LD_LIBRARY_PATH
echo 'export LD_LIBRARY_PATH=$HOME/tools/local/lib:$LD_LIBRARY_PATH' >> $HOME/env.sh

#### INSTALL PIP AND CO
wget https://bootstrap.pypa.io/get-pip.py
$HOME/tools/local/bin/python get-pip.py

$HOME/tools/local/bin/pip install IPython
$HOME/tools/local/bin/pip install --upgrade virtualenv
$HOME/tools/local/bin/pip install virtualenvwrapper
source $HOME/tools/local/bin/virtualenvwrapper.sh
echo 'source $HOME/tools/local/bin/virtualenvwrapper.sh' >> $HOME/env.sh

#PHYSICS

export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
alias setupATLAS='source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh'

echo 'export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase' >> $HOME/env.sh
echo 'alias setupATLAS='"'"'source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh'"'" >> $HOME/env.sh

cd $HOME
