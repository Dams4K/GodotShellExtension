#include "register_types.h"

#include <gdextension_interface.h>

#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "gdshell.h"
#include "gdshell_editor_plugin.h"

using namespace godot;

void initialize_gdshell_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_EDITOR) {
		return;
	}

	GDREGISTER_INTERNAL_CLASS(GDShell);
	GDREGISTER_INTERNAL_CLASS(GDShellEditorPlugin);

	EditorPlugins::add_by_type<GDShellEditorPlugin>();
}

void uninitialize_gdshell_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_EDITOR) {
		return;
	}

	EditorPlugins::remove_by_type<GDShellEditorPlugin>();
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT gdshell_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(initialize_gdshell_module);
	init_obj.register_terminator(uninitialize_gdshell_module);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}