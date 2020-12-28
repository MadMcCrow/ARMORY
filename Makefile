#!/usr/bin/make
#
# Makefile : 
#            will call setup.py to make your life a bit easier
#
# Copyright © Noé Perard-Gayot 2020.                                                                                        #
# Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php   #
#

# `make all` builds the editor
all:
	@python ./build/setup.py --build

# `make launch` calls launch script
launch:
	@./launch.sh
