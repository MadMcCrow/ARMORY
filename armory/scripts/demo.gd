extends Node

@onready var map = $MapNode
@onready var gen_button		 	= $Window/Panel/VSplitContainer/VBoxContainer2/MarginContainer/GenerateButton
@onready var seed_selector 		= $Window/Panel/VSplitContainer/VBoxContainer/selector_seed
@onready var size_selector 		= $Window/Panel/VSplitContainer/VBoxContainer/selector_size
@onready var r_selector 		= $Window/Panel/VSplitContainer/VBoxContainer/selector_ratio
@onready var sprite				= $ScrollContainer/AspectRatioContainer/Sprite2D

# Called when the node enters the scene tree for the first time.
func _ready():
	if not map :
		return
	if seed_selector:
		seed_selector.set_min(1)
		seed_selector.set_max(9999)
		size_selector.set_value(map.random_seed)
	if size_selector:
		size_selector.set_min(1)
		size_selector.set_max(500)
		size_selector.set_value(map.size)
	if r_selector:
		r_selector.set_min(1)
		r_selector.set_max(100)
		r_selector.set_value(map.flat_ratio)
	if gen_button:
		gen_button.button_up.connect(generate)
	

func generate():
	map.size = size_selector.get_value()
	map.flat_ratio = r_selector.get_value()
	map.random_seed = seed_selector.get_value()
	print("LET'S GO !")
	map.generate()
	sprite.draw_map()
