#!/usr/bin/make
#
# Makefile : 
#            How to build every C++ thing necessary
#
# Copyright © Noé Perard-Gayot 2020.                                                                                        #
# Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php   #
#

THREADS = 6
#$(shell nproc)

godot/bin/godot.*tools.* :
	cd godot && scons -j$(THREADS) profile=../custom.py

Godot : godot/bin/godot.*tools.*

godot: Godot

# Godot Cpp bindings
godot-cpp/bin/libgodot-cpp.*.a :
	cd godot-cpp && scons -j$(THREADS) target=debug

Godot-cpp : godot-cpp/bin/libgodot-cpp.*.a

godot-cpp : Godot-cpp

# extension
extensions/matrix/libgdmatrix.*.so :
	cd extensions/matrix && scons -j$(THREADS)

Extensions: extensions/matrix/libgdmatrix.*.so
	mkdir armory/ext/bin --parent &&\
	mv extensions/matrix/bin/libgdmatrix.*.so armory/ext/bin/ -f

extensions: Extensions

# get everything ready
all: godot extensions 

# `make launch` calls launch script
launch:
	godot/bin/godot.*.tools* armory/project.godot --editor --ups

clean:
	rm extensions/matrix/libgdmatrix.*.so || rm godot/bin/godot.*.tools*


