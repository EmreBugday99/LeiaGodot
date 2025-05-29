extends Resource
class_name Stat

@export var base_value: float = 0.0
@export var modifiers: Array[StatModifier] = []

func get_value() -> float:
	var add: float = 0.0
	var mul: float = 1.0
	var override = null
	
	# Calculate the final value of the stat based on base value and modifiers
	for m in modifiers:
		match m.operation:
			StatEnums.StatModifierOperation.ADD:
				add += m.value
			StatEnums.StatModifierOperation.SUBTRACT:
				add -= m.value
			StatEnums.StatModifierOperation.MULTIPLY:
				mul *= m.value
			StatEnums.StatModifierOperation.OVERRIDE:
				override = m.value
	
	if override != null:
		return float(override)
	return (base_value + add) * mul

func add_modifier(modifier_id: String, tag: String, operation: StatEnums.StatModifierOperation, value: float) -> void:
	var mod: StatModifier = StatModifier.new(modifier_id, tag, operation, value)
	modifiers.append(mod)

func clear_modifiers() -> void:
	modifiers.clear()

func remove_modifier(modifier_id: String) -> void:
	var index_to_remove := -1
	for i in range(modifiers.size()):
		if modifiers[i].unique_identifier == modifier_id:
			index_to_remove = i
			break
	
	if index_to_remove != -1:
		modifiers.remove_at(index_to_remove)
