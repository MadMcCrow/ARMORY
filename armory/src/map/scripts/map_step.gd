# MapScriptStep :
#	Struct-Like Resource
#	A wrapper around a scriptto add a name
#	(and possibly other things)
@tool
@icon("editor/icons/script")
class_name MapScriptStep
extends Resource

@export var name : String;
@export var gdscript : GDScript;
@export var parameters : Dictionary;

static var run_function_name = "run" 

# detect changes in script
func _set(property, value) :
	if property == "gdscript" and value != null :
		_set_parameters()
	return true

# update list of parameters
func _set_parameters() :
	parameters.clear()
	var list_of_properties := gdscript.get_script_property_list()
	for itr in list_of_properties:
		if itr.usage & PROPERTY_USAGE_SCRIPT_VARIABLE :
			parameters[itr.name] = gdscript.get_property_default_value(itr.name)
		
# will do what this step is supposed to do (should be async)
func run_step(grid : MapGrid) :
	if gdscript.has_method(run_function_name) :
		gdscript.call(run_function_name, grid, parameters)
	else :
		push_error("map script cannot be called")
