@tool
extends Node

# The mesh to use to show grid element positions in 3d
@export var debugMesh : Mesh

# grid size (2D)
@export var size : int = 20

# flattening factor
@export var flat_ratio : float = 2.0

# Seed for 2D noise
@export var random_seed : int = 15312

# how many different heights we can have
@export var quantification_steps : int = 5

# random number generator
@onready var _rng = RandomNumberGenerator.new()

# simplex noise for map
@onready var _noise = OpenSimplexNoise.new()

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
	_rng.randomize()
	_simplex_noise()
	_world.level(flat_ratio)
	_world.steps(quantification_steps)


#
# @func _random
# use simplex noise 
#
func _simplex_noise():
	# set noise
	_noise.seed = random_seed
	_noise.octaves = 9
	_noise.period = size / 4.0
	_noise.persistence = 0.8
	# prepare image
	var image = _noise.get_seamless_image(size)
	image.convert(Image.FORMAT_L8)
	_world.generate_from_image(image)
	


	
func get_image() :
	var image = Image.new()
	_world.export_to_image(image)
	print(image)
	return image



