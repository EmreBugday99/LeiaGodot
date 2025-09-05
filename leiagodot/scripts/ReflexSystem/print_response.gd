extends Response
class_name PrintResponse

func on_execute(reflex: Reflex) -> void:
	print("Executed: " + reflex.name)
