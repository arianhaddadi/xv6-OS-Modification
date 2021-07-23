#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "date.h"

int main(int argc, char* argv[]) {
    if(fork() == 0) {
        int time1, time2, var = 0;
        time1 = get_time();
        time2 = get_time();
        while(time2 - time1 < 60)
        {
            time2 = get_time();
            var += 1;
            printf(1, "");
        }
        printf(1, "DONE!!\n");
        exit();
    }
    exit();
}