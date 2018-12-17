// Linni Cai, Jingqi Yang
// CSE 374 Homework 6
// November 30, 2017
// This file prints the listing of blocks
// on the free list.

#include "mem.h"
#include "mem_impl.h"

// print a formatted listing on file f showing
// the blocks on the free list
void print_heap(FILE * f) {
    extern free_node * freeList;
    if (!freeList) {
        return;
    }
    free_node * current = freeList;
    while (current) {
        uintptr_t block_loc = (uintptr_t)current + HEADER_SIZE;
        fprintf(f, "The address of the memory block is: %p", (void *)block_loc);
        fprintf(f, "\nsize is: ");
        fprintf(f, "%" PRIuPTR "\n", current->size);
        current = current->next;
    }
}
