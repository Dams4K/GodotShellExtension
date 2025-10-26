#include "shell.h"

#include <pty.h>
#include <unistd.h>
#include <sys/wait.h>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#define BUFFER_SIZE 4096

using namespace godot;

void Shell::_bind_methods() {
    ClassDB::bind_method(D_METHOD("push_command", "command"), &Shell::push_command);
}

void Shell::_slave() {
    execlp("bash", "bash", "-i", NULL);
}

void Shell::_master() {
    char buffer[BUFFER_SIZE];

    while (true) {
        // -1 for the \0
        ssize_t n = read(master_fd, buffer, sizeof(char)*(BUFFER_SIZE-1));
        if (n > 0) {
            buffer[n] = '\n';
            print_line(String(buffer));
        }
    }

    close(master_fd);
    waitpid(pid, NULL, 0);
}

void Shell::_shell_process() {
    pid = forkpty(&master_fd, NULL, NULL, NULL);
    if (pid == 0) {
        _slave();
    } else {
        _master();
    }
}

void Shell::push_command(String command) {
    ERR_FAIL_COND_EDMSG(master_fd == -1, "master_fd equal -1");

    CharString utf8_cmd = command.utf8();
    const char *cmd_data = utf8_cmd.get_data();
    size_t cmd_length = strlen(cmd_data);

    ssize_t n = write(master_fd, cmd_data, cmd_length);
    ERR_FAIL_COND_EDMSG(n != cmd_length, "Not all of the command was written");
}

void Shell::_ready() {
    shell_thread.instantiate();
    shell_thread->start(callable_mp(this, &Shell::_shell_process));
}

void Shell::_notification(int p_what) {
    switch (p_what) {
    case NOTIFICATION_EXIT_TREE:
        print_line("Exit tree");
        if (shell_thread.is_valid()) {
            if (shell_thread->is_started() && shell_thread->is_alive()) {
                shell_thread->wait_to_finish();
            }
            shell_thread.unref();
        }
        break;
    
    default:
        break;
    }

}