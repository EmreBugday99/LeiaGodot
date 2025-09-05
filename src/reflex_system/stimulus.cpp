#include "reflex.hpp"  // Include this first to get complete Reflex definition
#include "stimulus.hpp"

Stimulus::Stimulus()
{
}

Stimulus::~Stimulus()
{
}

void Stimulus::initialize(Reflex* owner)
{
    if (GDVIRTUAL_IS_OVERRIDDEN(initialize))
        GDVIRTUAL_CALL(initialize, owner);
}

bool Stimulus::can_stimulate(Reflex* reflex)
{
    if (GDVIRTUAL_IS_OVERRIDDEN(can_stimulate)) {
        bool result = false;
        GDVIRTUAL_CALL(can_stimulate, reflex, result);
        return result;
    }

    return true;
}

void Stimulus::_bind_methods()
{
    GDVIRTUAL_BIND(initialize, "reflex");
    GDVIRTUAL_BIND(can_stimulate, "reflex");
}