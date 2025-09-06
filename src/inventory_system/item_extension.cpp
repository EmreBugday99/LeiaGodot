#include "inventory_system.hpp"

ItemExtension::ItemExtension()
{
    extension_name = "New Extension";
}

ItemExtension::~ItemExtension()
{
}

String ItemExtension::get_extension_name() const
{
    return extension_name;
}

void ItemExtension::set_extension_name(const String& new_name)
{
    extension_name = new_name;
}

void ItemExtension::on_item_used(Ref<ItemResource> item_resource, Ref<ItemObject> item_object)
{
    if (GDVIRTUAL_IS_OVERRIDDEN(on_item_used)) {
        GDVIRTUAL_CALL(on_item_used, item_resource, item_object);
    }
}

void ItemExtension::on_item_picked_up(Ref<ItemResource> item_resource, Ref<ItemObject> item_object)
{
    if (GDVIRTUAL_IS_OVERRIDDEN(on_item_picked_up)) {
        GDVIRTUAL_CALL(on_item_picked_up, item_resource, item_object);
    }
}

void ItemExtension::on_item_dropped(Ref<ItemResource> item_resource, Ref<ItemObject> item_object)
{
    if (GDVIRTUAL_IS_OVERRIDDEN(on_item_dropped)) {
        GDVIRTUAL_CALL(on_item_dropped, item_resource, item_object);
    }
}

void ItemExtension::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_extension_name"), &ItemExtension::get_extension_name);
    ClassDB::bind_method(D_METHOD("set_extension_name", "new_name"), &ItemExtension::set_extension_name);

    ADD_PROPERTY(PropertyInfo(Variant::STRING, "extension_name"), "set_extension_name", "get_extension_name");

    // Bind the virtual methods for GDScript
    GDVIRTUAL_BIND(on_item_used, "item_resource", "item_object");
    GDVIRTUAL_BIND(on_item_picked_up, "item_resource", "item_object");
    GDVIRTUAL_BIND(on_item_dropped, "item_resource", "item_object");
}