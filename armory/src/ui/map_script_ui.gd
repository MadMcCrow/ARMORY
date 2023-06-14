extends Control

# export
@export var map_node_path : NodePath

@export var script_text_path   : NodePath
@export var step_text_path     : NodePath
@export var step_progress_path : NodePath


# runtime
@onready var map_node : MapNode          = get_node(map_node_path)
@onready var script_text : Label         = get_node(script_text_path)
@onready var step_text : Label           = get_node(step_text_path)
@onready var step_progress : ProgressBar = get_node(step_progress_path)

# hidden
var _map_script

func _ready():
	set_map_script(map_node.gen_script)

func _set_text( label : Label, text : String) :
	if label != null :
		label.set_text(text)

func set_map_script(src : MapScript) :
	# save and store
	_map_script = src
	_set_text(script_text, _map_script.display_name)
	_map_script.on_script_step_complete.connect(self.update_step)
	if not _map_script.steps.is_empty() :
		update_step(_map_script.get_step())

# update step text and progressbar
func update_step(step : int):
	if _map_script != null :
		_set_text(step_text, _map_script.steps[step].name)
		if step_progress != null :
			step_progress.set_value_no_signal(float(step) / _map_script.steps.size())
