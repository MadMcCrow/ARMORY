use gdnative::prelude::*;

// equivalent to include
mod armory_tileset;
mod armory_tile;

// Function that registers all exposed classes to Godot
// register with godot
fn init(handle: InitHandle) {
    handle.add_class::<armory_tileset::ArmoryTileSet>();
    handle.add_class::<armory_tile::ArmoryTile>();
}

// Macro that creates the entry-points of the dynamic library.
godot_init!(init);
