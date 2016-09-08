#!/bin/sh
echo "start docker build"
mkdir -p /code/package
echo "hello i am a fragment new" > /code/package/frag.txt
echo "done building"
cp /.dockerbuild/resources/resource.txt /code/package
