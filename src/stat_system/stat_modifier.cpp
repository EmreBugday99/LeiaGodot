#include "stat_modifier.hpp"

StatModifier::StatModifier()
{
    // Initialize default values if needed
    unique_identifier = "";
    target_tag = "";
    value = 0.0f;
    type = StatModifierType::STAT_MODIFIER_ADDITIVE;
}

StatModifier::~StatModifier()
{
}

String StatModifier::get_unique_identifier() const
{
    return unique_identifier;
}

String StatModifier::get_target_tag() const
{
    return target_tag;
}

float StatModifier::get_value() const
{
    return value;
}

StatModifierType StatModifier::get_modifier_type() const
{
    return type;
}

void StatModifier::set_unique_identifier(const String& p_identifier)
{
    unique_identifier = p_identifier;
}

void StatModifier::set_target_tag(const String& p_tag)
{
    target_tag = p_tag;
}

void StatModifier::set_value(float p_value)
{
    value = p_value;
}

void StatModifier::set_modifier_type(StatModifierType p_type)
{
    type = p_type;
}

void StatModifier::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_unique_identifier"), &StatModifier::get_unique_identifier);
    ClassDB::bind_method(D_METHOD("set_unique_identifier", "identifier"), &StatModifier::set_unique_identifier);
    ADD_PROPERTY(PropertyInfo(Variant::Type::STRING, "unique_identifier"), "set_unique_identifier", "get_unique_identifier");


    ClassDB::bind_method(D_METHOD("get_target_tag"), &StatModifier::get_target_tag);
    ClassDB::bind_method(D_METHOD("set_target_tag", "tag"), &StatModifier::set_target_tag);
    ADD_PROPERTY(PropertyInfo(Variant::Type::STRING, "target_tag"), "set_target_tag", "get_target_tag");


    ClassDB::bind_method(D_METHOD("get_value"), &StatModifier::get_value);
    ClassDB::bind_method(D_METHOD("set_value", "value"), &StatModifier::set_value);
    ADD_PROPERTY(PropertyInfo(Variant::Type::FLOAT, "value"), "set_value", "get_value");


    ClassDB::bind_method(D_METHOD("get_modifier_type"), &StatModifier::get_modifier_type);
    ClassDB::bind_method(D_METHOD("set_modifier_type", "type"), &StatModifier::set_modifier_type);
    ADD_PROPERTY(PropertyInfo(Variant::Type::INT, "modifier_type", PROPERTY_HINT_ENUM, "Additive,Multiplicative,Override"), "set_modifier_type", "get_modifier_type");

    BIND_ENUM_CONSTANT(StatModifierType::STAT_MODIFIER_ADDITIVE);
    BIND_ENUM_CONSTANT(StatModifierType::STAT_MODIFIER_MULTIPLICATIVE);
    BIND_ENUM_CONSTANT(StatModifierType::STAT_MODIFIER_OVERRIDE);
}