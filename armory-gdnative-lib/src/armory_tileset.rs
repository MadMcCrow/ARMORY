// Copyright © Noé Perard-Gayot 2022. Licensed under the MIT License.
// You may also obtain a copy of the License at https://opensource.org/licenses/mit-license.php
use gdnative::prelude::*;
use gdnative::api::Resource;
use gdnative::core_types::VariantArray;

#[derive(NativeClass)]
#[inherit(Resource)]
pub struct ArmoryTileSet {
    #[property]
    name: String,
    #[property]
    tiles : VariantArray<Shared>,
}

#[methods]
impl ArmoryTileSet {

// ctr
    fn new(_owner: &Resource) -> Self {
        ArmoryTileSet{
        name : "None".into(),
        tiles : VariantArray::<Shared>::new_shared()
        }
    }

}
