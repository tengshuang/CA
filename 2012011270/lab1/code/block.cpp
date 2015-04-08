#include <iostream>
#include <stdint.h>
#include <ele.h>
#include <fstream>
#include <cstdlib>
using namespace std;

void blockSize(int Lx_size)
{
    ofstream fout("blockSize.dat");
    ele a = ele();
    int memUni = Lx_size * 1024 / sizeof(uint64_t);
    for (int stride = 1; stride < 64; ++stride) {
        a.address = (uint64_t*) calloc(memUni, sizeof(uint64_t));
	cout << "The " << stride << "th stride is canculated" << endl;
        fout << "stride: " << stride << ", throughput: " << a.run(memUni, stride) << endl;
    }
    fout.close();
}
int main(int argc, char** argv) {
    blockSize(32);
    return 0;
}

