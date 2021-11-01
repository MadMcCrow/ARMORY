@tool
extends Node

# The mesh to use to show grid element positions in 3d
@export var debugMesh : Mesh

# grid size (2D)
@export var size : int = 20

# Seed for 2D noise
@export var randomSeed : int = 15312

# how many different heights we can have
@export var quantificationSteps : int = 5

# random number generator
@onready var _rng = RandomNumberGenerator.new()

# simplex noise for map
@onready var _noise = OpenSimplexNoise.new()

# inner matrix
@onready var _matrix = Matrix.new()

#
# @func _ready
# called on scene init
#
func _ready():
	_matrix.set_size(Vector2i(size, size))
	_rng.randomize()
	_simplex_noise()
	_normalize()


#
# @func _random
# use simplex noise 
#
func _simplex_noise():
	# set noise
	_noise.seed = randomSeed
	_noise.octaves = 4
	_noise.period = 20.0
	_noise.persistence = 0.8
	# prepare image
	var image = _noise.get_seamless_image(size)
	image.convert(Image.FORMAT_L8)
	_matrix.from_image(image, Matrix.BRIGHTNESS)


#
# @func normalize
#
func _normalize() :
	_matrix.normalize(0.0,2)
	
	
func get_image() :
	var image = Image.new()
	_matrix.to_image(image)
	print(image)
	return image



