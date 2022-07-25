# Nix shell for developing a godot game on Nixos and/or with Nix
with import <nixpkgs> {
  config.android_sdk.accept_license = true;
};

stdenv.mkDerivation {
  name = "{{project-name}}";
  nativeBuildInputs = [
    cacert
    godot
    godot-export-templates
    jdk
    nix
    openssl
    pkgconfig
    ccache
    scons
  ];
  buildInputs = [
    alsaLib
    gcc-unwrapped.lib
    git
    clang
    libclang
    glibc_multi
    libGL
    libpulseaudio
    zlib
    llvmPackages.openmp] 
    ++ (with xorg;[
    libGLU
    libX11
    libXcursor
    libXext
    libXfixes
    libXi
    libXinerama
    libXrandr
    libXrender
    libglvnd
    libpulseaudio
    ]);
  
  shellHook = ''
    export PATH=$HOME/.rustup/toolchains/stable-x86_64-unknown-linux-gnu/bin:$PATH
  '';

  # Set Environment Variables
  EDITOR = "nano";
  LD_LIBRARY_PATH = builtins.concatStringsSep ":"  [
    "${alsaLib}/lib/"
    "${libGL}/lib/"
    "${libpulseaudio}/lib/"
    "${xorg.libX11}/lib/"
    "${xorg.libXcursor}/lib/"
    "${xorg.libXi}/lib/"
    "${xorg.libXinerama}/lib/"
    "${xorg.libXrandr}/lib/"
    "${xorg.libXrender}/lib/"
    "${xorg.libXext}/lib/"
    "${xorg.libXfixes}/lib/"
    "${xorg.libXcomposite}/lib/"
    "${zlib}/lib/"
    "${libclang}/lib"
  ];
  LIBCLANG_PATH = "${pkgs.llvmPackages_11.libclang.lib}/lib";
  CCACHE_DIR = "./.ccache";
  CCACHE_TEMPDIR="./.ccache";
  CC="ccache gcc-$(VER)";
  CXX="ccache g++-$(VER)";
  SHLIB_CXXLD="g++-$(VER)";
}
