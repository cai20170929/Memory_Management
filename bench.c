// Linni Cai, Jingqi Yang
// November 30, 2017
// This file test get and free memory blocks of
// random sizes and in random order.

#include "mem.h"
#include <time.h>

void test_mem(int arg[], clock_t c_start);

int main(int argc, char** argv) {
    int arg[6] = {10000, 50, 10, 200, 20000, time(NULL)};
    for (int i = 1; i < argc; i++) {
        arg[i - 1] = atoi(argv[i]);
    }
    clock_t c_start = clock();
    test_mem(arg, c_start);
}

// Test the getmem and freemem, take the given arguments and start time
void test_mem(int arg[], clock_t c_start) {
    clock_t c_end;
    int get_count = 0;

    int get_free = 0;
    int big_small = 0;

    int size = 0;
    srand(arg[5]);

    uintptr_t total_size = 0;
    uintptr_t total_free = 0;
    uintptr_t n_free_blocks = 0;
    uintptr_t* mem = (uintptr_t*)malloc(arg[0]*sizeof(uintptr_t));
    double print_ct = 0.1;
    // total n trails
    for (int i = 0; i < arg[0]; i++) {
        get_free = rand() % 100;
        if (get_free < arg[1]) {  // getmem
            big_small = rand() % 100;
            if (big_small < arg[2]) {  // big block
                size = rand() % arg[4] + arg[3];
            } else {
                size = rand() % arg[3] + 1;
            }
            void * get = getmem(size);
            if (get) {
                int ini_size = 16;
                if (size < 16) {
                    ini_size = size;
                }
                char * temp = get;
                for (int i = 0; i < ini_size; i++) {
                    *temp = 0xFE;
                    temp++;
                }
                mem[get_count] = (uintptr_t)get;
                get_count++;
            }
        } else if (get_count > 0) {
            int num = 0;
            if (get_count > 1) {
                num = rand() % get_count;
            }
            freemem((void *) mem[num]);
            mem[num] = mem[get_count - 1];
            get_count--;
        }

        // print the statistics
        if (print_ct < 10.1 && (arg[0] <= 10 || i == (int)(arg[0] * print_ct))) {
            c_end = clock();
            long double c_total = (long double)(c_end - c_start)/CLOCKS_PER_SEC;
            get_mem_stats(&total_size, &total_free, &n_free_blocks);
            printf("Total CPU time: %LF\n", c_total);
            printf("Total acquired storage: %lu\n", total_size);
            printf("Total free blocks: %lu\n", n_free_blocks);
            uintptr_t ave = 0;
            if (n_free_blocks != 0) {
                 ave = total_free / n_free_blocks;
            }
            printf("Average bytes of free blocks: %lu\n", ave);
            printf("\n");
            print_ct += 0.1;
        }
    }
}
