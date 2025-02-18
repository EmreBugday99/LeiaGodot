class_name ExpressionCondition
extends Resource

enum OperatorType {
	EQUALS,
	NOT_EQUAL,
	GREATER,
	SMALLER,
	GREATER_OR_EQUAL,
	SMALLER_OR_EQUAL
}

@export var left_operand: ExpressionDataContainer
@export var operator: OperatorType
@export var right_operand: ExpressionDataContainer

func evaluate(root_node: Node) -> bool:
	match operator:
		OperatorType.EQUALS:
			return left_operand.get_data(root_node) == right_operand.get_data(root_node)
		OperatorType.NOT_EQUAL:
			return left_operand.get_data(root_node) != right_operand.get_data(root_node)
		OperatorType.GREATER:
			return left_operand.get_data(root_node) > right_operand.get_data(root_node)
		OperatorType.SMALLER:
			return left_operand.get_data(root_node) < right_operand.get_data(root_node)
		OperatorType.GREATER_OR_EQUAL:
			return left_operand.get_data(root_node) >= right_operand.get_data(root_node)
		OperatorType.SMALLER_OR_EQUAL:
			return left_operand.get_data(root_node) <= right_operand.get_data(root_node)
		_:
			printerr("Invalid evaluation operator type.")
	
	return false
