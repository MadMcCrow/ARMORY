# custom.py for godot binary

custom_modules = relpath('../modules')

# global options
platform="linuxbsd"
target="release"
tools="no"
optimize="speed"
debug_symbols="no"
warnings="moderate"
use_static_cpp="no"
deprecated="no"
no_editor_splash="yes"
modules_enabled_by_default="yes"

# linux options:
x11 = "yes"
dbus = "yes"
udev = "yes"
pulseaudio = "yes"

# build tool options:
verbose = "no"
progress = "yes"

# compiler options:
use_llvm = "no"
use_lld = "no"
use_lto = "yes"
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
module_websocket_enabled = "yes"         # necessary for asset library
module_jpg_enabled = "yes"

# enabled modules
module_opensimplex_enabled = "yes"
module_gltf_enabled = "yes"
module_assimp_enabled = "yes"
module_gridmap_enabled = "yes"
module_gdnative_enabled = "yes"
module_gdscript_enabled = "yes"
module_visual_script_enabled = "yes"


# disabled modules
module_mobile_vr_enabled = "no"
module_mono_enabled = "no"
module_fbx_enabled = "no"
module_mono_enabled = "no"
module_bullet_enabled = "no"
module_camera_enabled = "no"
module_webxr_enabled = "no"
module_theora_enabled = "no"
module_vorbis_enabled = "no"

# potential disabled modules
#module_basis_universal_enabled = "no"
#module_bmp_enabled = "no"
#module_csg_enabled = "no"
#module_cvtt_enabled = "no"
#module_dds_enabled = "no"
#module_denoise_enabled = "no"
#module_enet_enabled = "no"
#module_etcpak_enabled = "no"
#module_hdr_enabled = "no"
#module_jsonrpc_enabled = "no"
#module_lightmapper_rd_enabled = "no"
#module_mbedtls_enabled = "no"
#module_meshoptimizer_enabled = "no"
#module_minimp3_enabled = "no"
#module_msdfgen_enabled = "no"
#module_ogg_enabled = "no"
#module_pvr_enabled = "no"
#module_raycast_enabled = "no"
#module_squish_enabled = "no"
#module_tga_enabled = "no"
#module_tinyexr_enabled = "no"
#module_upnp_enabled = "no"
#module_vhacd_enabled = "no"
#module_webp_enabled = "no"
#module_webrtc_enabled = "no"
#module_xatlas_unwrap_enabled = "no"

