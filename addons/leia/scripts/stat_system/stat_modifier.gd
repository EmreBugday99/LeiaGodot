extends Resource
# StatModifier: Simple data structure for stat changes
class_name StatModifier
## A StatModifier is a simple data structure that represents a change to a stat.

## Unique identifier for the StatModifier, used to identify it in the system.
@export var unique_identifier: String
## The tag of the stat to modify
@export var target_tag: String = ""
## The value to change the stat by
@export var value: float = 0.0
## The operation to perform on the stat
@export var operation: StatEnums.StatModifierOperation = StatEnums.StatModifierOperation.ADD

## Initializes a new StatModifier with the specified parameters.
func _init(_unique_id: String = "", _target_tag: String = "", _operation: StatEnums.StatModifierOperation = StatEnums.StatModifierOperation.ADD, _value: float = 0.0):
	unique_identifier = _unique_id
	target_tag = _target_tag
	operation = _operation
	value = _value
