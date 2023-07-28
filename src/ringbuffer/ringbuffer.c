

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "ringbuffer.h"
#include "memcheck.h"

// Initialize the ring buffer
void ringbuffer_init(ringbuffer *rb, int size) {
    rb->buffer = (unsigned char *)malloc(size * sizeof(unsigned char));
    rb->size = size;
    rb->count = 0;
    rb->head = 0;
    rb->tail = 0;
    pthread_mutex_init(&(rb->mutex), NULL);
}

// Destroy the ring buffer
void ringbuffer_destroy(ringbuffer *rb) {
    free(rb->buffer);
    pthread_mutex_destroy(&(rb->mutex));
}

// Check if the ring buffer is empty
bool ringbuffer_is_empty(const ringbuffer *rb) {
    return rb->count == 0;
}

// Check if the ring buffer is full
bool ringbuffer_is_full(const ringbuffer *rb) {
    return rb->count == rb->size;
}

// Write a specified length of data into the ring buffer
// Returns the number of elements successfully written
int ringbuffer_push(ringbuffer *rb, const unsigned char *data, int length) {
    pthread_mutex_lock(&(rb->mutex));

    if (ringbuffer_is_full(rb)) {
        pthread_mutex_unlock(&(rb->mutex));
        return 0;  // Buffer is full, cannot write new elements
    }

    int elements_to_write = (length < rb->size - rb->count) ? length : (rb->size - rb->count);

    // Write data into the ring buffer
    for (int i = 0; i < elements_to_write; i++) {
        rb->buffer[rb->tail] = data[i];
        rb->tail = (rb->tail + 1) % rb->size;  // Update tail index
    }

    rb->count += elements_to_write;

    pthread_mutex_unlock(&(rb->mutex));

    return elements_to_write;
}

// Read a specified length of data from the ring buffer
// Returns the number of elements successfully read
int ringbuffer_pop(ringbuffer *rb, unsigned char *data, int length) {
    pthread_mutex_lock(&(rb->mutex));

    if (ringbuffer_is_empty(rb)) {
        pthread_mutex_unlock(&(rb->mutex));
        return 0;  // Buffer is empty, cannot read elements
    }

    int elements_to_read = (length < rb->count) ? length : rb->count;

    // Read data from the ring buffer
    for (int i = 0; i < elements_to_read; i++) {
        data[i] = rb->buffer[rb->head];
        rb->head = (rb->head + 1) % rb->size;  // Update head index
    }

    rb->count -= elements_to_read;

    pthread_mutex_unlock(&(rb->mutex));

    return elements_to_read;
}

// Get the number of elements in the ring buffer
int ringbuffer_count(const ringbuffer *rb) {
    return rb->count;
}

// Peek a specified length of data from the ring buffer without modifying the buffer
// Returns the number of elements successfully peeked
int ringbuffer_peek(const ringbuffer *rb, unsigned char *data, int length) {
    pthread_mutex_lock(&(rb->mutex));

    if (ringbuffer_is_empty(rb)) {
        pthread_mutex_unlock(&(rb->mutex));
        return 0;  // Buffer is empty, cannot peek elements
    }

    int elements_to_peek = (length < rb->count) ? length : rb->count;

    int current_index = rb->head;
    for (int i = 0; i < elements_to_peek; i++) {
        data[i] = rb->buffer[current_index];
        current_index = (current_index + 1) % rb->size;
  // Move to the next index
    }

    pthread_mutex_unlock(&(rb->mutex));

    return elements_to_peek;
}

// Clear the ring buffer, resetting all indices and count
void ringbuffer_clear(ringbuffer *rb) {
    pthread_mutex_lock(&(rb->mutex));

    rb->count = 0;
    rb->head = 0;
    rb->tail = 0;

    pthread_mutex_unlock(&(rb->mutex));
}
