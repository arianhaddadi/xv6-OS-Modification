#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{
    int number1, number2;

    if(argc > 1) {
        number1 = atoi(argv[1]);
        number2 = atoi(argv[2]);
    }
    else {
        printf(1, "Wrong input!\n", sizeof("Wrong input!\n"));
        exit();
    }

    printf(1, "Calling set_lottery_ticket() system call!\n");
    set_lottery_ticket(number1, number2);
    printf(1, "In user mode! set_lottery_ticket() system call returned! \n");
    
    exit();
}