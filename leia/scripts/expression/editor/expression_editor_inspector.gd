extends EditorInspectorPlugin

func _can_handle(object: Object) -> bool:
	return object is ExpressionResource

func _parse_begin(object: Object) -> void:
	pass
