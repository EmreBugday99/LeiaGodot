extends RefCounted
class_name Stat

var identifier: String
var value: float
var min_value: float
var max_value: float
var modifiers: Array[StatModifier]

var is_dirty: bool
var cached_value: float

func _init(stat_identifier: String, stat_value: float, stat_min_value: float, stat_max_value: float):
	identifier = stat_identifier
	value = stat_value
	min_value = stat_min_value
	max_value = stat_max_value
	is_dirty = true
	cached_value = 0.0

func get_base_value(target: StatModifier.TargetType) -> float:
	if target == StatModifier.TargetType.VALUE:
		return value
	elif target == StatModifier.TargetType.MIN:
		return min_value
	elif target == StatModifier.TargetType.MAX:
		return max_value
	
	printerr("Stat failed to find StatModifier.TargetType")
	return 0 # Should not fire?

func get_modified_target_value(target: StatModifier.TargetType) -> float:
	var base_value: float = get_base_value(target)
	var additive: float = 0.0
	var multiplier: float = 1.0
	var override_value: float = base_value
	
	for mod in modifiers:
		if mod.target == target:
			match mod.type:
				StatModifier.ModifierType.ADDITIVE:
					additive += mod.value
				StatModifier.ModifierType.MULTIPLICATIVE:
					multiplier *= (1 + mod.value)
				StatModifier.ModifierType.OVERRIDE:
					override_value = mod.value
	
	if override_value != base_value:
		return override_value
	else:
		return (base_value + additive) * multiplier

func get_min_modified() -> float:
	return get_modified_target_value(StatModifier.TargetType.MIN)

func get_max_modified() -> float:
	return get_modified_target_value(StatModifier.TargetType.MAX)

func get_value_modified() -> float:
	if is_dirty:
		cached_value = clampf(get_modified_target_value(StatModifier.TargetType.VALUE), get_min_modified(), get_max_modified())
		is_dirty = false
	return cached_value

func set_value(new_value: float) -> void:
	value = clampf(new_value, min_value, max_value)

func add_modifier(modifier: StatModifier) -> void:
	modifiers.append(modifier)
	sort_modifiers()

func remove_modifier(identifier: String) -> void:
	for i in modifiers.size():
		if modifiers[i].identifier == identifier:
			modifiers.remove_at(i)
			sort_modifiers()
			break

func clear_modifiers() -> void:
	modifiers.clear()

func sort_modifiers() -> void:
	modifiers.sort_custom(sort_modifier_descending)

func sort_modifier_descending(a: StatModifier, b: StatModifier) -> bool:
	return a.priority > b.priority
