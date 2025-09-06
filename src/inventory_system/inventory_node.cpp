#include "inventory_node.hpp"
#include "../stat_system/stat_container.hpp"
#include "../stat_system/stat.hpp"

// Forward declaration
StatContainer* find_stat_container(Node* starting_node);

InventoryNode::InventoryNode()
{
    current_weight_stat_identifier = "inventory.weight.current";
    max_weight_stat_identifier = "inventory.weight.max";
    cached_stat_container = nullptr;
}

InventoryNode::~InventoryNode()
{}

void InventoryNode::_ready()
{
    cached_stat_container = find_stat_container(get_parent());
    if (!cached_stat_container)
    {
        UtilityFunctions::push_error("InventoryNode could not find a StatContainer in its parent nodes.");
        return;
    }

    Ref<Stat> current_weight_stat = Ref<Stat>(memnew(Stat));
    current_weight_stat->set_stat_tag(current_weight_stat_identifier);
    current_weight_stat->set_base_value(0.0f);
    cached_stat_container->add_stat(current_weight_stat);

    Ref<Stat> max_weight_stat = Ref<Stat>(memnew(Stat));
    max_weight_stat->set_stat_tag(max_weight_stat_identifier);
    max_weight_stat->set_base_value(100.0f); // Default max weight,
    cached_stat_container->add_stat(max_weight_stat);
}

TypedArray<ItemObject> InventoryNode::get_items() const
{
    return items;
}

InventoryValidationResult InventoryNode::can_add_item_detailed(const Ref<ItemObject>& item) const
{
    if (item.is_null())
        return InventoryValidationResult::NULL_ITEM;
    
    if (!cached_stat_container)
        return InventoryValidationResult::NO_STAT_CONTAINER;

    Ref<Stat> current_weight_stat = cached_stat_container->find_stat(current_weight_stat_identifier);
    Ref<Stat> max_weight_stat = cached_stat_container->find_stat(max_weight_stat_identifier);
    if (current_weight_stat.is_null() || max_weight_stat.is_null())
        return InventoryValidationResult::MISSING_WEIGHT_STATS;

    Ref<ItemResource> item_resource = item->get_item_resource();
    if (item_resource.is_null())
        return InventoryValidationResult::INVALID_ITEM_RESOURCE;

    float item_weight = item_resource->get_weight() * item->get_quantity();
    float new_total_weight = current_weight_stat->get_value() + item_weight;
    if (new_total_weight > max_weight_stat->get_value())
        return InventoryValidationResult::EXCEEDS_WEIGHT_LIMIT;
    
    return InventoryValidationResult::SUCCESS;
}

bool InventoryNode::can_add_item(const Ref<ItemObject>& item) const
{
    return can_add_item_detailed(item) == InventoryValidationResult::SUCCESS;
}

bool InventoryNode::add_item(const Ref<ItemObject>& item)
{
    // First try to stack with existing items if the resource is stackable
    if (item.is_valid() && item->get_item_resource().is_valid() && 
        item->get_item_resource()->get_is_stackable())
    {
        if (try_stack_with_existing(item))
            return true;
    }

    // If stacking didn't work or item isn't stackable, validate adding as new item
    InventoryValidationResult validation_result = can_add_item_detailed(item);
    
    // Handle validation errors with appropriate error messages
    switch (validation_result)
    {
        case InventoryValidationResult::NULL_ITEM:
            return false;
        case InventoryValidationResult::NO_STAT_CONTAINER:
            UtilityFunctions::push_error("InventoryNode could not find a StatContainer in its parent nodes.");
            return false;
        case InventoryValidationResult::MISSING_WEIGHT_STATS:
            UtilityFunctions::push_error("InventoryNode could not find required weight stats in the StatContainer.");
            return false;
        case InventoryValidationResult::INVALID_ITEM_RESOURCE:
            UtilityFunctions::push_error("ItemObject does not have a valid ItemResource.");
            return false;
        case InventoryValidationResult::EXCEEDS_WEIGHT_LIMIT:
            return false;
        case InventoryValidationResult::SUCCESS:
            break;
    }

    // If validation passed, proceed with adding the item
    Ref<Stat> current_weight_stat = cached_stat_container->find_stat(current_weight_stat_identifier);
    Ref<ItemResource> item_resource = item->get_item_resource();
    
    float item_weight = item_resource->get_weight() * item->get_quantity();
    float new_total_weight = current_weight_stat->get_value() + item_weight;
    
    items.append(item);
    current_weight_stat->set_base_value(new_total_weight);
    return true;
}

bool InventoryNode::remove_item(const Ref<ItemObject>& item)
{
    if (item.is_null())
        return false;
    
    int item_index = items.find(item);
    if (item_index == -1)
        return false; // Item not found in inventory
    
    if (!cached_stat_container)
    {
        UtilityFunctions::push_error("InventoryNode could not find a StatContainer in its parent nodes.");
        return false;
    }

    Ref<Stat> current_weight_stat = cached_stat_container->find_stat(current_weight_stat_identifier);
    if (current_weight_stat.is_null())
    {
        UtilityFunctions::push_error("InventoryNode could not find current weight stat in the StatContainer.");
        return false;
    }

    Ref<ItemResource> item_resource = item->get_item_resource();
    if (item_resource.is_null())
    {
        UtilityFunctions::push_error("ItemObject does not have a valid ItemResource.");
        return false;
    }

    float item_weight = item_resource->get_weight() * item->get_quantity();
    float new_total_weight = current_weight_stat->get_value() - item_weight;
    
    items.remove_at(item_index);
    current_weight_stat->set_base_value(new_total_weight);
    return true;
}

void InventoryNode::clear_inventory()
{
    items.clear();
}

void InventoryNode::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_items"), &InventoryNode::get_items);
    ClassDB::bind_method(D_METHOD("can_add_item"), &InventoryNode::can_add_item);
    ClassDB::bind_method(D_METHOD("add_item"), &InventoryNode::add_item);
    ClassDB::bind_method(D_METHOD("remove_item"), &InventoryNode::remove_item);
    ClassDB::bind_method(D_METHOD("clear_inventory"), &InventoryNode::clear_inventory);
}

// Stacking helper method implementations
Ref<ItemObject> InventoryNode::find_stackable_item(const Ref<ItemResource>& resource)
{
    for (size_t i = 0; i < items.size(); i++)
    {
        Ref<ItemObject> existing_item = items[i];
        if (existing_item.is_null() || existing_item->get_item_resource().is_null())
            continue;
            
        Ref<ItemResource> existing_resource = existing_item->get_item_resource();
        
        // Check if it's the same resource and can be stacked
        if (existing_resource == resource && 
            existing_resource->get_is_stackable() &&
            existing_item->get_quantity() < existing_resource->get_max_stack_size())
        {
            return existing_item;
        }
    }
    return Ref<ItemObject>(nullptr);
}

bool InventoryNode::try_stack_with_existing(const Ref<ItemObject>& new_item)
{
    if (new_item.is_null() || new_item->get_item_resource().is_null())
        return false;
        
    Ref<ItemResource> resource = new_item->get_item_resource();
    Ref<ItemObject> existing_item = find_stackable_item(resource);
    
    if (existing_item.is_null())
        return false;
    
    int max_stack = resource->get_max_stack_size();
    int current_quantity = existing_item->get_quantity();
    int new_quantity = new_item->get_quantity();
    int available_space = max_stack - current_quantity;
    
    if (available_space <= 0)
        return false;
    
    // Check if the entire new item quantity can fit in the stack
    if (new_quantity > available_space)
        return false;
    
    // Check if adding the full new item weight would exceed weight limit
    float weight_to_add = resource->get_weight() * new_quantity;
    
    if (cached_stat_container)
    {
        Ref<Stat> current_weight_stat = cached_stat_container->find_stat(current_weight_stat_identifier);
        Ref<Stat> max_weight_stat = cached_stat_container->find_stat(max_weight_stat_identifier);
        
        if (current_weight_stat.is_valid() && max_weight_stat.is_valid())
        {
            float new_total_weight = current_weight_stat->get_value() + weight_to_add;
            if (new_total_weight > max_weight_stat->get_value())
                return false;
        }
    }
    
    // Stack the entire new item quantity
    existing_item->set_quantity(current_quantity + new_quantity);
    
    // Update weight
    if (cached_stat_container)
    {
        Ref<Stat> current_weight_stat = cached_stat_container->find_stat(current_weight_stat_identifier);
        if (current_weight_stat.is_valid())
        {
            current_weight_stat->set_base_value(current_weight_stat->get_value() + weight_to_add);
        }
    }
    
    // Successfully stacked the entire item
    return true;
}

StatContainer* find_stat_container(Node* starting_node)
{
    if (!starting_node)
        return nullptr;

    TypedArray<Node> children = starting_node->get_children();
    for (size_t i = 0; i < children.size(); i++)
    {
        StatContainer* stat_container = Object::cast_to<StatContainer>(children[i]);
        if (stat_container)
            return stat_container;
    }

    return nullptr;
}