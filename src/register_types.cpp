#include "register_types.hpp"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "tag_system/tag_container.hpp"
#include "stat_system/stat_modifier.hpp"
#include "stat_system/stat.hpp"
#include "stat_system/stat_container.hpp"
#include "stat_system/stat_container_component.hpp"
#include "reflex_system/reflex.hpp"
#include "reflex_system/stimulus.hpp"
#include "reflex_system/response.hpp"
#include "inventory_system/inventory_system.hpp"

using namespace godot;

void initialize_leia_module(ModuleInitializationLevel p_level)
{
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
        return;

    GDREGISTER_CLASS(TagContainer);
    
    GDREGISTER_CLASS(Stat);
    GDREGISTER_CLASS(StatContainer);
    GDREGISTER_CLASS(StatModifier);
    GDREGISTER_VIRTUAL_CLASS(StatContainerComponent);

    GDREGISTER_CLASS(Reflex);
    GDREGISTER_VIRTUAL_CLASS(Response);
    GDREGISTER_VIRTUAL_CLASS(Stimulus);

    GDREGISTER_CLASS(ItemResource);
    GDREGISTER_CLASS(ItemObject);
    GDREGISTER_VIRTUAL_CLASS(ItemExtension);
}

void uninitialize_leia_module(ModuleInitializationLevel p_level)
{
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
        return;
}

extern "C"
{
    // Initialization.
    GDExtensionBool GDE_EXPORT leia_module_entry_point(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization* r_initialization)
    {
        godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

        init_obj.register_initializer(initialize_leia_module);
        init_obj.register_terminator(uninitialize_leia_module);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}