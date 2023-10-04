extends Node

@onready var map_node = %map_node

var test = MapGrid.new();

# Called when the node enters the scene tree for the first time.
func _ready():
	map_node.gen_map()

