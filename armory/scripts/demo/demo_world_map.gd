extends WorldMap

# map node
@onready var config   = $PanelContainer/HSplitContainer/Config
@onready var tex_rect = $PanelContainer/HSplitContainer/ScrollContainer/TextureRect

# set image
func _ready():
	pass

func draw_map() :
	var tex = tex_rect.get_texture()
	var image = Image.new()
	image.create(get_size().x,get_size().y, false, Image.FORMAT_L8)
	export_to_image(image);
	var s = Vector2i(image.get_width(), image.get_height())
	s = s * 10
	image.resize(s.x, s.y, Image.INTERPOLATE_NEAREST)
	tex.create_from_image(image)
	tex_rect.set_texture(tex)

	


func _on_config_on_generate(s, x, y):
	set_seed(s)
	set_size(Vector2i(x,y))
	generate_cells()
	draw_map()
