#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{
    int saved_amount_of_register, number;

    if(argc > 1) {
        number = atoi(argv[1]);
    }
    else {
        number = 12345;
    }

    asm volatile("movl %%ebx, %0;"
         "movl %1, %%ebx;"
         : "=r" ( saved_amount_of_register )
         : "r" ( number )
    );

    printf(1, "Calling count_num_of_digits() system call!\n");
    count_num_of_digits();
    printf(1, "In user mode! count_num_of_digits() system call returned! \n");

    asm volatile(
        "movl %1, %%ebx;" 
        : "=r"(saved_amount_of_register)
        : "r"(saved_amount_of_register)
    );
    
    exit();
}