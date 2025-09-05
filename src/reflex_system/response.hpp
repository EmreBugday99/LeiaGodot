#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "reflex_types.hpp"
#include <godot_cpp/core/gdvirtual.gen.inc>

using namespace godot;
class Response : public Resource
{
    GDCLASS(Response, Resource);

public:
    Response();
    virtual ~Response();

    virtual void on_execute(Reflex* reflex);

    GDVIRTUAL1_REQUIRED(on_execute, Reflex*);

    static void _bind_methods();
};
#endif // RESPONSE_HPP