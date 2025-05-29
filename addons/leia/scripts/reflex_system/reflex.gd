# Reflex.gd
# Binds a Stimulus to a Response. Coordinates the flow but holds no world knowledge.
extends Resource
class_name Reflex

@export var stimulus: Stimulus
@export var response: Response

func initialize(owner_node: Node) -> void:
	if stimulus:
		stimulus.initialize(owner_node, self)

func on_stimulus_triggered(context: Dictionary) -> void:
	if response:
		response.execute(context)
