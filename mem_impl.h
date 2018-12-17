// Linni Cai, Jingqi Yang
// CSE 374 Homework 6
// November 30, 2017
// This is a header file to check memory manager.

#ifndef MEM_IMPL
#define MEM_IMPL
#define BASE 80
#define HEADER_SIZE 16
#define MEM_SIZE 8000

// define the free list.
typedef struct free_node {
    uintptr_t size;
    struct free_node* next;
}free_node;

free_node* freeList;
uintptr_t totalSize;

free_node* scan_free(uintptr_t size);
free_node* expand(uintptr_t size);
void check_heap();
void insert(free_node* p_header);
uintptr_t mem_end(free_node* current);
void combine(free_node* front, free_node* back);

#endif
