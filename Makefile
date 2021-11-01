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

godot/bin/godot.*tools.* :
	cd godot && scons -j$(THREADS) profile=../custom.py;

Godot : godot/bin/godot.*tools.*

godot: Godot

# Godot Cpp bindings
godot-cpp/bin/libgodot-cpp.*.a :
	cd godot-cpp && scons -j$(THREADS) target=debug;
Godot-cpp : godot-cpp/bin/libgodot-cpp.*.a
godot-cpp : Godot-cpp

# extensions:
Extensions:
	mkdir armory/ext/bin --parent ;\
	for EXT in $(shell ls extensions); do \
	cd $(BASEDIR)/extensions/$${EXT} && scons -j$(THREADS) &&\
	mv $(BASEDIR)/extensions/$${EXT}/bin/libgd*.so $(BASEDIR)/armory/ext/bin/ -f;\
	done; cd $(BASEDIR);

extensions: Extensions

# get everything ready
all: godot extensions 

# `make launch` calls launch script
launch:
	godot/bin/godot.*.tools* armory/project.godot --editor --ups;

# clean everything
clean:
	@for f in $(shell ls extensions);\
	do echo "cleaning ${f}";\
	rm extensions/$${f}/bin/libgd*.so || true\
	done;\
	rm godot/bin/godot.*.tools*


