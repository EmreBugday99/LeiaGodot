#ifndef INVENTORY_NODE_HPP
#define INVENTORY_NODE_HPP

#include <godot_cpp/classes/node.hpp>
#include "inventory_system.hpp"

class StatContainer;
using namespace godot;

enum class InventoryValidationResult {
    SUCCESS,
    NULL_ITEM,
    NO_STAT_CONTAINER,
    MISSING_WEIGHT_STATS,
    INVALID_ITEM_RESOURCE,
    EXCEEDS_WEIGHT_LIMIT
};

class InventoryNode : public Node
{
    GDCLASS(InventoryNode, Node);

private:
    TypedArray<ItemObject> items;
    String current_weight_stat_identifier;
    String max_weight_stat_identifier;
    StatContainer* cached_stat_container;

public:
    InventoryNode();
    ~InventoryNode();
    void _ready() override;

    TypedArray<ItemObject> get_items() const;
    bool can_add_item(const Ref<ItemObject>& item) const;
    InventoryValidationResult can_add_item_detailed(const Ref<ItemObject>& item) const;
    bool add_item(const Ref<ItemObject>& item);
    bool remove_item(const Ref<ItemObject>& item);
    void clear_inventory();

    static void _bind_methods();

private:
    // Stacking helper methods
    Ref<ItemObject> find_stackable_item(const Ref<ItemResource>& resource);
    bool try_stack_with_existing(const Ref<ItemObject>& new_item);
};

#endif // INVENTORY_NODE_HPP