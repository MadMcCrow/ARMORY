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

@onready var debug_node = $debugCanvas/DebugDraw/DebugMesh

#
# @func _ready
# called on scene init
#
func _ready():
	_matrix.set_size(Vector2i(size, size))
	_rng.randomize()
	_simplex_noise()
	_normalize()
	_spawn_cubes()


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
	# set matrix
	for x in range (0, size):
		for y in range (0, size):
			_matrix.set(x,y,image.get_pixel(x,y).v)


#
# @func normalize
#
func _normalize() :
	_matrix.normalize(0.0,2)


#
# @func spawnCubes
# debug function to draw all cubes
#
func _spawn_cubes() :
	#set multimesh
	var multimesh = MultiMesh.new()
	var dim = size * 2
	multimesh.set_mesh(debugMesh)
	multimesh.set_transform_format(1) # 1 is 3D, 0 is 2D
	multimesh.set_instance_count(dim * dim)
	debug_node.set_multimesh(multimesh)
	#base transform
	var base = debug_node.get_transform()
	# set all instances
	for x in range (0, dim):
		for y in range (0, dim):
			var height = _matrix.get(x%size,y%size) * 10
			multimesh.set_instance_transform( x+(dim*y), base.translated(Vector3(x,height, y)))



