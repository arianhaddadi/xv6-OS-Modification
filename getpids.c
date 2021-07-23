#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{
    int pid = fork();
    if(pid == 0) {
        if (fork() == 0) {
            if (fork() == 0) {
                set_sleep(4);
                printf(1, "parent of grand grand son pid: %d\n", get_parent_id());
            }
            else {
                set_sleep(3);
                printf(1, "parent of grandson pid: %d\n", get_parent_id());
                wait();
            }
        }
        else {
            set_sleep(1);
            printf(1, "children of child: %d\n", get_children(getpid()));
            wait();
            printf(1, "parent pid: %d\n", get_parent_id());
        }
    }
    else {
        set_sleep(2);
        printf(1, "children pid: %d\n", get_children(getpid()));
        wait();
    }
    exit();
}