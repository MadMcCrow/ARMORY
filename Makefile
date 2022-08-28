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

# todo : make this work
# clean and rebuild everything
#_upgrade:
#	@echo "update engine";\
#   $(MAKE) clean;\
#   cd godot-cpp && git pull --rebase ; \
# 	cd godot && git pull --rebase ; \
#	$(MAKE) all;\

# godot editor : we don't need to rebuild it all the times
godot/bin/godot.*.tools.* :
	@cd godot && scons -j$(THREADS) profile="../build/custom.py" ;
godot: godot/bin/godot.*.tools.*

# GDextension bindings
godot-cpp/bin/libgodot-cpp.*.a :
	@cd godot-cpp && scons -j$(THREADS) target=debug ;
godot-cpp: godot-cpp/bin/libgodot-cpp.*.a

# Build our ARMORY modules 
Extensions: godot-cpp
	@rm armory/bin/* ; cd extensions && scons -j$(THREADS);
extensions: Extensions

# `make launch` calls launch script
# TODO : create a separate launcher 
launch:
	@cd armory && ../godot/bin/godot.*  --debug ;
editor:
	@godot/bin/godot.*  ./armory/project.godot ;

# clean everything
clean:
	@echo "cleaning engine";\
	rm godot/bin/* > /dev/null 2>&1 || true;\
	rm godot-cpp/bin/* > /dev/null 2>&1 || true;\

# Get everything ready
all: godot godot-cpp extensions


