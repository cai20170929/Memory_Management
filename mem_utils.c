// Linni Cai, Jingqi Yang
// November 30, 2017
// This file checks problems for the memory manager.

#include "mem.h"
#include "mem_impl.h"
#include <assert.h>

// Check for possible problems with the
// free list data structure
void check_heap() {
    if (!freeList) {
        return;
    }

    free_node * current = freeList;

    while (current) {
        assert(current->size >= BASE);
        if (current->next) {
            free_node * next_node = current->next;
            assert(next_node->size >= BASE);
            assert(mem_end(current) < (uintptr_t)next_node);
        }
        current = current->next;
    }
}
