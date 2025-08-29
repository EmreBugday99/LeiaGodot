#include "stat_container_component.hpp"


StatContainerComponent::StatContainerComponent() {}
StatContainerComponent::~StatContainerComponent() {}

void StatContainerComponent::on_container_ready(StatContainer* container)
{
    if (GDVIRTUAL_IS_OVERRIDDEN(on_container_ready))
        GDVIRTUAL_CALL(on_container_ready, container);
}

void StatContainerComponent::on_stat_added(StatContainer* container, const Ref<Stat> stat)
{
    if (GDVIRTUAL_IS_OVERRIDDEN(on_stat_added))
        GDVIRTUAL_CALL(on_stat_added, container, stat);
}

void StatContainerComponent::on_stat_removed(StatContainer* container, const Ref<Stat> stat)
{
    if (GDVIRTUAL_IS_OVERRIDDEN(on_stat_removed))
        GDVIRTUAL_CALL(on_stat_removed, container, stat);
}

void StatContainerComponent::_bind_methods()
{
    GDVIRTUAL_BIND(on_container_ready, "container");
    GDVIRTUAL_BIND(on_stat_added, "container", "stat");
    GDVIRTUAL_BIND(on_stat_removed, "container", "stat");
}