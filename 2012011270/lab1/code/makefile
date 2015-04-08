ELE = -I.
replacement:replacement.o ele.o
	g++ replacement.o ele.o -o replacement
writeBack:writeBack.o ele.o
	g++ writeBack.o ele.o -o writeBack
matrix_mul:matrix_mul.o
	g++ matrix_mul.o -o matrix_mul -O3
asso:associativity.o ele.o
	g++ associativity.o ele.o -o asso
blockSize: block.o ele.o
	g++ block.o ele.o -o blockSize
cacheSize: cache.o ele.o
	g++ cache.o ele.o -o cacheSize
ele.o:ele.cpp ele.h
	g++ $(ELE) -o ele.o -c ele.cpp

cache.o:cache.cpp ele.h
	g++ $(ELE) -o cache.o -c cache.cpp

block.o:block.cpp ele.h
	g++ $(ELE) -o block.o -c block.cpp
associativity.o:associativity.cpp ele.h
	g++ $(ELE) -o associativity.o -c associativity.cpp
matrix_mul.o:matrix_mul.cpp
	g++ -o matrix_mul.o -c matrix_mul.cpp -O3
writeBack.o:writeBack.cpp ele.h
	g++ $(ELE) -o writeBack.o -c writeBack.cpp
replacement.o:replacement.cpp ele.h
	g++ $(ELE) -o replacement.o -c replacement.cpp
