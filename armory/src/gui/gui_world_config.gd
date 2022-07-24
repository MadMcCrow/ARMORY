extends Node

signal on_generate(s,x,y)


@onready var s = $VBoxContainer/Seed
@onready var x = $VBoxContainer/X
@onready var y = $VBoxContainer/Y
@onready var b = $VBoxContainer/Button

func _ready():
	b.pressed.connect(self.button_pressed)

func generate():
	emit_signal("on_generate", s.get_value(), x.get_value(), y.get_value())
	pass


func button_pressed():
	generate()
