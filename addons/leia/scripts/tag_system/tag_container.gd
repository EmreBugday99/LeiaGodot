extends Resource
class_name TagContainer
## A container for managing tags in a normalized way.
## Tags are stored in a normalized format (trimmed and lowercase) to ensure consistency.

## Emitted when a tag is added
signal tag_added(tag: String) 
## Emitted when a tag is removed
signal tag_removed(tag: String)

## List of normalized tags in this container
@export var tags: Array[String] = []

## Normalizes a tag by trimming and converting to lowercase
func normalise(tag: String) -> String:
	return tag.strip_edges().to_lower()

## Adds a tag to the container if not already present
func add_tag(tag: String) -> void:
	tag = normalise(tag)
	if not tags.has(tag):
		tags.append(tag)
		tag_added.emit(tag)

## Removes a tag from the container if present
func remove_tag(tag: String) -> void:
	tag = normalise(tag)
	if tags.has(tag):
		tags.erase(tag)
		tag_removed.emit(tag)

## Checks if a tag exists in the container (normalized)
func has_tag(tag: String) -> bool:
	return tags.has(normalise(tag))

## Returns true if all query tags exist in the container
func has_all(query_tags: Array[String]) -> bool:
	for tag: String in query_tags:
		if not has_tag(tag):
			return false
	return true

## Returns true if any query tag exists in the container
func has_any(query_tags: Array[String]) -> bool:
	for tag: String in query_tags:
		if has_tag(tag):
			return true
	return false

## Returns true if the tag or any ancestor tag exists in the container
func has_tag_or_ancestor(tag: String) -> bool:
	tag = normalise(tag)
	var parts: Array[String] = tag.split(".")
	var ancestor_tags: Array[String] = []

	# Build all possible ancestor tags from most specific to most general
	for i: int in range(parts.size(), 0, -1):
		var ancestor: String = ".".join(parts.slice(0, i))
		ancestor_tags.append(ancestor)

	# Check if any ancestor tag exists in tags
	for ancestor_tag: String in ancestor_tags:
		if tags.has(ancestor_tag):
			return true

	return false
