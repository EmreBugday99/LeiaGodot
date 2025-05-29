class_name ExpressionResource
extends Resource

@export var conditions: Array[ExpressionCondition]

func evaluate(root_node: Node) -> bool:
	if !conditions or conditions.is_empty():
		return true
	
	for condition in conditions:
		if condition.evaluate(root_node) == false:
			return false
	
	return true
