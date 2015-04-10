#include <iostream>
#include <ele.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define TOTALREAD (1ULL << 32)
#define CACHE_SIZE (256 * 1024)
#define BLOCK_SIZE (1 << 6)
#define REPLACE_REPEAT_TIME (1 << 13)
#define LRU_TH 1.2

double ele::get_time_delta(timespec* t1, timespec * t2) {
    return ((t2->tv_sec - t1->tv_sec) + (double) (t2->tv_nsec - t1->tv_nsec) * 1e-9) * 1e9;
}

void ele::replacement(int cache_size, int asso) {
    cout << "Deciding replacement strategy..." << endl;
    timespec t1, t2;
    int s = cache_size << 9 << 1;
    int* buffer = new int[s];
    int n = asso << 1;
    int gs = s / n;
    clock_gettime(CLOCK_MONOTONIC, &t1);
    for (int j = 0; j < asso + 1; j ++) {
        buffer[j * gs] = 1;
    }
    // repeated visit two cache blocks, which yields temporal locality
    for (int i = 0; i < REPLACE_REPEAT_TIME; i ++) {
        buffer[(asso - 1) * gs] = 1;
        buffer[asso * gs] = 1;
    }
    clock_gettime(CLOCK_MONOTONIC, &t2);
    double time_with_locality = get_time_delta(&t1, &t2);
    cout << "Averaged time WITH locality =\t" << time_with_locality << "ns." << endl;

    clock_gettime(CLOCK_MONOTONIC, &t1);
    for (int j = 0; j < asso + 1; j ++) {
        buffer[j * gs] = 1;
    }
    for (int i = 0; i < REPLACE_REPEAT_TIME / asso * 2; i ++) {
        // visit the buffer in cycles
        for (int j = 0; j < asso; j++) {
            buffer[j * gs] = 1;
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &t2);
    double time_wo_locality = get_time_delta(&t1, &t2);
    cout << "Averaged time WITHOUT locality =\t" << time_wo_locality << "ns." << endl;
    if (time_wo_locality / time_with_locality > LRU_TH) {
        cout << "LRU IS used" << endl;
    }
    else {
        cout << "LRU IS NOT used" << endl;
    }
}
void ele::wriinit(uint64_t size) { // Initialize memory
    int i;
    for (i = 0; i < size / sizeof(uint64_t); i += BLOCK_SIZE / sizeof(uint64_t)) {
        address[i] = (uint64_t) &address[i + BLOCK_SIZE / sizeof(uint64_t)];
    }
    address[i - BLOCK_SIZE / sizeof(uint64_t)] = 0;
}

void ele::writest() {
    uint64_t* cur = address;
    while (*cur) {
        ++*(cur + 1);
        cur = (uint64_t*) *cur;
    }
}

double ele::wrirun(uint64_t size) {
    uint64_t iterNum = TOTALREAD * BLOCK_SIZE / (size * sizeof(uint64_t));
    wriinit(size);
    writest(); // Warm up
    clock_t start = clock();
    while (iterNum--) { // Repeat
        writest();
    }
    double cycles = (double) (clock() - start);
    return ((TOTALREAD / (1 << 20)) * CLOCKS_PER_SEC) / cycles;
}
void ele::init(int memUni, int stride) { // Initialize as linked list
    int i;
    for (i = 0; i < (memUni >> 1); i += stride) {
        address[i] = (uint64_t) &address[i + (memUni >> 1)];
        address[i + (memUni >> 1)] = (uint64_t) &address[i + stride];
    }
    address[i + (memUni >> 1) - stride] = 0;
}
void ele::init(uint64_t mask) { // Initialize memory
    int num = CACHE_SIZE / mask;
    uint64_t* cur = address;
    while (--num) {
        *cur = (uint64_t)cur + mask;
        cur = (uint64_t*) *cur;
    }
    *cur = 0;
}
double ele::run(uint64_t mask) {
    double cycles;
    clock_t start;
    uint64_t iterNum = TOTALREAD * mask / (CACHE_SIZE * sizeof(uint64_t));
    init(mask);
    test(); // Warm up
    start = clock();
    while (iterNum--) { // Repeat
        test();
    }
    cycles = (double) (clock() - start);
    return ((TOTALREAD / (1 << 20)) * CLOCKS_PER_SEC) / cycles;
}
void ele::test() { // Chase list to the end
    uint64_t* cur = address;
    while (*cur) cur = (uint64_t*) *cur;
}
double ele::run(int memUni, int stride) {
    init(memUni, stride);
    uint64_t iterNum = (TOTALREAD / (memUni * sizeof(uint64_t))) * stride;
    test(); // Warm up
    clock_t start = clock();
    while (iterNum--) test();
    double cycles = (double) (clock() - start);
    return ((TOTALREAD / (1 << 20)) * CLOCKS_PER_SEC) / cycles;
}
