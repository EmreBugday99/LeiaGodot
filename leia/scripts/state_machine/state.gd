class_name StateResource
extends Resource

@export var state_name: String
@export var next_states: Array[StateResource]
# Determines whether it is possible to transition to THIS state
@export var transition_expression: ExpressionResource
var parent_state: StateResource

func initialize(parent: StateResource):
	parent_state = parent
	
	for iterated_state in next_states:
		iterated_state.initialize(self)

func is_root_node() -> bool:
	return parent_state == null
