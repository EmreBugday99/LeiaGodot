class_name ExpressionCondition
extends Resource

enum OperatorType {
	EQUALS,
	GREATER
}

@export var left_operand: ExpressionDataContainer
@export var operator: OperatorType
@export var right_operand: ExpressionDataContainer

func evaluate(root_node: Node) -> bool:
	match operator:
		OperatorType.EQUALS:
			return left_operand.get_data(root_node) == right_operand.get_data(root_node)
		OperatorType.GREATER:
			return left_operand.get_data(root_node) > right_operand.get_data(root_node)
	
	return false
