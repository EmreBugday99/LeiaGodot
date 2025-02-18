extends RefCounted
class_name StatModifier

enum ModifierType { ADDITIVE, MULTIPLICATIVE, OVERRIDE }
enum TargetType { VALUE, MIN, MAX }

var identifier: String
var target: TargetType
var type: ModifierType
var value: float
var priority: int # Higher priority takes precedence

func _init(mod_id: String, mod_target: TargetType, mod_type: ModifierType, mod_value: float, mod_priority: int = 0):
	identifier = mod_id
	target = mod_target
	type = mod_type
	value = mod_value
	priority = mod_priority
