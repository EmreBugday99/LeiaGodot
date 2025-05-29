# ReflexManager.gd
# Node that owns and initializes all Reflexes for an entity.
extends Node
class_name ReflexManager

@export var reflexes: Array # Array of Reflex resources

func _ready() -> void:
	for reflex in reflexes:
		if reflex:
			reflex.initialize(self)
