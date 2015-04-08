#include <iostream>
#include <cstdlib>
#include <time.h>
#include <stdint.h>
#include <fstream>
#include <ele.h>
using namespace std;


#define CACHE_SIZE (256 * 1024)
#define BLOCK_SIZE (1 << 6)

void associativity(){
    ele a = ele();
    ofstream fout("associativity.dat");
    a.address = (uint64_t*) calloc(CACHE_SIZE / sizeof(uint64_t), sizeof(uint64_t));
    for (uint64_t mask = BLOCK_SIZE; mask < CACHE_SIZE; mask <<= 1) {
        fout << "mask: "<<mask << ", throughput: " <<  a.run(mask) << endl;
    }
    fout.close();
    free(a.address);
}
int main(int argc, char** argv) {
    associativity();
    return 0;
}

