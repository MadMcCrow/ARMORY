@tool
extends Node



# The mesh to use to show grid element positions in 3d
@export var debugMesh : Mesh

# grid size (2D)
@export var size : Vector2i = Vector2i(20,20)

# how many different heights we can have
@export var quantificationSteps : int = 5

# grid matrix stored as 1D array
@onready var _matrix = []

#random number generator
@onready var _rng = RandomNumberGenerator.new()

#
# @func _ready
# called on scene init
#
func _ready():
	_matrix.resize(size.x * size.y)
	_matrix.fill(0)
	_rng.randomize()
	_diamondsquare()
	_printMatrix()
	_spawnCubes()

#
# @func _printMatrix
# print in output the content of the grid
#
func _printMatrix():
	var line = []
	for x in range (0, size.x):
		for y in range (0, size.y):
			line.append("%.2f" % _get(x,y))
		print(line)
		line = []

#
# @func _getCoord
# @returns 1D coord of 2D coords
#
func _getCoord(x ,y):
	var fixedX = int(x)%size.x;
	var fixedY = int(y)%size.y;
	return (fixedY * size.x) + fixedX

#
# @func _get
# @returns value at {x,y}
#
func _get(x,y):
	return _matrix[_getCoord(x,y)]

#
# @func _set
# sets value at {x,y}
#
func _set(x,y, val):
	_matrix[_getCoord(x,y)] = val

#
# @func _random
# gets a random value for {a,b}
#
func _random(a,b):
	return _rng.randf_range(a, b)

#
# @func _diamondsquare
# diamond square algorithm to generate an array
#
func _diamondsquare():
	var h = size.x + 1
	_set(0,0, _random(-h, h))  # initialisation des coins : 1 seul
	var i = h-1
	while i > 1 :
		var id = floor(i/2.0)
		for x in range(id, h, i): # x allant de id à h avec un pas de i  /* début de la phase du diamant */
			for y in range(id, h, i): #pour y allant de id à h avec un pas de i
				var mean = (_get(x - id, y - id) + _get(x - id, y + id) + _get(x + id, y + id) + _get(x + id, y - id) / 4)
				_set(x, y, (mean + _random(-id, id)))

		var offset = 0
		for x in range(0,h, id):#f x allant de 0 à h avec un pas de id  /* début de la phase du carré */
			if offset == 0 :
				offset = id
			else:
				offset = 0

			for y in range(offset,h,i): #pour y allant de décalage à h avec un pas de i
				var sum = 0
				var n = 0
				if  x >= id :
					sum = sum + _get(x - id, y)
					n = n+1

				if x + id < h :
					sum = sum + _get(x + id, y)
					n = n+1

				if y >= id :
					sum = sum + _get(x, y - id)
					n = n+1

				if y + id < h :
					sum = sum + _get(x, y + id)
					n = n+1

				_set(x, y, sum / n + _random(-id, id))

		i = id
	#while end

#
# @func spawnCubes
# debug function to draw all cubes
#
func _spawnCubes() :
	# get a multimeshinstance
	var node = MultiMeshInstance3D.new()
	node.set_name("debugmultimesh")
	node.set_owner(get_tree().edited_scene_root)
	add_child(node)
	#set multimesh
	var multimesh = MultiMesh.new()
	node.set_multimesh(multimesh)
	multimesh.set_mesh(debugMesh)
	multimesh.set_transform_format(1) # 1 is 3D, 0 is 2D
	multimesh.set_instance_count( size.x * size.y)
	#base transform
	var base = node.get_transform()
	# set all instances
	for x in range (0, size.x):
		for y in range (0, size.y):
			multimesh.set_instance_transform( _getCoord(x,y), base.translated(Vector3(x,_get(x,y), y)))



