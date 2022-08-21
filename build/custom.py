# custom.py for godot binary
# this configuration creates the simplest editor we can for Armory

# build configuration
# platform="linuxbsd" autodetect
target="release_debug"
optimize="speed"

# engine features
tools="yes"
production="yes"
modules_enabled_by_default="no"
deprecated="no"
no_editor_splash="yes"

# output
progress="yes"
warnings="moderate"

# linking
use_static_cpp="yes" if target == "release"  else "no"
use_lto="yes" if target == "release"  else "no"

# debug symbols
debug_symbols="yes" if target != "release"  else "no"
separate_debug_symbols="yes" if debug_symbols == "yes"  else "no"

# linux options:
x11 = "yes"
dbus = "yes"
udev = "yes"
pulseaudio = "yes"

# SAN
use_ubsan="yes" if target == "release"  else "no"
use_asan="yes"  if target == "release"  else "no"
use_lsan="yes"  if target == "release"  else "no"
use_msan="yes"  if target == "release"  else "no"

# build tool options:
verbose = "false"
progress = "yes"

# compiler options:
use_llvm = "no"
use_lld = "no"
use_lto = "no"
use_thinlto = "no"

# vulkan option
vulkan = "yes"
use_volk = "yes"

# requiered modules
module_regex_enabled = "yes"            # requiered
module_freetype_enabled="yes"           # requiered
module_glslang_enabled = "yes"          # requiered
module_text_server_fb_enabled = "yes"   # requiered
module_navigation_enabled = "yes"       # requiered
module_svg_enabled = "yes"              # editor icons

#optional modules
module_text_server_adv_enabled = "yes"   # necessary for non latin text
module_websocket_enabled = "yes"         # necessary for asset library and networking
module_jpg_enabled = "yes"

# enabled modules
module_opensimplex_enabled = "yes"
module_gltf_enabled = "yes"
module_assimp_enabled = "yes"
module_gdnative_enabled = "yes"
module_gdscript_enabled = "yes"
module_visual_script_enabled = "yes"
module_hdr_enabled = "yes"

# disabled modules
module_squish_enabled = "no"
module_fbx_enabled = "no"
module_mobile_vr_enabled = "no"
module_mono_enabled = "no"
module_bullet_enabled = "no"
module_camera_enabled = "no"
module_webxr_enabled = "no"
module_theora_enabled = "no"
module_ogg_enabled = "no"
module_vorbis_enabled = "no"
module_bmp_enabled = "no"
module_tga_enabled = "no"
module_gridmap_enabled = "no"
module_basis_universal_enabled = "no"
module_csg_enabled = "no"
module_cvtt_enabled = "no"
module_dds_enabled = "no"
module_denoise_enabled = "no"
module_enet_enabled = "no"
module_etcpak_enabled = "no"
module_jsonrpc_enabled = "no"
module_lightmapper_rd_enabled = "no"
module_mbedtls_enabled = "no"
module_meshoptimizer_enabled = "no"
module_minimp3_enabled = "no"
module_msdfgen_enabled = "no"
module_pvr_enabled = "no"
module_raycast_enabled = "no"
module_tinyexr_enabled = "no"
module_upnp_enabled = "no"
module_vhacd_enabled = "no"
module_webp_enabled = "no"
module_webrtc_enabled = "no"
module_xatlas_unwrap_enabled = "no"
