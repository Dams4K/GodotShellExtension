#pragma once

#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/rich_text_label.hpp>
#include <godot_cpp/classes/line_edit.hpp>

#include "shell.h"

namespace godot {

class GDShell : public VBoxContainer {
    GDCLASS(GDShell, VBoxContainer)

private:
    Shell *shell = nullptr;
    RichTextLabel *shell_rtlabel = nullptr;
    LineEdit *command_ledit = nullptr;

    void _on_command_submitted(String command);

protected:
    static void _bind_methods();

public:
    GDShell();
    ~GDShell();
};

}