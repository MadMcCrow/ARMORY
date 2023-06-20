# gdproject.nix
# Function to either edit or build/export game made with godot
# TODO : possibly move to godot-flake
{libGodot, pkgs, src , name, dependencies, isEditor ? true , isDebug ? true , templateName ? "linux-x86_64"} : 
with pkgs;
let 
linux_ext = ".bin";
# export commandline
export = ''godot --export ${templateName} ${name}${linux_ext}'';
# godot editor
godotEngine = libGodot.mkGodot {withTemplates = !isEditor;};
in
# result derivation
stdenv.mkDerivation {
  inherit name src;
  nativeBuildInputs = [godotEngine] ++ dependencies;
  buildPhase = "";
}
