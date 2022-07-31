# Nix shell for developing a godot game on Nixos and/or with Nix
with import <nixpkgs> {
  config.android_sdk.accept_license = true;
};

stdenv.mkDerivation {
  name = "Armory";
  nativeBuildInputs = [
                    scons
                    gnumake
                    pkg-config
                    xorg.libX11
                    xorg.libXcursor
                    xorg.libXinerama
                    xorg.libXrandr
                    xorg.libXrender
                    xorg.libXi
                    xorg.libXext
                    xorg.libXfixes
                    udev
                    systemd
                    systemd.dev
                    libpulseaudio
                    freetype
                    openssl
                    alsa-lib
                    libGLU
                    zlib
                    yasm

                ];
  
  # Set Environment Variables
  EDITOR = "nano";
  LIBRARY_PATH = "${xorg.libXfixes}";
}
