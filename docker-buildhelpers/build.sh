#!/bin/sh
#set -x
targetname=$1
buildscript=$2
resources=$3
baseimage=$4

cidfile="cidfile-$(uuidgen|tr '[:upper:]' '[:lower:]'|tr -d '-').cid"
echo "building new image"
echo "------------------"

echo $cidfile
echo $resources
echo $baseimage
echo $buildscript

docker run --cidfile $cidfile -it $resources $baseimage $buildscript
docker commit $(cat $cidfile) $targetname
rm -rf $cidfile
