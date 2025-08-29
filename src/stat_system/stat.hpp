#ifndef STAT_HPP
#define STAT_HPP

#include <godot_cpp/classes/ref_counted.hpp>
#include "stat_modifier.hpp"

using namespace godot;

class Stat : public RefCounted
{
    GDCLASS(Stat, RefCounted);

private:
    String stat_tag; // Unique tag to identify the stat
    float base_value;
    TypedArray<StatModifier> modifiers; // List of modifiers affecting this stat

public:
    Stat();
    ~Stat();

    float get_value() const; // Calculate the effective value of the stat
    void add_modifier(const Ref<StatModifier> modifier);
    void remove_modifier(const Ref<StatModifier> modifier);
    void clear_modifiers();

    // Getters
    String get_stat_tag() const;
    float get_base_value() const;
    TypedArray<StatModifier> get_modifiers() const;

    // Setters
    void set_stat_tag(const String& p_tag);
    void set_base_value(float p_value);
    void set_modifiers(TypedArray<StatModifier> p_modifiers);

    static void _bind_methods();
};

#endif // STAT_HPP