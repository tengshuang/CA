#include <iostream>
#include <stdint.h>
#include <cstdlib>
#include <ele.h>
#include <fstream>
using namespace std;

void cacheSize(){
    ofstream fout("cacheSize.dat");
   // fout << "hello" << endl;
    cout << "executing" << endl;
    ele a = ele();
    for (int memUni = 1024 / sizeof(uint64_t); memUni <= 8196 * 1024 / sizeof(uint64_t); memUni <<= 1) { // For every size between
        a.address = (uint64_t*) calloc(memUni, sizeof(uint64_t));
	cout << memUni * sizeof(uint64_t) / 1024 <<"KB is being canculated!"<< endl;
       	fout << "size: "<< memUni * sizeof(uint64_t) / 1024 <<"KB, throughput: "<< a.run(memUni, 32) << endl;
    }
    fout.close();
}
int main(int argc, char** argv) {
    cacheSize();
    return 0;
}

