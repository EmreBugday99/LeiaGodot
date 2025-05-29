extends Node
class_name EffectManager
## Manages all active effects (instances) on a single entity.
## Handles application, stacking, ticking, and expiration.
## Mediates between entity, TagContainer, and StatStore.

## Maps effect identity (tag_self) to arrays of active EffectInstance objects
var active_effects: Dictionary[String, Array] = {}

## Reference to the entity's StatStore for stat changes
@export var stat_store: StatStore

## Reference to the entity's TagContainer for tag operations
@export var tag_container: TagContainer

## Timer for effect processing
var effect_timer: Timer

## Signals
signal effect_applied(effect: GameplayEffect, instance: EffectInstance)
signal effect_ticked(effect: GameplayEffect, instance: EffectInstance)
signal effect_expired(effect: GameplayEffect, instance: EffectInstance)

func _ready() -> void:
	# Initialize timer for effect processing
	effect_timer = Timer.new()
	effect_timer.wait_time = 0.1  # Process effects every 100ms
	effect_timer.timeout.connect(_process_effects)
	add_child(effect_timer)
	effect_timer.start()

func apply_effect(effect_resource: GameplayEffect, source_node: Node) -> bool:
	if not effect_resource or not source_node:
		return false
	
	# Check Tag Gating
	if not _check_tag_requirements(effect_resource):
		return false
	
	# Check Stacks
	var existing_instances: Array[EffectInstance] = active_effects.get(effect_resource.tag_self, [])
	
	# If we already have max stacks, handle refreshing or fail
	if existing_instances.size() >= effect_resource.max_stacks:
		if effect_resource.max_stacks == 1:
			# Refresh the existing effect
			existing_instances[0].refresh_duration()
			return true
		else:
			# Can't add more stacks
			return false
		# Create new effect instance
	var new_instance: EffectInstance = EffectInstance.new(source_node, get_parent(), effect_resource)
	
	# Add to active effects
	if effect_resource.tag_self not in active_effects:
		active_effects[effect_resource.tag_self] = []
	active_effects[effect_resource.tag_self].append(new_instance)
	
	# Apply Tags and Modifiers
	_apply_effect_changes(effect_resource, new_instance)
	
	# Run On Apply Response
	if effect_resource.on_apply_response:
		_execute_response(effect_resource.on_apply_response, new_instance)
	
	# Emit Signals
	effect_applied.emit(effect_resource, new_instance)
	
	return true

func remove_effect(tag_self: String) -> void:
	if tag_self not in active_effects:
		return
	
	var instances: Array[EffectInstance] = active_effects[tag_self]
	
	for instance in instances:
		# Run On Expire Response
		if instance.effect.on_expire_response:
			_execute_response(instance.effect.on_expire_response, instance)
				# Clean Up Tags and Modifiers
		_remove_effect_changes(instance.effect, instance)
		
		# Emit Signal
		effect_expired.emit(instance.effect, instance)
	
	# Remove from active effects
	active_effects.erase(tag_self)

func get_effects_by_tag(tag: String) -> Array[EffectInstance]:
	var result: Array[EffectInstance] = []
	
	for effect_tag in active_effects.keys():
		var instances: Array[EffectInstance] = active_effects[effect_tag]
		for instance in instances:
			if tag in instance.effect.tags_applied or instance.effect.tag_self == tag:
				result.append(instance)
	
	return result

func _check_tag_requirements(effect: GameplayEffect) -> bool:
	if not tag_container:
		return true
	
	# Check required tags
	for required_tag in effect.tags_required:
		if not tag_container.has_tag(required_tag):
			return false
	
	# Check blocked tags
	for blocked_tag in effect.tags_blocked:
		if tag_container.has_tag(blocked_tag):
			return false
	
	return true

func _apply_effect_changes(effect: GameplayEffect, instance: EffectInstance) -> void:
	# Apply tags
	if tag_container:
		for tag in effect.tags_applied:
			tag_container.add_tag(tag)
	
	# Apply stat modifiers
	if stat_store:
		for modifier in effect.stat_modifiers:
			var stat: Stat = stat_store.get_stat(modifier.target_tag)
			if stat:
				# Create unique modifier ID for this instance
				var instance_modifier_id = effect.tag_self + "_" + modifier.unique_identifier + "_" + str(instance.get_instance_id())
				stat.add_modifier(instance_modifier_id, modifier.target_tag, modifier.operation, modifier.value)
				instance.applied_modifier_ids.append(instance_modifier_id)

func _remove_effect_changes(effect: GameplayEffect, instance: EffectInstance) -> void:
	# Remove tags
	if tag_container:
		for tag in effect.tags_applied:
			tag_container.remove_tag(tag)
	
	# Remove stat modifiers using tracked IDs
	if stat_store:
		for modifier_id in instance.applied_modifier_ids:
			# Find the stat that this modifier was applied to
			for modifier in effect.stat_modifiers:
				var stat: Stat = stat_store.get_stat(modifier.target_tag)
				if stat:
					stat.remove_modifier(modifier_id)
					break  # Only need to remove from one stat per modifier ID

func _process_effects() -> void:
	var effects_to_remove: Array[String] = []
	
	for effect_tag in active_effects.keys():
		var instances: Array[EffectInstance] = active_effects[effect_tag]
		var expired_instances: Array[EffectInstance] = []
		
		for instance in instances:
			instance.tick(effect_timer.wait_time)
			
			if instance.expired:
				expired_instances.append(instance)
			elif instance.effect.period > 0 and instance.time_to_next_tick <= 0.0:
				effect_ticked.emit(instance.effect, instance)
				# Remove expired instances
		for expired_instance in expired_instances:
			instances.erase(expired_instance)
			_remove_effect_changes(expired_instance.effect, expired_instance)
			effect_expired.emit(expired_instance.effect, expired_instance)
		
		# Mark entire effect for removal if no instances left
		if instances.is_empty():
			effects_to_remove.append(effect_tag)
	
	# Clean up empty effect arrays
	for effect_tag in effects_to_remove:
		active_effects.erase(effect_tag)

func _execute_response(response: Resource, instance: EffectInstance) -> void:
	# Placeholder for response execution
	# This would be integrated with the response system when available
	pass