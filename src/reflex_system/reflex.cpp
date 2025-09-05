#include "reflex.hpp"
#include "stimulus.hpp"
#include "response.hpp"
#include "../helper_macros.hpp"

Reflex::Reflex()
{
    is_initialized = false;
}

Reflex::~Reflex()
{
}

void Reflex::_ready()
{
    if (!stimulus.is_null())
        stimulus->initialize(this);

    is_initialized = true;
}

void Reflex::trigger_reflex()
{
    if (stimulus.is_null() || stimulus->can_stimulate(this) == false)
        return;

    for (size_t i = 0; i < responses.size(); i++)
    {
        Ref<Response> response = responses[i];
        if (response.is_null())
            continue;

        response->on_execute(this);
    }
}

void Reflex::set_stimulus(const Ref<Stimulus> new_stimulus)
{
    if (new_stimulus.is_null())
        return;

    stimulus = new_stimulus;
    if (is_initialized)
        stimulus->initialize(this);
}

Ref<Stimulus> Reflex::get_stimulus() const
{
    return stimulus;
}

void Reflex::set_responses(const TypedArray<Response> new_responses)
{
    responses = new_responses;
}

TypedArray<Response> Reflex::get_responses() const
{
    return responses;
}

void Reflex::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("trigger_reflex"), &Reflex::trigger_reflex);
    ClassDB::bind_method(D_METHOD("set_stimulus", "stimulus"), &Reflex::set_stimulus);
    ClassDB::bind_method(D_METHOD("get_stimulus"), &Reflex::get_stimulus);
    ClassDB::bind_method(D_METHOD("set_responses", "responses"), &Reflex::set_responses);
    ClassDB::bind_method(D_METHOD("get_responses"), &Reflex::get_responses);

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "stimulus", PROPERTY_HINT_RESOURCE_TYPE, "Stimulus"), "set_stimulus", "get_stimulus");
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "responses", PROPERTY_HINT_ARRAY_TYPE, LEIA_MAKE_RESOURCE_TYPE_HINT("Response")), "set_responses", "get_responses");
}