extends Node

# map node
#@onready var config   = $PanelContainer/HSplitContainer/Config
@onready var tex_rect = $PanelContainer/HSplitContainer/ScrollContainer/TextureRect

var seed = 156412
var x = 10
var y = 10 

# set image
func _ready():
	pass

func draw_map() :
	var tex = tex_rect.get_texture()
	var image = Image.new()
	image.create(get_size().x,get_size().y, false, Image.FORMAT_L8)
	WorldMap.export_to_image(image, 32);
	var s = Vector2i(image.get_width(), image.get_height())
	s = s * 10
	image.resize(s.x, s.y, Image.INTERPOLATE_NEAREST)
	tex.create_from_image(image)
	tex_rect.set_texture(tex)

	


func generate(s, x, y):
	WorldMap.set_seed(s)
	WorldMap.set_size(Vector2i(x,y))
	WorldMap.generate_cells()
	draw_map()
