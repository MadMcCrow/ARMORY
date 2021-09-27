#!/usr/bin/make
#
# Makefile : 
#            will call setup.py to make your life a bit easier
#
# Copyright © Noé Perard-Gayot 2020.                                                                                        #
# Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php   #
#

Godot:
	cd godot && scons -j8 platform=linuxbsd 

# `make all` builds the editor
all: Godot

# `make launch` calls launch script
launch:
	godot/bin/godot.*.tools* armory/project.godot --editor --ups
