# Linni Cai, Jingqi Yang
# CSE 374 Homework 6
# November 30, 2017
# This file compiles files for bench and test.

object=getmem.o freemem.o get_mem_stats.o print_heap.o mem_utils.o bench.o

bench: $(object)
	gcc -Wall -std=c11 -g $(object) -o bench 

#test: $(object)
#	gcc -Wall -std=c11 -g $(object) -o test

bench.o: bench.c mem.h
	gcc -Wall -std=c11 -g -c bench.c

test.o: test.c mem.h
	gcc -Wall -std=c11 -g -c test.c

getmem.o: getmem.c mem_impl.h
	gcc -Wall -std=c11 -g -c getmem.c

freemem.o: freemem.c mem_impl.h
	gcc -Wall -std=c11 -g -c freemem.c

get_mem_stats.o: get_mem_stats.c mem_impl.h
	gcc -Wall -std=c11 -g -c get_mem_stats.c

print_heap.o: print_heap.c mem_impl.h
	gcc -Wall -std=c11 -g -c print_heap.c

mem_utils.o: mem_utils.c mem_impl.h
	gcc -Wall -std=c11 -g -c mem_utils.c

clean: 
	rm -f *.o git.log bench test
