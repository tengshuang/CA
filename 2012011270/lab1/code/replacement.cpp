#include <iostream>
#include <time.h>
#include <string.h>
#include <algorithm>
#include <ele.h>

#define CACHE_REPEAT_TIME (1 << 13)
#define BLOCK_REPEAT_TIME (1 << 12)
#define ASSO_REPEAT_TIME (1 << 13)
#define STEP_SIZE 16
#define TEST_BLOCK_SIZE (1 << 18)
#define WRITE_STYLE_SIZE (1 << 13)
#define WRITE_REPEAT_TIME (1 << 13)
#define WRITE_STEP_SIZE 16
#define WRITE_TH 1.2
#define REPLACE_REPEAT_TIME (1 << 13)
#define LRU_TH 1.2

using namespace std;

int main() {
	ele a = ele();
    	a.replacement(32, 64);
	return 0;
}
