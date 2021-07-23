#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{

    if(argc != 1) {
        printf(1, "Wrong input!\n", sizeof("Wrong input!\n"));
    }

    printf(1, "Calling print_processes_info() system call!\n");
    print_processes_info();
    printf(1, "In user mode! print_processes_info() system call returned! \n");
    
    exit();
}