#!/bin/zsh
#
# This is the bootsrap script for the root user to setup an
# environment for physics analysis on top of a fresh
# CernVM image: ucernvm-prod.1.18-2.cernvm.x86_64.iso (CernVM 3.3.0.6)
# Tested on this minimal contextualization:
# https://cernvm-online.cern.ch/context/view/261a48a9385b46dd81fc0da18a68a88d/plain
#

# fail immediately on any error
set -e

# we will assume the user already exists
# useradd ciserver
# passwd ciserver
# visudo #(add ciserver to sudoers, optional)


echo CVMFS_REPOSITORIES=atlas.cern.ch,atlas-condb.cern.ch,sft.cern.ch >> /etc/cvmfs/default.local
echo CVMFS_CACHE_BASE=/var/cache/cvmfs >> /etc/cvmfs/default.local
echo CVMFS_QUOTA_LIMIT=10000 >> /etc/cvmfs/default.local
#comment following out if we are outside of cern and cannot reach ca-proxy.cern.ch
#echo CVMFS_HTTP_PROXY="http://ca-proxy.cern.ch:3128" >> /etc/cvmfs/default.local

cvmfs_config reload
cvmfs_config chksetup

mkdir -p /var/cache/cvmfs
mkdir -p /var/cache/cvmfs/shared

mkdir -p /afs
/sbin/chkconfig afs on
/sbin/service afs start

yum --assumeyes install bzr