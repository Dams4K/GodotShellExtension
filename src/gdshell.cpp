#include "gdshell.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void GDShell::_bind_methods() {

}

GDShell::GDShell() {
    shell_rtlabel = memnew(RichTextLabel);
    shell_rtlabel->set_v_size_flags(SIZE_EXPAND_FILL);
    shell_rtlabel->set_scroll_follow(true);
    shell_rtlabel->set_custom_minimum_size(Vector2(0, 64));
    add_child(shell_rtlabel);

    command_ledit = memnew(LineEdit);
    command_ledit->set_keep_editing_on_text_submit(true);
    add_child(command_ledit);
}

GDShell::~GDShell() {
    
}