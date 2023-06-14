extends Node

@onready var map_node = %map_node

# Called when the node enters the scene tree for the first time.
func _ready():
	map_node.gen_map()

