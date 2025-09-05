#include "reflex.hpp"  // Include this first to get complete Reflex definition
#include "response.hpp"

Response::Response()
{
}

Response::~Response()
{
}

void Response::on_execute(Reflex* reflex)
{
    if (GDVIRTUAL_IS_OVERRIDDEN(on_execute))
        GDVIRTUAL_CALL(on_execute, reflex);
}

void Response::_bind_methods()
{
    GDVIRTUAL_BIND(on_execute, "reflex");
}