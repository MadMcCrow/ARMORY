{ godot-flake, system, flake }:
let
  # we use as much as possible pre-built godot from godot-flake
  godot-lib = godot-flake.lib."${system}";
  godot-pkgs = godot-flake.packages."${system}";
  #pkgs = import godot-flake.inputs.nixpkgs { inherit system; };

  # the extension
  extension = godot-lib.mkGdext {
    name = "armory";
    src = flake + "/src/armory";
    godot-cpp = godot-pkgs.godot-cpp;
    patches = [ ./SConstruct.patch ];
  };

  # the game
  # game = godot-lib.mkExport {
  #   godot = godot-pkgs.godot;
  #   src = flake + "/src/armory";
  #   name = "armory-game";
  #   buildInputs = [ extension ];
  #   # todo : get lib name from the nix derivation
  #   unpackPhase = ''
  #     cp -r $src/* ./
  #     mkdir -p ./bin/x11
  #     cp    ${extension}/bin/libarmory.so ./bin/x11
  #   '';
  # };
  
in {
 inherit extension;
}
