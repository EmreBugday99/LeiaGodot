#ifndef ITEM_EXTENSION_HPP
#define ITEM_EXTENSION_HPP

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/gdvirtual.gen.inc>

using namespace godot;

// Forward declarations - actual includes handled by inventory_system.hpp
class ItemResource;
class ItemObject;

class ItemExtension : public Resource
{
    GDCLASS(ItemExtension, Resource);

private:
    String extension_name;

public:
    ItemExtension();
    virtual ~ItemExtension();

    String get_extension_name() const;
    void set_extension_name(const String& new_name);

    GDVIRTUAL2(on_item_used, Ref<ItemResource>, Ref<ItemObject>);
    GDVIRTUAL2(on_item_picked_up, Ref<ItemResource>, Ref<ItemObject>);
    GDVIRTUAL2(on_item_dropped, Ref<ItemResource>, Ref<ItemObject>);

    virtual void on_item_used(Ref<ItemResource> item_resource, Ref<ItemObject> item_object);
    virtual void on_item_picked_up(Ref<ItemResource> item_resource, Ref<ItemObject> item_object);
    virtual void on_item_dropped(Ref<ItemResource> item_resource, Ref<ItemObject> item_object);

    static void _bind_methods();
};

#endif // ITEM_EXTENSION_HPP