// Linni Cai, Jingqi Yang
// CSE 374 Homework 6
// November 30, 2017
// This file allocates memory from the free list.

#include "mem.h"
#include "mem_impl.h"

// Return a pointer to a new block satifies the given size
void* getmem(uintptr_t size) {
    check_heap();
    extern free_node * freeList;
    if (size <= 0) {
        return NULL;
    }
    uintptr_t real_size = size;
    free_node* result;
    free_node* current = freeList;
    free_node* extra;

    // cast size
    if (size % HEADER_SIZE != 0) {
        real_size = ((size / HEADER_SIZE) + 1) * HEADER_SIZE;
    }

    if (real_size < BASE) {
        real_size = BASE;
    }

    // find the mem
    result = scan_free(real_size);

    // expand and find the mem
    if (!result) {
        if (real_size > MEM_SIZE) {
            // return the mem head loc
            extern uintptr_t totalSize;
            free_node* temp = (free_node*)malloc(real_size + HEADER_SIZE);
            temp->size = real_size;
            temp->next = NULL;
            totalSize += real_size + HEADER_SIZE;
            check_heap();
            return (void*)((uintptr_t)temp + HEADER_SIZE);
        } else {
            expand(MEM_SIZE);
            result = scan_free(real_size);
        }
    }

    // take the mem
    if ((uintptr_t)result != (uintptr_t)freeList) {
        while (current && current->next) {
            if ((uintptr_t)current->next == (uintptr_t)result) {
                break;
            } else {
                current = current->next;
            }
        }
    }

    // divide the taken mem
    if (result->size > real_size + BASE) {
        extra = (free_node*)((uintptr_t)result + HEADER_SIZE + real_size);
        extra->size = result->size - HEADER_SIZE - real_size;
        extra->next = result->next;
        result->size = real_size;
        result->next = NULL;
    } else {
        extra = result->next;
    }

    // disconnect current and freeList, connect current->next and freeList
    if ((uintptr_t) freeList == (uintptr_t)result) {
        freeList = extra;
    } else {
        current->next = extra;
    }
    check_heap();
    return (void*)((uintptr_t)result + HEADER_SIZE);
}

// Return the found free block satisfies the given size in the free list
free_node* scan_free(uintptr_t size) {
    extern free_node * freeList;
    free_node* free_block = freeList;
    while (free_block) {
        if (free_block->size >= size) {
            return free_block;
        } else {
            free_block = free_block->next;
        }
    }
    return NULL;
}

// Return the new free block of the given size
free_node* expand(uintptr_t size) {
    extern uintptr_t totalSize;
    free_node* extra = (free_node*)malloc(size + HEADER_SIZE);
    extra->size = size;
    extra->next = NULL;
    totalSize += size + HEADER_SIZE;
    insert(extra);
    return extra;
}
