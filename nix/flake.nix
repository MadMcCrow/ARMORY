# this flakes uses godot-flake to build Armory
{
  description = "Armory, a RTS game made in Godot";
  inputs = {
    # the godot Engine
    godot-flake = {
      url = "github:MadMcCrow/godot-flake";
    };
  };

  outputs = { self, nixpkgs, ... }@inputs:
    let
      # only linux supported in nix for now
      system = "x86_64-linux";
      # use nixpkgs
      pkgs = import nixpkgs { inherit system; };
      lib = pkgs.lib;
      # get function from other flake
      libGodotFlake = inputs.godot-flake.lib."${system}";
      libGdExt = libGodotFlake.libGdExt;
      libGodot = libGodotFlake.libGodot;

      # how to build an extension
      mkExtension = args : import ./gdextension.nix  ({inherit libGdExt;} // args);
      mkArmory    = args : import ./gdproject.nix    ({inherit libGodot pkgs;} // args); 

      # extensions
      armory-ext = mkExtension {src = ../src/armory; name = "armory";};

      # project
      armory-project = mkArmory {src = ../armory; name = "armory"; dependencies = [armory-ext];};

      # godot engine editor
      godotEditor = libGodot.mkGodot {withTemplates = false;};
        
    in {
      #interface
      packages."${system}" = with pkgs; {
        inherit  armory-project;
        default = armory-project;
      };
      
      # dev-shell
      devShells."${system}".default = (libGdExt.mkExtensionShell armory-ext).overrideAttrs (oldAttr:
      {
         inputsFrom = [ armory-project armory-ext];
         shellHook = oldAttr.shellHook + ''
            ln -s ${godotEditor}/bin/*
            mkdir -p armory/bin/x11
         '';
      });
    };
}