@tool
extends Sprite2D

# map node
@export var _map_node_path : NodePath

# retrieve the image from map node
func get_map_image() :
	var map_node = get_node(_map_node_path)
	if map_node and map_node.has_method("get_image") :
		return map_node.get_image()
	else :
		print("failed to get map_node image")
	return Image.new()
	
# set image
func _ready():
	var image = get_map_image()
	if image :
		var tex = get_texture()
		if tex and tex.has_method("create_from_image"):
			var size = Vector2i(image.get_width(), image.get_height())
			size = size * 10
			image.resize(size.x, size.y, Image.INTERPOLATE_NEAREST)
			tex.create_from_image(image)
	else :
		print("could not retreive image")


