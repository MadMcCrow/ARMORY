#!/usr/bin/env python
#
# blender_export.py :
#                       helper to export every blender file into obj
#
# Copyright © Noé Perard-Gayot 2020.                                                                                        #
# Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php   #
#

import bpy
from os import path
from os import makedirs

def check_folder_export(exportFolder : str) ->str :
    folder = path.realpath(path.join( bpy.path.abspath("//"), exportFolder))
    try:
        print(folder)
        makedirs(folder)
    except OSError as e:
        if e.errno != errno.EEXIST:
            raise
    finally:
        return folder

def export_all_obj(exportFolder):
    ''' 
    xport every object in scene to obj
    '''
    folder = check_folder_export(exportFolder)
    objects = bpy.data.objects
    for object in objects:
        bpy.ops.object.select_all(action='DESELECT')
        object.select_set(state=True)
        print("exporting {} to obj".format(object.name))
        exportName = path.join(folder, object.name + '.obj')
        bpy.ops.export_scene.obj(   filepath=exportName, check_existing=False,
                                    axis_forward='-Z', axis_up='Y',
                                    filter_glob="*.obj;*.mtl",
                                    use_selection=True,
                                    use_animation=False,
                                    use_mesh_modifiers=True,
                                    use_edges=True, use_smooth_groups=False,
                                    use_smooth_groups_bitflags=False,
                                    use_normals=True,
                                    use_uvs=True,
                                    use_materials=True,
                                    use_triangles=False,
                                    use_nurbs=False,
                                    use_vertex_groups=False,
                                    use_blen_objects=True, 
                                    group_by_object=False,
                                    group_by_material=False,
                                    keep_vertex_order=False,
                                    global_scale=1.0, path_mode='AUTO')


export_all_obj("../obj")