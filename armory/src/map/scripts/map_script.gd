@icon("editor/icons/script")
class_name MapScript
extends Resource

@export var display_name : String;
@export var steps : Array[MapScriptStep]

var _is_running : bool = false
var _last_step : int = 0

# called in between every step
signal on_script_step_complete(index : int)

# called when generation complete
signal on_script_complete()

#  will execute map script
func exec (grid : MapGrid) :
	_is_running = true
	# run every step, one after another :
	for index in range(steps.size()) :
		_last_step = index
		var step = steps[index]
		var process = BackgroundProcess.new()
		await process.exec(step.run_step.bind(grid))
		on_script_step_complete.emit(index)
	on_script_complete.emit()
	_is_running = false

# is the script being executed
# for now we are using this method instead of checking threads.
func is_running() :
	return _is_running
	
# what step are we at ?
func get_step() :
	return _last_step

