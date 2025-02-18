class_name StateMachine
extends Node

@export var entry_state: StateResource
var current_state: StateResource
@export var root_node: Node

signal on_state_changed(previous_state: StateResource, current_state: StateResource, root_node: Node)

func _ready() -> void:
	current_state = entry_state
	if current_state:
		current_state.initialize(null)

func _process(delta: float) -> void:
	process_current_state()

func process_current_state() -> void:
	if !current_state:
		return
	
	if !current_state.is_root_node() and !current_state.transition_expression.evaluate(root_node):
		current_state = current_state.parent_state
	
	for iterated_state in current_state.next_states:
		if iterated_state.transition_expression.evaluate(root_node):
			var previous_state: StateResource = current_state
			current_state = iterated_state
			on_state_changed.emit(previous_state, current_state, root_node)
			return

func tranisiton_to(state_to_transition: StateResource) -> void:
	current_state = state_to_transition
