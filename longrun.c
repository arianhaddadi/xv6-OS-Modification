#include "types.h"
#include "user.h"
#include "utils.h"




int main(void) {
    int num_processes = 20;

    for (int i = 0; i < num_processes; i++) {
        if (fork() == 0) {
            int temp;
            int ceil = 100000000;
            for (int j = 0; j < ceil; j++) temp = j;
            printf(1, "Child Done\n");
            exit();
        }
    }
    
    for (int i = 0; i < num_processes; i++) {
        wait();
    }

    printf(1, "Parent Done\n");
    exit();
}