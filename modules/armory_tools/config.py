# Copyright © Noé Perard-Gayot 2021.                                                                                        #
# Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php   #

def can_build(env, platform):
    # build if using editor and have armory module
    is_editor = env["tools"]
    depend_armory = env.module_check_dependencies("armory-tools", ["armory"])
    return is_editor and depend_armory

def configure(env):
    pass


def get_doc_classes():
    return [
    #    "World",
    ]


def get_doc_path():
    return "doc_classes"
