extends Resource
class_name GameplayEffect
## Defines a reusable effect (buff, debuff, etc.) as a data asset.
## Specifies stacking, durations, tags, and stat modifiers.

## Unique identity tag for this effect instance (used for stacking and removal)
@export var tag_self: String = ""

## Tags added to the target while the effect is active
@export var tags_applied: Array[String] = []

## Tags that must be present on the entity to apply this effect
@export var tags_required: Array[String] = []

## Tags that block this effect if present on the entity
@export var tags_blocked: Array[String] = []

## How long the effect lasts in seconds (0 = instant)
@export var duration: int = 0

## Seconds between ticks for periodic responses (0 = not ticking)
@export var period: int = 0

## Maximum number of effect stacks allowed (>= 1)
@export var max_stacks: int = 1

## Texture resource for UI display (optional)
@export var icon: Texture = null

## Text description for designers and tooltips
@export var description: String = ""

## Array of stat modifier objects
@export var stat_modifiers: Array[StatModifier] = []

## Optional resource for custom logic when the effect is applied
@export var on_apply_response: Response = null

## Optional resource for custom logic on every tick
@export var on_tick_response: Response = null

## Optional resource for custom logic when the effect expires
@export var on_expire_response: Response = null