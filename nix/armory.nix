{ godot-flake, system, flake }:
let
  # we use as much as possible pre-built godot from godot-flake
  godot-lib = godot-flake.lib."${system}";
  godot-pkgs = godot-flake.packages."${system}";
  #pkgs = import godot-flake.inputs.nixpkgs { inherit system; };

  # the extension
  extension = godot-lib.mkGdext {
    godot-cpp = godot-pkgs.godot-cpp;
    src = flake + "/src/armory";
    name = "armory";
    patches = [ ./SConstruct.patch ];
  };

  # the game
  game = godot-lib.mkExport {
    godot = godot-pkgs.godot;
    src = flake + "/src/armory";
    name = "armory";
    buildInputs = [ extension ];
  };
in {
 inherit extension game;
}
