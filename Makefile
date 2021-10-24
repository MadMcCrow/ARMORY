#!/usr/bin/make
#
# Makefile : 
#            try to build everything
#
# Copyright © Noé Perard-Gayot 2020.                                                                                        #
# Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php   #
#


godot/bin/godot.*tools.* :
	cd godot && scons -j4 profile=../custom.py

extensions/matrix/libgdmatrix.*.so :
	cd extensions/matrix && scons -j4

Godot : godot/bin/godot.*tools.*

# copy extension
Extensions: extensions/matrix/libgdmatrix.*.so
	mv extensions/matrix/bin/libgdmatrix.*.so armory/ext/bin/ -f

# get everything ready
all: Godot Extensions

# `make launch` calls launch script
launch:
	godot/bin/godot.*.tools* armory/project.godot --editor --ups

clean:
	rm extensions/matrix/libgdmatrix.*.so || rm godot/bin/godot.*.tools*


