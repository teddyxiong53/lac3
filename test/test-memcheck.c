#include "memcheck.h"
#include "mylog.h"
// Example program
int main() {
    // Allocate some memory blocks
    int *p1 = malloc(sizeof(int));
    int *p2 = malloc(sizeof(int) * 10);
    char *p3 = malloc(100);

    // Free some memory blocks
    free(p2);
    free(p3);

    // Check if there are any unfreed memory blocks
    check_memory_leak();

    return 0;
}
