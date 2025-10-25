#pragma once

#include <godot_cpp/classes/editor_plugin.hpp>
#include "gdshell.h"

namespace godot {

class GDShellEditorPlugin : public EditorPlugin {
    GDCLASS(GDShellEditorPlugin, EditorPlugin)
private:
    GDShell *shell_dock = nullptr;

protected:
    static void _bind_methods();

public:
    GDShellEditorPlugin();
    ~GDShellEditorPlugin();

    virtual void _enter_tree() override;
    virtual void _exit_tree() override;
};

}