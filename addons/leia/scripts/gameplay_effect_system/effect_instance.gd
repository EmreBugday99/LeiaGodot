extends RefCounted
class_name EffectInstance
## Tracks an individual applied effect: its timer, tick logic, and stack count.
## Managed by EffectManager.

## Node that applied the effect
var causer: Node

## Entity affected by the effect
var target: Node

## Reference to the GameplayEffect resource
var effect: GameplayEffect

## Seconds until the effect expires
var remaining_time: float

## Current stack count
var current_stacks: int

## Whether this instance is marked for removal
var expired: bool = false

## Time until next tick
var time_to_next_tick: float

## Tracks modifier IDs applied by this instance for cleanup
var applied_modifier_ids: Array[String] = []

func _init(p_causer: Node, p_target: Node, p_effect: GameplayEffect, p_stacks: int = 1) -> void:
	causer = p_causer
	target = p_target
	effect = p_effect
	remaining_time = float(effect.duration)
	current_stacks = p_stacks
	time_to_next_tick = float(effect.period)

func tick(delta: float) -> void:
	if expired:
		return
	
	# Handle duration countdown
	if effect.duration > 0:
		remaining_time -= delta
		if remaining_time <= 0.0:
			expired = true
			return
	
	# Handle periodic ticking
	if effect.period > 0:
		time_to_next_tick -= delta
		if time_to_next_tick <= 0.0:
			time_to_next_tick = float(effect.period)
			# Execute tick response if available
			if effect.on_tick_response:
				_execute_response(effect.on_tick_response)

func add_stacks(amount: int) -> void:
	current_stacks = min(current_stacks + amount, effect.max_stacks)

func refresh_duration() -> void:
	remaining_time = float(effect.duration)

func _execute_response(response: Resource) -> void:
	# Placeholder for response execution
	# This would be implemented based on the response system design
	pass