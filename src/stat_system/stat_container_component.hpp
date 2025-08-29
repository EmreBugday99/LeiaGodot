#ifndef STAT_COMPONENT_HPP
#define STAT_COMPONENT_HPP

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/gdvirtual.gen.inc>
#include "stat.hpp"
#include "stat_container.hpp"

using namespace godot;

class StatContainerComponent : public Resource
{
    GDCLASS(StatContainerComponent, Resource);

public:
    StatContainerComponent();
    virtual ~StatContainerComponent();

    virtual void on_container_ready(StatContainer* container);
    virtual void on_stat_added(StatContainer* container, const Ref<Stat> stat);
    virtual void on_stat_removed(StatContainer* container, const Ref<Stat> stat);

    GDVIRTUAL1(on_container_ready, StatContainer*);
    GDVIRTUAL2(on_stat_added, StatContainer*, Ref<Stat>);
    GDVIRTUAL2(on_stat_removed, StatContainer*, Ref<Stat>);

    static void _bind_methods();
};

#endif // STAT_COMPONENT_HPP