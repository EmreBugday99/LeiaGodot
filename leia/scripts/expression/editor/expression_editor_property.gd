class_name  ExpressionEditorProperty
extends EditorProperty

var modify_button : Button

func _init() -> void:
	modify_button = Button.new()
	modify_button.set_text("Modify")
	modify_button.pressed.connect(self.modify_pressed)
	add_child(modify_button)

func modify_pressed() -> void:
	print("Button pressed")
	pass
