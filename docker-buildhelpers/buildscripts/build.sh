#!/bin/sh
echo "start docker build"
mkdir -p /code/package
echo "hello i am a fragment new" > /code/package/frag.txt
echo "done building"
cp /.dockerbuild/resources/resource.txt /code/package

while true; do
    read -p "Do you wish to install this program?" yn
    case $yn in
        [Yy]* ) echo "great!"; break;;
        [Nn]* ) exit;;
        * ) echo "Please answer yes or no.";;
    esac
done

