/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "map/tile_collection.h"

using namespace Armory;

void TileCollection::_bind_methods()
{
    BIND_PROPERTY_GETSET(TileCollection, Variant::ARRAY, tileset, PROPERTY_HINT_ARRAY_TYPE, "Tiles")
}