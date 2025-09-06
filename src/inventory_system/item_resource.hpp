#ifndef ITEM_RESOURCE_HPP
#define ITEM_RESOURCE_HPP

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/typed_array.hpp>

using namespace godot;

// Forward declarations - actual includes handled by inventory_system.hpp
class ItemExtension;
class ItemObject;
class ItemResource : public Resource
{
    GDCLASS(ItemResource, Resource);

private:
    String item_name;
    String description;
    int max_stack_size;
    bool is_stackable;
    int weight;
    TypedArray<ItemExtension> extensions;

public:
    ItemResource();
    ~ItemResource();

    String get_item_name() const;
    void set_item_name(const String& new_name);

    String get_description() const;
    void set_description(const String& new_desc);

    int get_max_stack_size() const;
    void set_max_stack_size(int new_size);

    bool get_is_stackable() const;
    void set_is_stackable(bool stackable);

    int get_weight() const;
    void set_weight(int new_weight);

    TypedArray<ItemExtension> get_extensions() const;
    void set_extensions(TypedArray<ItemExtension> new_extensions);
    void add_extension(const Ref<ItemExtension> extension);
    void remove_extension(const Ref<ItemExtension> extension);

    void on_item_used(Ref<ItemObject> item_object);
    void on_item_picked_up(Ref<ItemObject> item_object);
    void on_item_dropped(Ref<ItemObject> item_object);

    static void _bind_methods();
};

#endif // ITEM_RESOURCE_HPP