// Linni Cai, Jingqi Yang
// November 30, 2017
// This file gives the statistics of the state of memory manager.

#include "mem.h"
#include "mem_impl.h"

// store statistics about the current state of the memory manager
void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free,
    uintptr_t* n_free_blocks) {
    *total_size = totalSize;
    free_node* temp = freeList;
    *total_free = 0;
    *n_free_blocks = 0;
    while (temp != NULL) {
        *total_free += temp->size + HEADER_SIZE;
        *n_free_blocks += 1;
        temp = temp->next;
    }
}
