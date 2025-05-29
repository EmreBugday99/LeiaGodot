# Response.gd
# Stateless logic executor Resource. Executes behaviour when called by Reflex.
extends Resource
class_name Response

# Override in subclasses to implement behaviour
func execute(context: Dictionary) -> void:
	pass
