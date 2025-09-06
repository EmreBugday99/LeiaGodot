#ifndef ITEM_OBJECT_HPP
#define ITEM_OBJECT_HPP

#include <godot_cpp/classes/ref_counted.hpp>

using namespace godot;

// Forward declarations - actual includes handled by inventory_system.hpp
class ItemResource;
class ItemObject : public RefCounted
{
    GDCLASS(ItemObject, RefCounted);

public:
    ItemObject();
    ~ItemObject();

    int get_quantity() const;
    void set_quantity(int new_quantity);

    Ref<ItemResource> get_item_resource() const;
    void set_item_resource(const Ref<ItemResource>& new_resource);

    static void _bind_methods();

private:
    int quantity;
    Ref<ItemResource> item_resource;
};

#endif // ITEM_OBJECT_HPP