#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/thread.hpp>

namespace godot {

class Shell : public Node {
    GDCLASS(Shell, Node)

private:
    Ref<Thread> shell_thread = nullptr;
    pid_t pid = -1;
    int master_fd = -1;

    void _slave();
    void _master();
    void _shell_process();

protected:
    static void _bind_methods();
    void _notification(int p_what);

public:
    void _ready() override;
    

    void push_command(String command);
    // void read
};

}