#include "inventory_system.hpp"
#include "../helper_macros.hpp"

ItemResource::ItemResource()
{
    item_name = "New ItemResource";
    description = "ItemResource Description";
    max_stack_size = 1;
    is_stackable = false;
    weight = 0;
}

ItemResource::~ItemResource()
{
}

String ItemResource::get_item_name() const
{
    return item_name;
}

void ItemResource::set_item_name(const String& new_name)
{
    item_name = new_name;
}

String ItemResource::get_description() const
{
    return description;
}

void ItemResource::set_description(const String& new_description)
{
    description = new_description;
}

int ItemResource::get_max_stack_size() const
{
    return max_stack_size;
}

void ItemResource::set_max_stack_size(int new_size)
{
    max_stack_size = new_size;
}

bool ItemResource::get_is_stackable() const
{
    return is_stackable;
}

void ItemResource::set_is_stackable(bool stackable)
{
    is_stackable = stackable;
}

int ItemResource::get_weight() const
{
    return weight;
}

void ItemResource::set_weight(int new_weight)
{
    weight = new_weight;
}

TypedArray<ItemExtension> ItemResource::get_extensions() const
{
    return extensions;
}

void ItemResource::set_extensions(TypedArray<ItemExtension> new_extensions)
{
    extensions = new_extensions;
}

void ItemResource::add_extension(const Ref<ItemExtension> extension)
{
    extensions.append(extension);
}

void ItemResource::remove_extension(const Ref<ItemExtension> extension)
{
    extensions.erase(extension);
}

void ItemResource::on_item_used(Ref<ItemObject> item_object)
{
    for (size_t i = 0; i < extensions.size(); i++)
    {
        Ref<ItemExtension> iterated_extension = extensions[i];
        if (iterated_extension.is_null())
            continue;

        iterated_extension->on_item_used(Ref<ItemResource>(this), item_object);
    }
}

void ItemResource::on_item_picked_up(Ref<ItemObject> item_object)
{
    for (size_t i = 0; i < extensions.size(); i++)
    {
        Ref<ItemExtension> iterated_extension = extensions[i];
        if (iterated_extension.is_null())
            continue;

        iterated_extension->on_item_picked_up(Ref<ItemResource>(this), item_object);
    }
}

void ItemResource::on_item_dropped(Ref<ItemObject> item_object)
{
    for (size_t i = 0; i < extensions.size(); i++)
    {
        Ref<ItemExtension> iterated_extension = extensions[i];
        if (iterated_extension.is_null())
            continue;

        iterated_extension->on_item_dropped(Ref<ItemResource>(this), item_object);
    }
}

void ItemResource::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_item_name"), &ItemResource::get_item_name);
    ClassDB::bind_method(D_METHOD("set_item_name", "new_name"), &ItemResource::set_item_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "item_name"), "set_item_name", "get_item_name");

    ClassDB::bind_method(D_METHOD("get_description"), &ItemResource::get_description);
    ClassDB::bind_method(D_METHOD("set_description", "new_description"), &ItemResource::set_description);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "description"), "set_description", "get_description");

    ClassDB::bind_method(D_METHOD("get_max_stack_size"), &ItemResource::get_max_stack_size);
    ClassDB::bind_method(D_METHOD("set_max_stack_size", "new_size"), &ItemResource::set_max_stack_size);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "max_stack_size"), "set_max_stack_size", "get_max_stack_size");

    ClassDB::bind_method(D_METHOD("get_is_stackable"), &ItemResource::get_is_stackable);
    ClassDB::bind_method(D_METHOD("set_is_stackable", "stackable"), &ItemResource::set_is_stackable);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_stackable"), "set_is_stackable", "get_is_stackable");

    ClassDB::bind_method(D_METHOD("get_weight"), &ItemResource::get_weight);
    ClassDB::bind_method(D_METHOD("set_weight", "new_weight"), &ItemResource::set_weight);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "weight"), "set_weight", "get_weight");

    ClassDB::bind_method(D_METHOD("get_extensions"), &ItemResource::get_extensions);
    ClassDB::bind_method(D_METHOD("set_extensions", "new_extensions"), &ItemResource::set_extensions);
    ClassDB::bind_method(D_METHOD("add_extension", "extension"), &ItemResource::add_extension);
    ClassDB::bind_method(D_METHOD("remove_extension", "extension"), &ItemResource::remove_extension);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "extensions", PROPERTY_HINT_ARRAY_TYPE, LEIA_MAKE_RESOURCE_TYPE_HINT("ItemExtension")), "set_extensions", "get_extensions");

    ClassDB::bind_method(D_METHOD("on_item_used", "item_object"), &ItemResource::on_item_used);
    ClassDB::bind_method(D_METHOD("on_item_picked_up", "item_object"), &ItemResource::on_item_picked_up);
    ClassDB::bind_method(D_METHOD("on_item_dropped", "item_object"), &ItemResource::on_item_dropped);


}