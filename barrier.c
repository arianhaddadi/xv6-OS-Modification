#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "param.h"

int main() {
    long long int play;
    int i;
    make_barrier();
    for(i = 0; i < BARRIER_CAPACITY - 1; i++) {
        if(!fork()) {
            for(int j = 0; j < i; j++) {
                play = 0;
                for(int k = 0; k < 40000000; k++) {
                    play += k * 10 / 104 * i;
                }
            }
            break; 
        }
    }
    sleep(i);
    printf(1, "Process with pid %d wants to check the barrier!\n", getpid());
    check_barrier();
    sleep(i);
    printf(1, "Process with pid %d passed from the barrier!\n", getpid());
    exit();
}