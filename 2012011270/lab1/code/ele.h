#ifndef ELE_H
#define ELE_H
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <algorithm>
class ele{
    private:
        void init(int memUni, int stride);
	void init(uint64_t mask);
	void wriinit(uint64_t size);
	void test();
	void writest();
	double get_time_delta(timespec* t1, timespec * t2);
    public:
	uint64_t* address;
	double run(int memUni, int stride);
	double run(uint64_t mask);
	double wrirun(uint64_t size);
	void replacement(int cache_size, int asso);
};

#endif
