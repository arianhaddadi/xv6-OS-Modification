#include "types.h"
#include "user.h"
#include "utils.h"


int main(void) {
    uint start = rdtsc();

    getpid();

    uint end = rdtsc();

    printf(1, "Elapsed Time: %x\n", end - start);

    exit();
}
