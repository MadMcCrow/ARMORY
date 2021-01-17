/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */


#ifndef ARMORY_RESOURCE_IMPORTER_TILE_MESH_H
#define ARMORY_RESOURCE_IMPORTER_TILE_MESH_H

#ifdef TOOLS_ENABLED
#include "editor/import/resource_importer_obj.h"
#include "core/templates/map.h"

namespace Armory
{
class ResourceImporterTileMesh : public ResourceImporterOBJ {
	GDCLASS(ResourceImporterTileMesh, ResourceImporterOBJ);

public:

	static String TileGeometryOption;

	virtual String get_importer_name() const override;
	virtual String get_visible_name() const override;
	virtual void get_recognized_extensions(List<String> *p_extensions) const override;
	virtual String get_save_extension() const override;
	virtual String get_resource_type() const override;
	virtual int get_format_version() const override;

	virtual int get_preset_count() const override;
	virtual String get_preset_name(int p_idx) const override;

	virtual void get_import_options(List<ImportOption> *r_options, int p_preset = 0) const override;
	virtual bool get_option_visibility(const String &p_option, const Map<StringName, Variant> &p_options) const override;

	virtual Error import(const String &p_source_file, const String &p_save_path, const Map<StringName, Variant> &p_options, List<String> *r_platform_variants, List<String> *r_gen_files = nullptr, Variant *r_metadata = nullptr) override;

	ResourceImporterTileMesh();
};
} //namespace Armory

#endif // TOOLS_ENABLED
#endif // ARMORY_RESOURCE_IMPORTER_TILE_MESH_H
