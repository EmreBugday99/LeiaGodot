#include "inventory_system.hpp"
#include "../helper_macros.hpp"

ItemObject::ItemObject()
{
    quantity = 1;
    item_resource = Ref<ItemResource>(nullptr);
}

ItemObject::~ItemObject()
{
}

int ItemObject::get_quantity() const
{
    return quantity;
}

void ItemObject::set_quantity(int new_quantity)
{
    quantity = new_quantity;
}

Ref<ItemResource> ItemObject::get_item_resource() const
{
    return item_resource;
}

void ItemObject::set_item_resource(const Ref<ItemResource>& new_resource)
{
    item_resource = new_resource;
}

void ItemObject::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_quantity"), &ItemObject::get_quantity);
    ClassDB::bind_method(D_METHOD("set_quantity", "new_quantity"), &ItemObject::set_quantity);
    ClassDB::bind_method(D_METHOD("get_item_resource"), &ItemObject::get_item_resource);
    ClassDB::bind_method(D_METHOD("set_item_resource", "new_resource"), &ItemObject::set_item_resource);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "quantity"), "set_quantity", "get_quantity");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "item_resource", PROPERTY_HINT_RESOURCE_TYPE, LEIA_MAKE_RESOURCE_TYPE_HINT("ItemResource")), "set_item_resource", "get_item_resource");
}