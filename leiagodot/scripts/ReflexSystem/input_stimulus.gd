extends Stimulus
class_name InputStimulus

func initialize(reflex: Reflex) -> void:
	var button : Button = reflex.get_parent().find_child("Button")
	button.button_down.connect(reflex.trigger_reflex)

func can_stimulate(reflex: Reflex) -> bool:
	return true
