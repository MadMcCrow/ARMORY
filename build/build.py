#!/usr/bin/env python
#
# build.py :
#               functions dedicated to building this project
#				this replaces the improper makefile that used to call scons
#
# Copyright © Noé Perard-Gayot 2020.                                                                                        #
# Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php   #
#

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


def buildPrint(text: str):
    print(bcolors.WARNING + text + bcolors.ENDC)


def buildTime():
    time = 0
    try:
        from time import perf_counter_ns as nsec
        time = nsec() / 1000.0
    finally:
        return time


def sharedLib():
    shared_modules = ""
    try:
        from functions import getGitFolders
        from info      import SOURCES_PATH
        custom_modules = SOURCES_PATH
        print(custom_modules)
        module_list = getGitFolders(custom_modules)
        for module in module_list:
            module_shared_var_name = '_'.join(
                ['module', module.split('/', 1)[1], 'shared'])
            shared_modules += '='.join([module_shared_var_name, "yes"]) + ' '
    except:
        pass
    finally:
        return shared_modules


def buildCommand(custom_path : str , shared=False, extra=""):
    buildcommand = "scons -j{threads}  profile={custom} {extra}"
    import multiprocessing
    cpu = multiprocessing.cpu_count()
    Extra = (sharedLib() if shared else " ") + extra
    return buildcommand.format(threads=cpu, custom=custom_path, extra=Extra)

#
#	build godot with custom profile
#


def build(godot_path : str, custom_path : str, shared: bool = False):
    start_time = buildTime()
    print("--- build started at {} ---".format(start_time))
    try:
        import subprocess
        import shlex
        cmd = buildCommand(custom_path, shared, "")
        print("building godot with command : \n{}".format(cmd))
        rc = subprocess.run(shlex.split(cmd), cwd=godot_path, shell=True, encoding="utf-8")
        # while True:
        #	line = rc.stdout.readline()
        #	if "error" in str(line) :
        #		print("{}"str(line))
        #		rc.terminate()
        #	if not line: break
    except:
        print("Failed to buid {} with {}".format(godot_path, custom_path))
        # if rc != None:
        #    rc.terminate()
        raise
    else:
        buildtime = buildTime() - start_time
        print("--- build finished in {} seconds ---".format(buildtime))
