@tool
extends EditorPlugin


func _enter_tree() -> void:
	print("start")

func _exit_tree() -> void:
	print("stop")
