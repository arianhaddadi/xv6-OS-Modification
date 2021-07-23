#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        write(1, "Wrong Number of Arguments!!\n", strlen("Wrong Number of Arguments!!\n"));
        exit();
    }
    if (strcmp(argv[1], "PATH") != 0) {
        write(1, "Wrong Arguments!!\n", strlen("Wrong Arguments!!\n"));
        exit();
    }

    printf(1, "Calling set_path() system call!\n");
    set_path(argv[2]);
    printf(1, "In user mode! set_path() system call returned! \n");
    
    
    exit();
}