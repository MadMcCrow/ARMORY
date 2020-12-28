#!/usr/bin/env python
#
# Setup.py :
#               Setup this project according to platform
#				this replaces the improper makefile that used to call scons
#
# Copyright © Noé Perard-Gayot 2020.                                                                                        #
# Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php   #
#


#
#   Desktop file generation
#	This creates a shortcut for linux users
#
def generateDesktopFile(path):
    text = "[Desktop Entry]\nName={Name}\nComment={Comment}\nExec={bin} {args}\nIcon={icon}\nTerminal={bterm}\nType=Application"
    # find binary
    bin_path = str()
    project_path = str()
    icon_path = str()
    try:
        from functions import findFiles
        from functions import findFilesList
        bin_path = findFilesList(
            _godotPath() + "/bin", [str(_projectName()).lower(), ".tools.", "bin"])[0]
        project_path = findFiles(str(_projectName()), ".godot")[0]
        icon_path = findFiles(str(_projectName()), "icon")[0]
    except:
        raise
    # create desktop file
    try:
        # \see import config
        arguments = "${path_to_project} --editor --upwards".format(
            path_to_project=project_path)
        d = text.format(Name=_projectName(), Comment=_description(),
                        bin=bin_path, args=arguments, icon=icon_path, bterm="true")

        d_file = open(path, "w")
        d_file.writelines(d)
        d_file.close()
    except:
        raise


#
#	remove unnecesary files
#
def clean():
    pass


#
#	print help info
#	TODO : automate this
#
def _help():
    pass


#
#	will create a shortcut to the editor
#
def shortcut():
    try:
        from os import getcwd
        from functions import isLinux
        if isLinux():
            generateDesktopFile(getcwd() + "/" + _projectName() + ".desktop")
        else:
            raise NotImplementedError
    except:
        raise

#
#	handle command line argument
#
def arg_condition(arg: str, arg_list: list) -> bool:
    return arg in arg_list


#
#	Main setup function
#
def main():
    import sys
    for arg in sys.argv:
        if arg_condition(arg, ["--help", "-h", "h", "help"]):
            _help()
            return

        if arg_condition(arg, ["--build", "-b", "-b", "build"]):
            from build import build
            build()

        if arg_condition(arg, ["--shortcut", "-s", "s", "shortcut"]):
            shortcut()


# Run setup program
if __name__ == "__main__":
    main()
