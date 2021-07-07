/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_TILE_INSTANCE_H
#define ARMORY_TILE_INSTANCE_H

#include "scene/3d/visual_instance_3d.h"
#include "map/tile_mesh.h"
#include "map/map_core.h"
#include "static_helper.h" // add GETSET_SUPPORT

/** Armory namespace */
namespace Armory 
{

/**
 *  GridNode3D implements gridNode with 3D 
 */
class TileInstance : public GeometryInstance3D  {
    GDCLASS(TileInstance, GeometryInstance3D);

private:

	Ref<MultiMesh> multimesh;
	void update_multimesh(Ref<TileMesh> tile_mesh);

public:
	Ref<TileMesh> tile_mesh;
    GET(Ref<TileMesh>, tile_mesh)
    void set_tile_mesh(const Ref<TileMesh> &p_tile_mesh);

	static void _bind_methods();
	// bind helpers

	//TypedArray<String> get_configuration_warning() const override;

	virtual Vector<Face3> get_faces(uint32_t p_usage_flags) const override;

	virtual AABB get_aabb() const override;

	TileInstance();
	~TileInstance();

	inline Ref<MultiMesh> get_multimesh() const {return multimesh;}

};

} // namespace Armory

#endif //ARMORY_TILE_INSTANCE_H