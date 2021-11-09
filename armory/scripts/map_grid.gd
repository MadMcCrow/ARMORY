extends Node

# The mesh to use to show grid element positions in 3d
@export var debugMesh : Mesh

# grid size (2D)
@export var size : int = 20

# flattening factor
@export var flat_ratio : float = 100.0

# Seed for 2D noise
@export var random_seed : int = 15312


# inner matrix
@onready var _world = World.new()

#
# @func _ready
# called on scene init
#
func _ready():
	generate()


#
# @func generate
#  generate map
#
func generate():
	_world.set_size(Vector2i(size, size))
	_world.generate(random_seed, flat_ratio/100.0)
	
func get_image() :
	var image = Image.new()
	_world.export_to_image(image)
	print(image)
	return image



