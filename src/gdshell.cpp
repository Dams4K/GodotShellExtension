#include "gdshell.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void GDShell::_bind_methods() {
}

void GDShell::_on_command_submitted(String command) {
    command_ledit->clear();
    shell->push_command(command);
}

GDShell::GDShell() {
    shell = memnew(Shell);

    shell_rtlabel = memnew(RichTextLabel);
    shell_rtlabel->set_v_size_flags(SIZE_EXPAND_FILL);
    shell_rtlabel->set_scroll_follow(true);
    shell_rtlabel->set_custom_minimum_size(Vector2(0, 64));
    add_child(shell_rtlabel);

    command_ledit = memnew(LineEdit);
    command_ledit->set_keep_editing_on_text_submit(true);
    command_ledit->connect("text_submitted", callable_mp(this, &GDShell::_on_command_submitted));
    add_child(command_ledit);
}

GDShell::~GDShell() {
    
}