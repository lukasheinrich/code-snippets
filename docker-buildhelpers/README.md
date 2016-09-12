
    ./build.sh lukasheinrich/newimage /.dockerbuild/buildinput/build.sh "-v $PWD/buildscripts:/.dockerbuild/buildinput -v $PWD/buildresources:/.dockerbuild/resources" busybox
    ./update.sh lukasheinrich/newimage /.dockerbuild/buildinput/update.sh "-v $PWD/buildscripts:/.dockerbuild/buildinput -v $PWD/buildresources:/.dockerbuild/resources"
