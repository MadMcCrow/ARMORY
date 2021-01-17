/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// Godot
#include "core/io/resource_saver.h"
#include "core/os/file_access.h"
#include "editor/import/scene_importer_mesh.h"
#include "editor/import/scene_importer_mesh_node_3d.h"
#include "scene/3d/mesh_instance_3d.h"
#include "scene/3d/node_3d.h"
#include "scene/resources/mesh.h"
#include "scene/resources/surface_tool.h"

// Armory
#include "editor/resource_importer_tile_mesh.h"
#include "map/tile_mesh.h"

// we use Armory here
using namespace Armory;

String ResourceImporterTileMesh::TileGeometryOption = "TileType";

String ResourceImporterTileMesh::get_importer_name() const
{
	return "wavefront_obj_tile_mesh";
}

String ResourceImporterTileMesh::get_visible_name() const
{
	return "ARMORY : OBJ As Tile Mesh";
}

void ResourceImporterTileMesh::get_recognized_extensions(List<String> *p_extensions) const
{
	p_extensions->push_back("obj");
}

String ResourceImporterTileMesh::get_save_extension() const
{
	return "tilemesh";
}

String ResourceImporterTileMesh::get_resource_type() const
{
	return "TileMesh";
}

int ResourceImporterTileMesh::get_format_version() const
{
	return 1;
}

int ResourceImporterTileMesh::get_preset_count() const
{
	return 0;
}

String ResourceImporterTileMesh::get_preset_name(int p_idx) const
{
	return "";
}

void ResourceImporterTileMesh::get_import_options(List<ImportOption> *r_options, int p_preset) const
{
	ResourceImporterOBJ::get_import_options(r_options, p_preset);
	r_options->push_back(ImportOption(PropertyInfo(Variant::INT, TileGeometryOption, PROPERTY_HINT_ENUM, "flat,straight,cross,angle_convex,angle_concave,T_convex,T_concave,all_sides"), 0));
}

bool ResourceImporterTileMesh::get_option_visibility(const String &p_option, const Map<StringName, Variant> &p_options) const
{
	return true;
}

Error ResourceImporterTileMesh::import(const String &p_source_file, const String &p_save_path, const Map<StringName, Variant> &p_options, List<String> *r_platform_variants, List<String> *r_gen_files, Variant *r_metadata)
{
	// import obj as always
	Error err = ResourceImporterOBJ::import(p_source_file, p_save_path, p_options, r_platform_variants, r_gen_files, r_metadata);
	// get info on waht was imported
	String save_path = r_gen_files->back()->get();
	print_msg(this, save_path);
	Ref<ArrayMesh> res = ResourceLoader::load(save_path);
	Ref<TileMesh> mesh = TileMesh::from_mesh(res);
	// rebuild savepath
	save_path = p_save_path + "." + get_save_extension();
	// save new asset
	err = ResourceSaver::save(save_path, mesh);
	ERR_FAIL_COND_V_MSG(err != OK, err, "Cannot save Mesh to file '" + save_path + "'.");
	return OK;
}

ResourceImporterTileMesh::ResourceImporterTileMesh()
{
}
