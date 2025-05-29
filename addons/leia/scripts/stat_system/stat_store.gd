extends Resource
class_name StatStore

@export var stats: Dictionary[String, Stat] = {}

func get_stat(tag: String) -> Stat:
	return stats.get(tag)
