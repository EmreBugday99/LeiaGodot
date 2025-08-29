#ifndef STAT_MODIFIER_HPP
#define STAT_MODIFIER_HPP

#include <godot_cpp/classes/resource.hpp>

using namespace godot;

enum StatModifierType
{
    STAT_MODIFIER_ADDITIVE,       // Adds directly to base value
    STAT_MODIFIER_MULTIPLICATIVE, // Multiplies after additive modifications
    STAT_MODIFIER_OVERRIDE        // Overrides all previous calculations
};

class StatModifier : public Resource
{
    GDCLASS(StatModifier, Resource);

private:
    String unique_identifier; // Unique identifier for the modifier
    String target_tag; // Tag to identify the target stat
    float value = 0.0f; // Value of the modifier
    StatModifierType type = STAT_MODIFIER_ADDITIVE; // Type of the modifier

public:
    StatModifier();
    ~StatModifier();

    // Getters
    String get_unique_identifier() const;
    String get_target_tag() const;
    float get_value() const;
    StatModifierType get_modifier_type() const;

    // Setters
    void set_unique_identifier(const String& p_identifier);
    void set_target_tag(const String& p_tag);
    void set_value(float p_value);
    void set_modifier_type(StatModifierType p_type);

    static void _bind_methods();
};
VARIANT_ENUM_CAST(StatModifierType)

#endif // STAT_MODIFIER_HPP