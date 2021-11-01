#! /usr/bin/sh
# get all submodules :
git submodule update --init --recursive # update/get the godot
# build godot
cd godot
scons -j profile=/custom.py
# build godot-cpp
cd ../godot-cpp
scons -j target=debug
# build extensions
cd ../extensions/matrix
scons -j target=debug

