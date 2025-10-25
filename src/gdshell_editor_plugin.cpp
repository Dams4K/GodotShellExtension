#include "gdshell_editor_plugin.h"

#include <godot_cpp/classes/editor_interface.hpp>

using namespace godot;

void GDShellEditorPlugin::_bind_methods() {

}

GDShellEditorPlugin::GDShellEditorPlugin() {

}

GDShellEditorPlugin::~GDShellEditorPlugin() {
    
}


void GDShellEditorPlugin::_enter_tree() {
    shell_dock = memnew(GDShell);
    add_control_to_bottom_panel(shell_dock, "Shell");
}

void GDShellEditorPlugin::_exit_tree() {
    if (shell_dock != nullptr) {
        remove_control_from_bottom_panel(shell_dock);
        memdelete(shell_dock);
        shell_dock = nullptr;
    }
}
