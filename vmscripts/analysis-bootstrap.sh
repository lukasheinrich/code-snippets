#!/bin/echo "run this with source, please"
#
# This is the bootsrap script to checkout the analysis
# Tested on this minimal contextualization:
# https://cernvm-online.cern.ch/context/view/261a48a9385b46dd81fc0da18a68a88d/plain
# on top of this image: ucernvm-prod.1.18-2.cernvm.x86_64.iso (CernVM 3.3.0.6)
#

# fail immediately on any error
set -e

source env.sh

git clone https://github.com/lukasheinrich/threebody.git ~/threebody
cd ~/threebody

mkvirtualenv threebody --system-site-packages
workon threebody
HEPMCPATH=$HOME/heptools/local pip install --editable $PWD --process-dependency-links
cd workflow
./waf configure

echo "analysis is setup.. try one of these: "
echo ./waf --targets=mcviz.svg
echo "if we want to run athena do this: "
echo setupATLAS
echo asetup 18.1.0,here
echo ./waf --targets=recorun/aod.pool.root
