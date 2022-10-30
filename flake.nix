{
  description = "godot and the godot-cpp bindings";
  inputs = {
    # godot engine, master branch
    godot-flake = { url = "github:MadMcCrow/Godot-Flake"; };
  };

  outputs = { self, nixpkgs, godot-flake, ... }@inputs:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs { inherit system; };
      flags =  "platform=linux";
      buildTools = with pkgs; [scons pkg-config autoPatchelfHook patchelf gcc clang];
      godot     = inputs.godot-flake.packages."${system}".godot;
      godot-cpp = inputs.godot-flake.packages."${system}".godot-cpp; 
    in rec {
      packages."${system}" = {
        # armory extension
        armory-extension = stdenv.mkDerivation rec {
          name = "armory-extension";
          src = self + "/extensions";
          sconsFlags = flags;
          nativeBuildInputs = buildTools;
          buildInputs = nativeBuildInputs ++ [ godot-cpp ];
          patchPhase = ''
            ln -s ${godot-cpp} ./godot-cpp;
          '';
            installPhase = ''
            mkdir -p "$out/bin"
            cp bin/godot.* $out/bin/godot.bin
          '';
        };

        # default:
        # todo : make a editor output and a Game output 
        default = pkgs.linkFarmFromDrvs "armory"
          [ 
            packages."${system}".armory-extension
            godot # the engine
          ];
      };

      devShells."${system}".default =
        mkShell {
          nativeBuildInputs = buildTools ++ libs;
          runtimeDependencies = libs + [ packages."${system}".default];        
        };

    };
}
