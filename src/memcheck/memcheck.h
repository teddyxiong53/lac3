
#ifndef __AML_MEMCHECK_H__
#define __AML_MEMCHECK_H__
#include <stddef.h>

#define DEBUG_MEMCHECK

#ifdef DEBUG_MEMCHECK
void *my_malloc(size_t size);
void my_free(void *addr);
void check_memory_leak() ;
void *my_calloc(size_t num, size_t size) ;
void *my_realloc(void *addr, size_t size) ;

#define  malloc my_malloc
#define  free my_free
#define  calloc my_calloc
#define  realloc my_realloc
#endif

#endif // __AML_MEMCHECK_H__

