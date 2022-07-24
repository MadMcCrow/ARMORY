// Copyright © Noé Perard-Gayot 2022. Licensed under the MIT License.
// You may also obtain a copy of the License at https://opensource.org/licenses/mit-license.php
use gdnative::prelude::*;
use gdnative::api::Resource;

#[derive(NativeClass)]
#[inherit(Resource)]
pub struct ArmoryTile {
    #[property]
    name: String,
    #[property]
    north: String,
    #[property]
    south: String,
    #[property]
    east: String,
    #[property]
    west: String,
}

#[methods]
impl ArmoryTile {
    fn new(_owner: &Resource) -> Self {
    Self {
        name : "None".into(),
        north: "None".into(),
        south: "None".into(),
        east: "None".into(),
        west: "None".into(),
        }
    }
}