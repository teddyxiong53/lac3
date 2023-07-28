
#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <stdbool.h>
#include <pthread.h>

typedef struct ringbuffer {
    unsigned char *buffer;
    int size;
    int count;
    int head;
    int tail;
    pthread_mutex_t mutex;
} ringbuffer;

void ringbuffer_init(ringbuffer *rb, int size);
void ringbuffer_destroy(ringbuffer *rb);
bool ringbuffer_is_empty(const ringbuffer *rb);
bool ringbuffer_is_full(const ringbuffer *rb);
int ringbuffer_push(ringbuffer *rb, const unsigned char *data, int length);
int ringbuffer_pop(ringbuffer *rb, unsigned char *data, int length);
int ringbuffer_count(const ringbuffer *rb);
int ringbuffer_peek(const ringbuffer *rb, unsigned char *data, int length);
void ringbuffer_clear(ringbuffer *rb);

#endif /* RINGBUFFER_H */
