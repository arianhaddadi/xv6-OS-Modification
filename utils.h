#include "types.h"

// Wrapper function for rdtsc instructions
uint rdtsc() {
    uint lo, hi;
    asm volatile("rdtsc" : "=a" (lo), "=d" (hi));
    return lo;
}