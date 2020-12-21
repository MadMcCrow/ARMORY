#!/usr/bin/env python
#
# Config.py : 
#              allows setting project wide settings for building this project
#
# Copyright © Noé Perard-Gayot 2020.                                                                                        #
# Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php   #
#
from os import path
from functions import getPlatform

# Set project name here
#PROJECTNAME = os.path.basename(path.dirname(path.realpath(__file__)))
PROJECT_NAME = "Armory"
GODOT_PATH   = "godot"
CUSTOM_PATH  = "../Armory/build/custom.py"
PLATFORM     = getPlatform()
DESCRIPTION  = "Armory is a RTS inspired by abandonware _Arsenal : Taste The Power_"


# Storing important infos as global :
globals()["ProjectName"]  = PROJECT_NAME
globals()["Platform"]     = getPlatform()
globals()["GodotPath"]    = path.realpath(GODOT_PATH)
globals()["CustomPath"]   = path.realpath(CUSTOM_PATH)
globals()["Description"]  = DESCRIPTION