{libGdExt, src , name} : 
let
ext_file = ''
[configuration]
entry_symbol = "${name}_library_init"

[libraries]
linux.x86_64 = "res://bin/x11/lib${name}.so"
windows.x86_64 = "res://bin/win64/lib${name}.dll"
'';
in
libGdExt.mkGDExt {
  inherit src;
  extName = name;
  installPhase = ''
  mkdir -p $out/bin
  cp bin/lib${name}*.so $out/bin/lib${name}.so
  echo ${ext_file} >> $out/${name}.gdextension
  '';
}