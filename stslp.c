#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "date.h"

int main(int argc, char *argv[])
{
    int sleepAmount, startTime, finishTime, sleepDuration;

    if(argc > 1) {
        sleepAmount = atoi(argv[1]);
    }
    else {
        sleepAmount = 2;
    }

    printf(1, "Starting the timer!\n");
    startTime = get_time();

    printf(1, "Calling set_sleep() system call!\n");
    set_sleep(sleepAmount);
    printf(1, "set_sleep() system call returned! \n");
    
    printf(1, "Finishing the timer!!\n");
    finishTime = get_time();

    sleepDuration = finishTime - startTime;

    printf(1, "In user mode! Process slept for %d seconds!\n", sleepDuration);
    exit();
}