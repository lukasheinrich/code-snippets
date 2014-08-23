#!/bin/echo "run this with source, please"
#
# This is the bootsrap script to checkout the analysis
# Tested on this minimal contextualization:
# https://cernvm-online.cern.ch/context/view/261a48a9385b46dd81fc0da18a68a88d/plain
# on top of this image: ucernvm-prod.1.18-2.cernvm.x86_64.iso (CernVM 3.3.0.6)
#

# fail immediately on any error
(source env.sh                                                                                 )|| return

(git clone https://github.com/lukasheinrich/threebody.git ~/threebody                          )|| return
(cd ~/threebody                                                                                )|| return

(mkvirtualenv threebody --system-site-packages                                                 )|| return
(workon threebody                                                                              )|| return
(HEPMCPATH=$HOME/heptools/local pip install --editable $PWD --process-dependency-links         )|| return
(cd workflow                                                                                   )|| return
(./waf configure                                                                               )|| return

(echo "analysis is setup.. try one of these: "                                                 )|| return
(echo ./waf --targets=mcviz.svg                                                                )|| return
(echo "if we want to run athena do this: "                                                     )|| return
(echo setupATLAS                                                                               )|| return
(echo asetup 18.1.0,here                                                                       )|| return
(echo ./waf --targets=recorun/aod.pool.root                                                    )|| return