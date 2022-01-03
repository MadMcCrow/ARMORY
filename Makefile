#!/usr/bin/make
#
# Makefile : 
#            How to build every C++ thing necessary
#
# Copyright © Noé Perard-Gayot 2020.                                                                                        #
# Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php   #
#

# save these info for later
THREADS := $(shell nproc)
BASEDIR := $(realpath $(CURDIR))

# godot/bin/godot.*tools.*
Godot :
	@cd godot && scons -j$(THREADS) profile="../custom.py" ;

godot: Godot

# get everything ready
all: godot extensions 

# `make launch` calls launch script
launch:
	@godot/bin/godot.*.tools* armory/project.godot --editor --ups;

# clean everything
clean:
	@echo "cleaning engine";\
	rm godot/bin/godot.*.tools* > /dev/null 2>&1 || true;\



