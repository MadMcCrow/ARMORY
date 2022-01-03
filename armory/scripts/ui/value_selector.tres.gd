@tool
extends Control

@onready var SliderComp	= $Panel/VBox/ValueSlider
@onready var LabelComp 	= $Panel/VBox/VSplit/ValueLabel
@onready var NameComp  	= $Panel/VBox/VSplit/NameLabel

@export var min : float = 0
@export var max : float = 100
@export var val : float = 50
@export var display_name : String

func _ready():
	SliderComp.value_changed.connect(set_value)
	update_slider()
	set_value(0)
	
# update appearance, min and max
func update_slider() :
	val = clampf(val, min, max)
	if SliderComp:
		SliderComp.value = val
		SliderComp.max_value = max
		SliderComp.min_value = min
	if LabelComp :
		var text = "%3d" % float(val)
		LabelComp.set_text(text)
	if NameComp : 
		NameComp.set_text(display_name)

# set value on slider
func set_value(in_value):
	val = in_value
	update_slider()

		
func set_min(in_min) :
	min = in_min
	update_slider()

func set_max(in_max) :
	max = in_max
	update_slider()

func get_value() :
	return val
