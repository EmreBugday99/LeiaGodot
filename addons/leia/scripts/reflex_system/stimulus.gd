# Stimulus.gd
# A self-contained observer Resource that listens to signals or state and notifies its Reflex when triggered.
extends Resource
class_name Stimulus

var owner_node: Node
var reflex: Reflex

func initialize(_owner_node: Node, _reflex: Reflex) -> void:
	owner_node = _owner_node
	reflex = _reflex
	_setup()

# Override in subclasses to connect signals or observe state
func _setup() -> void:
	pass

# Call this when the stimulus condition is met
func trigger(context: Dictionary = {}) -> void:
	if reflex:
		reflex.on_stimulus_triggered(context)
