/***************************************************************************
 * Copyright (c) 2023 amlogic, inc. All rights reserved.
 *
 * description:
 * 		Memcheck module. check the mem alloc with malloc/realloc/calloc
 * is all freed or not.
 *
 * \author hanliang.xiong
 * \date 2023-07-20
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define DEBUG_MEMCHECK

#ifdef DEBUG_MEMCHECK

// Define a linked list node struct to record each allocated memory block
struct mem_block {
    void *addr; // the address of the memory block
    size_t size; // the size of the memory block
    struct mem_block *next; // the next memory block
};

static struct mem_block *mem_list = NULL; // the head pointer of the memory block linked list

// Custom function to allocate memory and record each allocated memory block
void *my_malloc(size_t size) {
    void *addr = malloc(size);
    printf("memcheck -- malloc:addr:%p, size:%d\n", addr, size);
    if (addr != NULL) {
        // Allocation succeeded, add the memory block to the linked list
        struct mem_block *block = malloc(sizeof(struct mem_block));
        block->addr = addr;
        block->size = size;
        block->next = mem_list;
        mem_list = block;
    }
    return addr;
}
// Custom function to reallocate memory and update the corresponding memory block in the linked list
void *my_realloc(void *addr, size_t size) {
    void *new_addr = realloc(addr, size);
    printf("memcheck -- realloc:addr:%p, new_addr:%p, size:%d\n", addr, new_addr, size);
    if (new_addr != NULL) {
        // Reallocation succeeded, update the corresponding memory block in the linked list
        struct mem_block *block = mem_list;
        while (block != NULL) {
            if (block->addr == addr) {
                block->addr = new_addr;
                block->size = size;
                break;
            }
            block = block->next;
        }
    }
    return new_addr;
}

// Custom function to allocate and clear memory and record each allocated memory block
void *my_calloc(size_t num, size_t size) {
    void *addr = calloc(num, size);
    if (addr != NULL) {
        printf("memcheck -- calloc:addr:%p, size:%d\n", addr, size*num);
        // Allocation succeeded, add the memory block to the linked list
        struct mem_block *block = malloc(sizeof(struct mem_block));
        block->addr = addr;
        block->size = num * size;
        block->next = mem_list;
        mem_list = block;
    }
    return addr;
}
// Custom function to free memory and remove the corresponding memory block from the linked list
void my_free(void *addr) {
    struct mem_block *prev = NULL;
    struct mem_block *curr = mem_list;
    while (curr != NULL) {
        if (curr->addr == addr) {
            // Found the corresponding memory block, remove it from the linked list
            if (prev == NULL) {
                mem_list = curr->next;
            } else {
                prev->next = curr->next;
            }
            printf("memcheck -- free:addr:%p, size:%d\n", addr, curr->size);
            free(curr);

            free(addr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

// Check if there are any unfreed memory blocks and print related information
void check_memory_leak() {
    struct mem_block *block = mem_list;
    while (block != NULL) {
        printf("Memory block at %p size %lu not freed\n", block->addr, block->size);
        block = block->next;
    }
}
#if 0
// Example program
int main() {
    // Allocate some memory blocks
    int *p1 = my_malloc(sizeof(int));
    int *p2 = my_malloc(sizeof(int) * 10);
    char *p3 = my_malloc(100);

    // Free some memory blocks
    my_free(p2);
    my_free(p3);

    // Check if there are any unfreed memory blocks
    check_memory_leak();

    return 0;
}

#endif

#endif
