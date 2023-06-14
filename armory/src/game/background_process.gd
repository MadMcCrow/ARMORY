class_name BackgroundProcess
extends Object

# the callable that will be called
var call = Callable()
var priority = Thread.PRIORITY_NORMAL

func get_tree() :
	return Engine.get_main_loop()

func bind(callable : Callable) :
	call = callable

func run() :
	var thread := Thread.new()
	thread.start(call, priority)
	while thread.is_alive():
		await get_tree().physics_frame
	thread.wait_to_finish()
	
func exec(callable : Callable) :
	bind(callable)
	run()
