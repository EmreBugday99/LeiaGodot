#ifndef STIMULUS_HPP
#define STIMULUS_HPP

#include "reflex_types.hpp"
#include <godot_cpp/core/gdvirtual.gen.inc>

using namespace godot;
class Stimulus : public Resource
{
    GDCLASS(Stimulus, Resource);

public:
    Stimulus();
    virtual ~Stimulus();

    virtual void initialize(Reflex* reflex);
    virtual void deinitialize(Reflex* reflex);
    virtual bool can_stimulate(Reflex* reflex);

    GDVIRTUAL1_REQUIRED(initialize, Reflex*);
    GDVIRTUAL1_REQUIRED(deinitialize, Reflex*);
    GDVIRTUAL1R_REQUIRED(bool, can_stimulate, Reflex*);

    static void _bind_methods();
};
#endif // STIMULUS_HPP