# Copyright © Noé Perard-Gayot 2021.                                                                                        #
# Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php   #

def can_build(env, platform):
    return  True

def configure(env):
    pass


def get_doc_classes():
    base_classes = [
        "World",
        "Cell",
        "Module",
    ]
    editor_classes = [
        "ModulePreviewPlugin"
    ]
    return base_classes


def get_doc_path():
    return "doc_classes"
