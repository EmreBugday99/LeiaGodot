#include "stat.hpp"
#include <godot_cpp/variant/utility_functions.hpp>
#include "../helper_macros.hpp"

Stat::Stat()
{
    stat_tag = "no_tag";
    base_value = 0.0f;
}

Stat::~Stat()
{
}

float Stat::get_value() const
{
    float add_value = 0.0f;
    float mult_value = 1.0f;
    float override_value = 0.0f;
    bool has_override = false;

    for (int64_t i = 0; i < modifiers.size(); i++)
    {
        Ref<StatModifier> modifier = modifiers[i];
        if (modifier == nullptr)
            continue;

        switch (modifier->get_modifier_type())
        {
        case STAT_MODIFIER_ADDITIVE:
            add_value += modifier->get_value();
            break;
        case STAT_MODIFIER_MULTIPLICATIVE:
            mult_value *= modifier->get_value();
            break;
        case STAT_MODIFIER_OVERRIDE:
            override_value = modifier->get_value();
            has_override = true;
            break;
        }
    }

    if (has_override)
        return override_value;
    else
        return (base_value + add_value) * mult_value;
}

void Stat::add_modifier(const Ref<StatModifier> modifier)
{
    if (modifier.is_valid() == false)
    {
        UtilityFunctions::push_error("Attempted to add an invalid StatModifier to Stat: " + stat_tag);
        return;
    }

    // Check for existing modifier with the same unique identifier
    for (int64_t i = 0; i < modifiers.size(); i++)
    {
        Ref<StatModifier> existing_modifier = modifiers[i];
        if (existing_modifier.is_valid() && existing_modifier->get_unique_identifier() == modifier->get_unique_identifier())
        {
            UtilityFunctions::push_warning("Modifier with unique identifier '" + modifier->get_unique_identifier() + "' already exists in Stat: " + stat_tag);
            return; // Do not add duplicate modifiers
        }
    }

    // If not found, add the new modifier
    modifiers.push_back(modifier);
}

void Stat::remove_modifier(const Ref<StatModifier> modifier)
{
    if (modifier.is_valid() == false)
    {
        UtilityFunctions::push_error("Attempted to remove an invalid StatModifier from Stat: " + stat_tag);
        return;
    }

    // Find the modifier by unique identifier and cache the index
    int64_t modifier_index = -1;
    for (int64_t i = 0; i < modifiers.size(); i++)
    {
        Ref<StatModifier> existing_modifier = modifiers[i];
        if (existing_modifier.is_valid() && existing_modifier->get_unique_identifier() == modifier->get_unique_identifier())
        {
            modifier_index = i;
            break;
        }
    }

    // Remove the modifier if found
    if (modifier_index != -1)
        modifiers.remove_at(modifier_index);
    else
        UtilityFunctions::push_warning("Attempted to remove a StatModifier with unique identifier '" + modifier->get_unique_identifier() + "' that does not exist in Stat: " + stat_tag);
}

void Stat::clear_modifiers()
{
    modifiers.clear();
}

String Stat::get_stat_tag() const
{
    return stat_tag;
}

float Stat::get_base_value() const
{
    return base_value;
}

TypedArray<StatModifier> Stat::get_modifiers() const
{
    return modifiers;
}

void Stat::set_stat_tag(const String& p_tag)
{
    stat_tag = p_tag;
}

void Stat::set_base_value(float p_value)
{
    base_value = p_value;
}

void Stat::set_modifiers(TypedArray<StatModifier> p_modifiers)
{
    modifiers = p_modifiers;
}

void Stat::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_value"), &Stat::get_value);
    ClassDB::bind_method(D_METHOD("add_modifier", "modifier"), &Stat::add_modifier);
    ClassDB::bind_method(D_METHOD("remove_modifier", "modifier"), &Stat::remove_modifier);
    ClassDB::bind_method(D_METHOD("clear_modifiers"), &Stat::clear_modifiers);

    ClassDB::bind_method(D_METHOD("get_stat_tag"), &Stat::get_stat_tag);
    ClassDB::bind_method(D_METHOD("get_base_value"), &Stat::get_base_value);
    ClassDB::bind_method(D_METHOD("get_modifiers"), &Stat::get_modifiers);

    ClassDB::bind_method(D_METHOD("set_stat_tag", "tag"), &Stat::set_stat_tag);
    ClassDB::bind_method(D_METHOD("set_base_value", "value"), &Stat::set_base_value);
    ClassDB::bind_method(D_METHOD("set_modifiers", "modifiers"), &Stat::set_modifiers);    ADD_PROPERTY(PropertyInfo(Variant::STRING, "stat_tag"), "set_stat_tag", "get_stat_tag");
    
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "base_value"), "set_base_value", "get_base_value");
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "modifiers", PROPERTY_HINT_ARRAY_TYPE, LEIA_MAKE_RESOURCE_TYPE_HINT("StatModifier")), "set_modifiers", "get_modifiers");
}