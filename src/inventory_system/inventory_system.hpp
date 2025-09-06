#ifndef INVENTORY_SYSTEM_HPP
#define INVENTORY_SYSTEM_HPP

// This header includes all inventory system classes in the correct order
// to resolve circular dependencies. All other files should include this
// header instead of individual class headers.

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/core/gdvirtual.gen.inc>

using namespace godot;

// Forward declare all classes first
class ItemResource;
class ItemObject;
class ItemExtension;

// Include class headers - the order doesn't matter much since we use forward declarations
// but we'll include them in logical order: resource -> object -> extension
#include "item_resource.hpp"
#include "item_object.hpp"
#include "item_extension.hpp"

#endif // INVENTORY_SYSTEM_HPP
