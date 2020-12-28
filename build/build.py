#!/usr/bin/env python
#
# build.py :
#               functions dedicated to building this project
#				this replaces the improper makefile that used to call scons
#
# Copyright © Noé Perard-Gayot 2020.                                                                                        #
# Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php   #
#

# color output
def _buildPrint(mode, txt) :
    from functions import color
    if "HEADER" in mode :
        color.print(color.HEADER, txt)
    if "BUILD" in mode :
        color.print(color.LESS, txt)
    if "INFO" in mode :
        color.print(color.OKBLUE, txt)
    if "ERROR" in mode :
        color.print(color.ERROR, txt)
    if "WARNING" in mode :
        color.print(color.WARNING, txt)

#
#   Strings scons might output, to be then parsed by us
#
class BuildStr:
    _init_str  = "[initial build] {init_info}"
    _def_str   = "[{percent}] {info}"
    _error_str = "{err_a} error {err_b}"
    strs = [_init_str, _def_str, _error_str]

#
#   Exception class for when things go south
#
class BuildError(Exception):
    pass


#
#  measure time
#
def _buildTime():
    time = 0
    try:
        from time import perf_counter_ns as nsec
        time = nsec() / 1e9
    finally:
        return time


def _sharedLib():
    shared_modules = ""
    try:
        from functions import getGitFolders
        from info import SOURCES_PATH
        custom_modules = SOURCES_PATH
        module_list = getGitFolders(custom_modules)
        for module in module_list:
            module_shared_var_name = '_'.join(
                ['module', module.split('/', 1)[1], 'shared'])
            shared_modules += '='.join([module_shared_var_name, "yes"]) + ' '
    except:
        pass
    finally:
        return shared_modules




#
#	generate correct build command
#
def _buildCommand(custom_path: str, shared=False, extra=""):
    buildcommand = "scons -j{threads}  profile={custom} {extra}"
    import multiprocessing
    cpu = multiprocessing.cpu_count()
    Extra = (_sharedLib() if shared else " ") + extra
    return buildcommand.format(threads=cpu, custom=custom_path, extra=Extra)


#
#	analyse output text and scan for error
#
def _parseBuildOutput(line :str):
    out = line.replace('\n', '')
    for err_str in ["error", "Error", "ERROR"] :
        if err_str in line:
            _buildPrint("ERROR", out)
            return False
    print( '\r' + out, end='\x1b[1K' )
    return True

       

    


def _runScons(cmd : str, godot_path : str ) :
    import subprocess
    import shlex
    scons = subprocess.Popen(cmd, cwd=godot_path, stdout=subprocess.PIPE, shell=True, encoding="utf-8")
    while True:
        line = scons.stdout.readline()
        if not line:
            break
        if not _parseBuildOutput(line):
            if scons != None:
                scons.terminate()
            raise BuildError
    print('\x1b[1K ') # clean terminal



#
#	build godot with custom profile
#
def build(godot_path: str, custom_path: str, shared: bool = False):
    start_time = _buildTime()
    _buildPrint("HEADER", "--- build started  ---")
    try:
      
        cmd = _buildCommand(custom_path, shared, "")
        _buildPrint("INFO", "building godot with command : \n{}".format(cmd))
        _runScons(cmd, godot_path)
    except:
        _buildPrint("ERROR" , "Failed to buid {} with {}".format(godot_path, custom_path))
        raise
    else:
        buildtime = _buildTime() - start_time
        _buildPrint("HEADER", "--- build finished in {:.3f} seconds ---".format(buildtime))
