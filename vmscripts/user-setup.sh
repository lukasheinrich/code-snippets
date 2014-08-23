# #!/bin/zsh
# #
# # This is the bootsrap script for a new user to setup an
# # environment for physics analysis on top of a fresh
# # CernVM image: ucernvm-prod.1.18-2.cernvm.x86_64.iso (CernVM 3.3.0.6)
# # Tested on this minimal contextualization:
# # https://cernvm-online.cern.ch/context/view/261a48a9385b46dd81fc0da18a68a88d/plain
# #
#
#
# # fail immediately on any error
# set -e
#
# #### INSTALL PYTHON 2.7
# mkdir -p ~/tools && cd $HOME/tools
# curl https://www.python.org/ftp/python/2.7.8/Python-2.7.8.tgz | tar -xzvf -
# cd Python-2.7.8
# ./configure --prefix=$HOME/tools/local
# make -j4
# make install
# cd ~/tools
#
# export PATH=$HOME/tools/local/bin:$PATH
# echo 'export PATH=$HOME/tools/local/bin:$PATH' >> $HOME/env.sh
#
# #### INSTALL PIP AND CO
# wget https://bootstrap.pypa.io/get-pip.py
# $HOME/tools/local/bin/python get-pip.py
#
# $HOME/tools/local/bin/pip install IPython
#
# $HOME/tools/local/bin/pip install virtualenvwrapper
# source $HOME/tools/local/bin/virtualenvwrapper.sh
# echo 'source $HOME/tools/local/bin/virtualenvwrapper.sh' >> $HOME/env.sh
#
#
# ##PHYSICS
#
# ### Rivet HepMC and co
# mkdir -p ~/heptools && cd ~/heptools
# wget http://rivet.hepforge.org/hg/bootstrap/raw-file/2.1.2/rivet-bootstrap
# chmod +x rivet-bootstrap
# ./rivet-bootstrap
source $HOME/heptools/Rivet-2.1.2/rivetenv.sh
echo 'source $HOME/heptools/Rivet-2.1.2/rivetenv.sh' >> $HOME/env.sh

### Madgraph
bzr branch lp:~maddevelopers/mg5amcnlo/1.5.10 madgraph-1.5.10
ln -s $PWD/madgraph-1.5.10/bin/mg5 $HOME/heptools/local/bin

### Pythia
curl http://home.thep.lu.se/~torbjorn/pythia8/pythia8186.tgz|tar -xzvf -
cd pythia8186
./configure --with-hepmc=$HOME/heptools/local --with-hepmcversion=2.06.09 --prefix=$HOME/heptools/local
make -j8
make install
cd ~/heptools



export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
alias setupATLAS='source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh'

echo 'export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase' >> $HOME/env.sh
echo 'alias setupATLAS='"'"'source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh'"'" >> $HOME/env.sh