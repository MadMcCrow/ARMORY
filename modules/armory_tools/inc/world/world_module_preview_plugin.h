/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_WORLD_MODULE_PREVIEW_PLUGIN_CLASS_H
#define ARMORY_WORLD_MODULE_PREVIEW_PLUGIN_CLASS_H
// godot class
#include <scene/main/node.h>


namespace armory
{

class WorldModulePreviewPlugin : public EditorResourcePreviewGenerator {
	GDCLASS(WorldModulePreviewPlugin, EditorResourcePreviewGenerator);

	RID viewport;
	RID viewport_texture;
	RID canvas;
	RID canvas_item;
	Semaphore preview_done;

	void _generate_frame_started();
	void _preview_done();

public:
	virtual bool handles(const String &p_type) const override;
	virtual Ref<Texture2D> generate(const RES &p_from, const Size2 &p_size) const override;
	virtual Ref<Texture2D> generate_from_path(const String &p_path, const Size2 &p_size) const override;


	WorldModulePreviewPlugin();
	~WorldModulePreviewPlugin();
};
};

#endif // ARMORY_WORLD_MODULE_PREVIEW_PLUGIN_CLASS_H