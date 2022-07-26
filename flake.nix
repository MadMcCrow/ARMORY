# Flake for building armory with nix
{
    inputs = {
    };
    outputs = {self, nixpkgs, ...}@inputs: 
        let
            system = "x86_64-linux";
            pkgs = import nixpkgs{inherit system;};
        in
    {
        packages."${system}" = with pkgs; {
            default = stdenv.mkDerivation rec{
                name = "ARMORY";
                src = self;
                nativeBuildInputs = [
                    scons
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
                patchPhase = ''
                    substituteInPlace platform/linuxbsd/detect.py --replace 'pkg-config xi ' 'pkg-config xi xfixes '
                '';
                enableParallelBuilding = true;
                buildInputs = nativeBuildInputs;
                
                sconsFlags = "platform=linuxbsd";
                LIBRARY_PATH = "${xorg.libXfixes}";
                installPhase = ''
                    mkdir -p "$out/bin"
                    cp bin/godot.* $out/bin/godot
                '';
            };
        };

    };
}
