/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "map/tile_collection.h"
#include "core/core_bind.h"
using namespace Armory;



const TileMesh * TileCollection::get_tile(int index) const 
{
    if (index >= tileset.size()) 
        return nullptr;
    
    Variant element = tileset[index];
    if(element.is_ref())
    {
        Object *reference = static_cast<Object *>(element);
        return Cast<TileMesh>(reference);
    }

    return Cast<TileMesh>(element.get_validated_object());

}

void TileCollection::_bind_methods()
{
    
    BIND_PROPERTY_GETSET(TileCollection, Variant::ARRAY, tileset, PROPERTY_HINT_ARRAY_TYPE, "TileMesh" );
    #ifdef TOOLS_ENABLED
    BIND_PROPERTY_GETSET(TileCollection, Variant::OBJECT, import_tile, PROPERTY_HINT_RESOURCE_TYPE, "TileMesh" );
    #endif //TOOLS_ENABLED
}

#ifdef TOOLS_ENABLED
void TileCollection::set_import_tile(const Ref<TileMesh> &p_import_tile)
{
    tileset.push_back(p_import_tile);
    set_tileset(tileset); // make sure to update
}
#endif //TOOLS_ENABLED