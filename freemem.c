// Linni Cai, Jingqi Yang
// CSE 374 Homework 6
// November 30, 2017
// This file frees a block of storage and 
// returns it to the free list.

#include "mem.h"
#include "mem_impl.h"

// Return the block of storage at location p to
// the free list
void freemem(void* p) {
    if (!p) {
        return;
    }
    check_heap();
    insert((free_node*)((uintptr_t)p - HEADER_SIZE));
    check_heap();
}

// Insert the free block back into the freelist
// and combine adjacent blocks into one block
void insert(free_node * p_header) {
    extern free_node * freeList;
    free_node * current = freeList;
    uintptr_t p_loc = (uintptr_t) p_header;
    uintptr_t p_end = mem_end(p_header);

    if (!freeList) {  // p is the only free block
        freeList = p_header;
    } else {
        int done = 1;  // mark false

        // p at the beginning of the freelist
        if (p_loc < (uintptr_t)freeList) {
            if (p_end == (uintptr_t)freeList) {
                combine(p_header, freeList);
            } else {
                p_header->next = freeList;
            }
            freeList = p_header;
            done = 0;  // mark true
        }

        // p in the middle of the freelist
        while (done == 1 && current->next) {
            free_node* next_node = current->next;
            if (p_end < (uintptr_t)next_node) {
                p_header->next = next_node;
                if (mem_end(current) == p_loc) {
                    combine(current, p_header);
                } else if (mem_end(current) < p_loc) {
                    current->next = p_header;
                }
                done = 0;
            } else if (p_end == (uintptr_t)next_node) {
                combine(p_header, next_node);
                if (mem_end(current) == p_loc) {
                    combine(current, p_header);
                } else {
                    current->next = p_header;
                }
                done = 0;
            } else {
                current = current->next;
            }
        }

        // p at the end of the freelist
        if (done == 1) {
            if (mem_end(current) == p_loc) {
                current->size += p_header->size + HEADER_SIZE;
            } else {
                current->next = p_header;
            }
        }
    }
}

// Return the bottom location of the given node
uintptr_t mem_end(free_node* current) {
    return (uintptr_t)current + current->size + HEADER_SIZE;
}

// Combine the given front node and back node
void combine(free_node* front, free_node* back) {
    front->size += (uintptr_t)back->size + HEADER_SIZE;
    front->next = back->next;
}
