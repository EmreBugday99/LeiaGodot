extends Resource
class_name StatResource

@export var identifier: String
@export var base_value: float
@export var min_value: float
@export var max_value: float

func create_stat_instance() -> Stat:
	return Stat.new(identifier, base_value, min_value, max_value)
