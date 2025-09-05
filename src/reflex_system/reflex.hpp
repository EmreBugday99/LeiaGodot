#ifndef REFLEX_HPP
#define REFLEX_HPP

#include "reflex_types.hpp"

using namespace godot;
class Reflex : public Node
{
    GDCLASS(Reflex, Node);

public:
    Reflex();
    ~Reflex();

    void _ready() override;
    void trigger_reflex();

    void set_stimulus(const Ref<Stimulus> new_stimulus);
    Ref<Stimulus> get_stimulus() const;
    void set_responses(const TypedArray<Response> new_responses);
    TypedArray<Response> get_responses() const;

    static void _bind_methods();

private:
    bool is_initialized;
    Ref<Stimulus> stimulus;
    TypedArray<Response> responses;
};

#endif // REFLEX_HPP