extends Node
class_name StatContainer

var stats: Dictionary
@export var base_stats: Array[StatResource]

func _ready() -> void:
	for stat_resource: StatResource in base_stats:
		add_stat(stat_resource.create_stat_instance())

func has_stat(stat_identifier: String) -> bool:
	return stats.has(stat_identifier)

func get_stat(stat_identifier: String) -> Stat:
	return stats.get(stat_identifier)

func add_stat(stat: Stat) -> void:
	if not has_stat(stat.identifier):
		stats[stat.identifier] = stat
	else:
		printerr("Attempted to add already existing stat: " + stat.identifier)

func remove_stat(identifier: String) -> void:
	if not stats.erase(identifier):
		printerr("Failed to remove a non existing stat: " + identifier)

func get_stat_value(stat_identifier: String) -> float:
	var stat: Stat = get_stat(stat_identifier)
	if stat:
		return stat.get_value_modified()
	return 0.0

func set_stat_value(stat_identifier: String, new_value: float) -> void:
	var stat: Stat = get_stat(stat_identifier)
	if stat:
		stat.set_value(new_value)
