/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "map/tile_collection.h"

using namespace Armory;



const TileMesh * TileCollection::get_tile(int index) const 
{
    if (index >= tileset.size()) 
        return nullptr;
    
    Variant element = tileset[index];
    if(element.is_ref())
    {
        Reference *reference = static_cast<Reference *>(static_cast<Object *>(element));
        return Cast<TileMesh>(reference);
    }

    return Cast<TileMesh>(element.get_validated_object());

}

void TileCollection::_bind_methods()
{
    BIND_GETSET(tileset,TileCollection )
    ADD_PROPERTY(PropertyInfo( Variant::ARRAY, "tileset", PROPERTY_HINT_ARRAY_TYPE, "Object"), XSTR(SETTER(tileset)), XSTR(GETTER(tileset)) );
    //BIND_PROPERTY_GETSET(TileCollection, , tileset, )
}