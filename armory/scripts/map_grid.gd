@tool
extends Node


# Declare member variables here. Examples:
@export var debugMesh : Mesh
@export var sizeX : int = 20
@export var sizeY = sizeX
var steps = 5

# this is the final array
var _matrix = []
var _rng = RandomNumberGenerator.new()

# Called when the node enters the scene tree for the first time.
func _ready():
	_matrix.resize(sizeX * sizeY)
	_matrix.fill(0)
	_rng.randomize()
	_diamondsquare()
	_printMatrix()
	spawnCubes()


func _printMatrix():
	var line = []
	for x in range (0, sizeX):
		for y in range (0, sizeY): 
			line.append("%.2f" % _get(x,y))
		print(line)
		line = []

func _getCoord(x,y):
	var fixedX = int(x)%sizeX;
	var fixedY = int(y)%sizeY;
	return (fixedY * sizeX) + fixedX

# get value at x, y
func _get(x,y):
	return _matrix[_getCoord(x,y)]

# set value at x, y
func _set(x,y, val):
	_matrix[_getCoord(x,y)] = val

func _random(a,b):
	return _rng.randf_range(a, b)

func _diamondsquare():
	var h = sizeX + 1
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

func spawnCubes() :
	for x in range (0, sizeX):
		for y in range (0, sizeY): 
			var node = MeshInstance3D.new()
			node.set_name("node_%d_%d" % [x,y])
			add_child(node)
			node.set_owner(get_tree().edited_scene_root)
			node.translate(Vector3(x,_get(x,y), y))
			node.set_mesh(debugMesh)

