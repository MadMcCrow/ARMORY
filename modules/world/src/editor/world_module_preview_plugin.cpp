/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */
#if TOOLS_ENABLED

#include "editor/world_module_preview_plugin.h" // header
#include <editor/plugins/editor_preview_plugins.h>
#include <scene/resources/texture.h> // godot

#include "world_module.h"
#include "world_cell.h"

using namespace armory;

void ModulePreviewPlugin::_generate_frame_started()
{
	RS::get_singleton()->viewport_set_update_mode(viewport, RS::VIEWPORT_UPDATE_ONCE); //once used for capture
	RS::get_singleton()->request_frame_drawn_callback(callable_mp(const_cast<ModulePreviewPlugin *>(this), &ModulePreviewPlugin::_preview_done));
}

void ModulePreviewPlugin::_preview_done()
{
	preview_done.post();
}

bool ModulePreviewPlugin::handles(const String &p_type) const
{
   return ClassDB::is_parent_class(p_type, "Module");
}

Ref<Texture2D> ModulePreviewPlugin::generate(const RES &p_from, const Size2 &p_size) const
{
	String path = p_from->get_path();
	if (!FileAccess::exists(path)) {
		return Ref<Texture2D>();
	}
    return generate_from_path(path, p_size);

}

Ref<Texture2D> ModulePreviewPlugin::generate_from_path(const String &p_path, const Size2 &p_size) const
{
    RES res = ResourceLoader::load(p_path);
	Ref<Module> sampled_module;
	if (res->is_class("Module")) {
		sampled_module = res->duplicate();
	}
    else
    {
        return Ref<Texture2D>();
    }

    if (!sampled_module.is_valid())
    {
        return Ref<Texture2D>();
    }

    sampled_module->calculate_size();
	const auto mod_size = sampled_module->get_size();
    const auto mod_map  = sampled_module->get_cell_map();

    // calculate final cell size based on module size. there might be issues
    Size2 cell_size(p_size.x / mod_size.x, p_size.y / mod_size.y);

	//font->draw_string(canvas_item, pos, sample, HALIGN_LEFT, -1.f, 50, Color(1, 1, 1));

  // append all cells
    for (auto cell_itr : mod_map)
    {
        auto pos  = cell_itr.first;
        auto cell = cell_itr.second;
        if (!cell.is_valid())
        {
            continue;
        }

		if (!cell->get_cell().is_valid())
		{
			continue;
		}

        auto cell_tex = cell->get_cell()->get_tile_2d();
        if (!cell_tex.is_valid())
        {
            continue;
        }

        Rect2 draw_rect(pos, pos + cell_size);
        cell_tex->draw_rect(canvas_item, draw_rect, false);
    }

	RS::get_singleton()->connect(SNAME("frame_pre_draw"), callable_mp(const_cast<ModulePreviewPlugin *>(this), &ModulePreviewPlugin::_generate_frame_started), Vector<Variant>(), Object::CONNECT_ONESHOT);
	preview_done.wait();
	RS::get_singleton()->canvas_item_clear(canvas_item);

	Ref<Image> img = RS::get_singleton()->texture_2d_get(viewport_texture);
	ERR_FAIL_COND_V(img.is_null(), Ref<ImageTexture>());

	img->convert(Image::FORMAT_RGBA8);

	Vector2 new_size = img->get_size();
	if (new_size.x > p_size.x) {
		new_size = Vector2(p_size.x, new_size.y * p_size.x / new_size.x);
	}
	if (new_size.y > p_size.y) {
		new_size = Vector2(new_size.x * p_size.y / new_size.y, p_size.y);
	}
	img->resize(new_size.x, new_size.y, Image::INTERPOLATE_CUBIC);

	post_process_preview(img);

	Ref<ImageTexture> ptex = Ref<ImageTexture>(memnew(ImageTexture));
	ptex->create_from_image(img);

	return ptex;
}

ModulePreviewPlugin::ModulePreviewPlugin()
{
	viewport = RS::get_singleton()->viewport_create();
	RS::get_singleton()->viewport_set_update_mode(viewport, RS::VIEWPORT_UPDATE_DISABLED);
	RS::get_singleton()->viewport_set_size(viewport, 128, 128);
	RS::get_singleton()->viewport_set_active(viewport, true);
	viewport_texture = RS::get_singleton()->viewport_get_texture(viewport);

	canvas = RS::get_singleton()->canvas_create();
	canvas_item = RS::get_singleton()->canvas_item_create();

	RS::get_singleton()->viewport_attach_canvas(viewport, canvas);
	RS::get_singleton()->canvas_item_set_parent(canvas_item, canvas);
}

ModulePreviewPlugin::~ModulePreviewPlugin()
{
    RS::get_singleton()->free(canvas_item);
	RS::get_singleton()->free(canvas);
	RS::get_singleton()->free(viewport);
}

#endif // TOOLS_ENABLED
