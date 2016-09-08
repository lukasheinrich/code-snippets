#!/bin/sh
#set -x

tobeupdated=$1
buildscript=$2
resources=$3


cidfile="cidfile-$(uuidgen|tr '[:upper:]' '[:lower:]'|tr -d '-').cid"
echo "building new image"
echo "------------------"

echo $cidfile
echo $resources
echo $baseimage
echo $buildscript

docker run --cidfile $cidfile -it $resources $tobeupdated $buildscript
docker commit $(cat $cidfile) $tobeupdated
rm -rf $cidfile
