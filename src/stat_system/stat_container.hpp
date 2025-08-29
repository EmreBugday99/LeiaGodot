#ifndef STAT_CONTAINER_HPP
#define STAT_CONTAINER_HPP

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/typed_array.hpp>

using namespace godot;
class Stat;
class StatContainerComponent;

class StatContainer : public Node
{
    GDCLASS(StatContainer, Node);

private:
    enum class ComponentEvent
    {
        CONTAINER_READY,
        STAT_ADDED,
        STAT_REMOVED
    };

    Vector<Ref<Stat>> contained_stats;
    TypedArray<StatContainerComponent> container_components;

public:
    StatContainer();
    ~StatContainer();

    void on_ready(); // Called when the container is ready

    bool add_stat(const Ref<Stat> stat_to_add);
    bool remove_stat(const String& stat_identifier);
    void remove_all_stats();
    Ref<Stat> find_stat(const String& stat_identifier);

    TypedArray<StatContainerComponent> get_stat_components() const;
    void set_stat_components(const TypedArray<StatContainerComponent> components);

    static void _bind_methods();

    // Helper method to invoke component methods (not exposed to GDScript)
    void invoke_component_method(ComponentEvent event, const Ref<Stat> stat = Ref<Stat>());
};

#endif // STAT_CONTAINER_HPP