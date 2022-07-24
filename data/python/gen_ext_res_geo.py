import glob
import sys
import pathlib


res_format  = "[ext_resource type=\"ArrayMesh\" uid={} path={} id=\"{}\"]"
item_format = "item/{idx_str}/name = \"{name_str}\"\nitem/{idx_str}/mesh = ExtResource( \"{idname_str}\" )\nitem/{idx_str}/mesh_transform = Transform3D(1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0)\nitem/{idx_str}/shapes = []\nitem/{idx_str}/navmesh_transform = Transform3D(1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0)"

geo_path = sys.argv[1]
tres_path = sys.argv[2]


geo_glob = glob.glob(geo_path + '*.obj.import')

idx=0

ext_res=""
items=""

for idx in range(len(geo_glob)) :
    f = geo_glob[idx]
    uid    = ""
    path   = ""
    name   = pathlib.Path(f).stem[:-4].replace('.', '_')
    idname = str(idx) + "_" + name

    with open(f, "r") as a_file:
        for line in a_file:
            if line.startswith("uid="):
                uid = line[len("uid="):].strip()
            
            if line.startswith("source_file"):
                path = line[len("source_file="):].strip()
    
    ext_res = ext_res + "\n" + res_format.format(uid, path, idname)
    items   = items + "\n" + item_format.format(idx_str = idx, name_str = name, idname_str = idname)



text = ext_res + "\n\n[resource]\nresource_name = \"ground mesh library\"" + items


with open(tres_path, "r+") as f:
    firstline = f.readline()
    print(firstline)
    print(text)
    f.seek(0) # rewind
    f.write(firstline + text) # write the new line before