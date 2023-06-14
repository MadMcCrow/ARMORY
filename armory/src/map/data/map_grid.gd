@icon("editor/icons/script")
class_name MapGrid
extends Resource

static func _repeat( p: int, q : int) :
	return ( 0 if p >= 0  else q) + p % q

# Size of level
@export var size : Vector2i

# Actual array of cells
var grid : Array[MapCell]

static func new_grid(grid_size : Vector2i) :
	var grid = MapGrid.new()
	grid.size = grid_size
	grid.init_cells()
	return grid

func init_cells() :
	grid.resize(size.x * size.y)
	grid.fill(MapCell.new())

func coord2index(pos : Vector2i) :
	return _repeat(pos.x, size.x) + _repeat(pos.y, size.y) * size.x;

func get_cell(pos : Vector2i) :
	return grid[coord2index(pos)]
	
