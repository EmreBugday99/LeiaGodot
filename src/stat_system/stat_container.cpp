#include "stat_container.hpp"
#include <godot_cpp/variant/utility_functions.hpp>
#include "stat.hpp"
#include "stat_container_component.hpp"
#include "../helper_macros.hpp"

StatContainer::StatContainer()
{
    connect("ready", Callable(this, "on_ready"));
}

StatContainer::~StatContainer()
{
    remove_all_stats();
}

void StatContainer::on_ready()
{
    invoke_component_method(ComponentEvent::CONTAINER_READY);
}

bool StatContainer::add_stat(const Ref<Stat> stat_to_add)
{
    Ref<Stat> found_stat = find_stat(stat_to_add->get_stat_tag());
    if (found_stat.is_valid()) // No duplicate stats allowed
        return false;

    contained_stats.push_back(stat_to_add);

    invoke_component_method(ComponentEvent::STAT_ADDED, stat_to_add);
    emit_signal("stat_added", stat_to_add);

    return true;
}

bool StatContainer::remove_stat(const String& stat_identifier)
{
    int64_t stat_index = -1;
    for (int64_t i = 0; i < contained_stats.size(); i++)
    {
        Ref<Stat> iterated_stat = contained_stats[i];
        if (iterated_stat->get_stat_tag() == stat_identifier)
        {
            stat_index = i;
            break;
        }
    }

    if (stat_index != -1)
    {
        Ref<Stat> removed_stat = contained_stats[stat_index];
        contained_stats.remove_at(stat_index);

        invoke_component_method(ComponentEvent::STAT_REMOVED, removed_stat);
        emit_signal("stat_removed", removed_stat);

        return true;
    }
    else
    {
        UtilityFunctions::push_warning("Attempted to remove a Stat with unique identifier '" + stat_identifier + "' that does not exist in the Stat Container.");
        return false;
    }
}

void StatContainer::remove_all_stats()
{
    for (Ref<Stat> stat : contained_stats)
    {
        invoke_component_method(ComponentEvent::STAT_REMOVED, stat);
        emit_signal("stat_removed", stat);
    }

    contained_stats.clear();
}

Ref<Stat> StatContainer::find_stat(const String& stat_identifier)
{
    for (Ref<Stat> iterated_stat : contained_stats)
    {
        if (iterated_stat->get_stat_tag() == stat_identifier)
            return iterated_stat;
    }

    return Ref<Stat>(nullptr);
}

TypedArray<StatContainerComponent> StatContainer::get_stat_components() const
{
    return container_components;
}

void StatContainer::set_stat_components(const TypedArray<StatContainerComponent> components)
{
    container_components = components;
}

void StatContainer::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("on_ready"), &StatContainer::on_ready);

    ClassDB::bind_method(D_METHOD("add_stat", "stat_to_add"), &StatContainer::add_stat);
    ClassDB::bind_method(D_METHOD("remove_stat", "stat_identifier"), &StatContainer::remove_stat);
    ClassDB::bind_method(D_METHOD("remove_all_stats"), &StatContainer::remove_all_stats);
    ClassDB::bind_method(D_METHOD("find_stat", "stat_identifier"), &StatContainer::find_stat);

    ClassDB::bind_method(D_METHOD("get_stat_components"), &StatContainer::get_stat_components);
    ClassDB::bind_method(D_METHOD("set_stat_components", "components"), &StatContainer::set_stat_components);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "container_components", PROPERTY_HINT_ARRAY_TYPE, LEIA_MAKE_RESOURCE_TYPE_HINT("StatContainerComponent")), "set_stat_components", "get_stat_components");

    ADD_SIGNAL(MethodInfo("stat_added", PropertyInfo(Variant::OBJECT, "added_stat")));
    ADD_SIGNAL(MethodInfo("stat_removed", PropertyInfo(Variant::OBJECT, "removed_stat")));
}

void StatContainer::invoke_component_method(ComponentEvent event, const Ref<Stat> stat)
{
    for (int64_t i = 0; i < container_components.size(); i++)
    {
        Ref<StatContainerComponent> component = container_components[i];
        if (component.is_valid())
        {
            switch (event)
            {
            case ComponentEvent::CONTAINER_READY:
                component->on_container_ready(this);
                break;
            case ComponentEvent::STAT_ADDED:
                component->on_stat_added(this, stat);
                break;
            case ComponentEvent::STAT_REMOVED:
                component->on_stat_removed(this, stat);
                break;
            }
        }
    }
}