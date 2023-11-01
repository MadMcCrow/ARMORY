# this flakes uses godot-flake to build Armory
{
  description = "Armory, a RTS game made in Godot";
  inputs = { godot-flake.url = "github:MadMcCrow/godot-flake"; };

  outputs = { self, nixpkgs, godot-flake, ... }@inputs:
    with builtins;
    let
      # supported systems
      systems = [ "x86_64-linux" "aarch64-linux" ];

      # nixpkgs from godot-flake
      pkgs = godot-flake.inputs.nixpkgs;

      mergeSystems = f:
        foldl' (x: y: pkgs.lib.recursiveUpdate x y) { }
        (map f systems);

      # default system-agnostic flake implementation :
      flake = system:
        let

          # everything is in a separate nix file
          armory = import nix/armory.nix {
            inherit godot-flake system;
            flake = self;
          };
        in {
          packages."${system}" = {
            default = armory.extension;
          };
          devShell."${system}" = (import pkgs {inherit system;}).mkShell { 
            inputsFrom = [ armory.game ];
            buildInputs = armory.extension.nativeBuildInputs;
            };
        };
    in mergeSystems flake;
}
