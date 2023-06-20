class_name MapNode
extends Node

@export var gen_script : MapScript
@export var gen_size : Vector2i

# runtime
@onready var grid = MapGrid.new()

func gen_map() :
	grid.set_size(gen_size)
	if gen_script == null :
		return
	start_gen()
	await gen_script.exec(grid)
	end_gen()
	
	
func start_gen():
	pass
	
func end_gen():
	pass

