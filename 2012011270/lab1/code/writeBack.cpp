#include <iostream>
#include <fstream>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <ele.h>
using namespace std;

#define TOTALREAD (1ULL << 32)
#define L1_CACHE_SIZE (32 * 1024)
#define L2_CACHE_SIZE (256 * 1024)
#define BLOCK_SIZE (1 << 6)

void writeBack()
{
    ele a = ele();
    ofstream fout("writeback.dat");
    a.address = (uint64_t*) calloc(L2_CACHE_SIZE / sizeof(uint64_t), sizeof(uint64_t));
    for (uint64_t size = L1_CACHE_SIZE; size <= 2 * L1_CACHE_SIZE; size <<=1) {
        fout << "size: " << size << ", throughput: " << a.wrirun(size) << endl;
    }
    free(a.address);
    fout.close();
}
int main(int argc, char** argv) {
    writeBack();
    return 0;
}

