#include "priority_queue.h"

#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "array_util.h"

priqueue_t priqueue_create(size_t el_size,
                           uint64_t (*hash)(const void *item, uint64_t s0,
                                            uint64_t s1),
                           int (*cmp)(const void *a, const void *b,
                                      void *udata)) {
    priqueue_t queue;
    queue.el_size = el_size;
    queue.heap = vec_create(sizeof(int64_t) + el_size);
    queue.map =
        hashmap_new(el_size + sizeof(size_t), 0, 0, 0, hash, cmp, NULL, NULL);
    queue.buffer = malloc(el_size + sizeof(int64_t));
    return queue;
}

void priqueue_free(priqueue_t *queue) {
    vec_free(&queue->heap);
    hashmap_free(queue->map);
    free(queue->buffer);
}

static int64_t *get_key(priqueue_t *queue, size_t i) {
    return (int64_t *)vec_get(&queue->heap, i);
}

static void set_index(priqueue_t *queue, size_t i) {
    void *element = vec_get(&queue->heap, i) + sizeof(int64_t);
    void *loc = hashmap_get(queue->map, element);
    if (loc) {
        *(size_t *)(loc + queue->el_size) = i;
    } else {
        memcpy(queue->buffer, element, queue->el_size);
        *(size_t *)(queue->buffer + queue->el_size) = i;
        hashmap_set(queue->map, queue->buffer);
    }
}

static void swap_elements(priqueue_t *queue, size_t i, size_t j) {
    memswap(vec_get(&queue->heap, i), vec_get(&queue->heap, j),
            sizeof(int64_t) + queue->el_size);
    set_index(queue, i);
    set_index(queue, j);
}

static void heapify(priqueue_t *queue, size_t i) {
    size_t l = 2 * i + 1;
    size_t r = l + 1;

    size_t m = i;

    if (l<queue->heap.len && * get_key(queue, l)> * get_key(queue, i)) {
        m = l;
    }

    if (r<queue->heap.len && * get_key(queue, r)> * get_key(queue, m)) {
        m = r;
    }

    if (m != i) {
        swap_elements(queue, i, m);
        heapify(queue, m);
    }
}

bool priqueue_pop(priqueue_t *queue, void *dest, int64_t *keydist) {
    if (queue->heap.len) {
        void *first = vec_get(&queue->heap, 0);
        if (keydist) {
            *keydist = *(int64_t *)first;
        }
        memcpy(dest, first + sizeof(int64_t), queue->el_size);
        hashmap_delete(queue->map, first + sizeof(int64_t));
        vec_pop(&queue->heap, first);
        set_index(queue, 0);
        heapify(queue, 0);
        return true;
    } else {
        return false;
    }
}

static bool priqueue_increase_key(priqueue_t *queue, size_t i, int64_t key) {
    if (key < *get_key(queue, i)) {
        return false;
    } else {
        *get_key(queue, i) = key;
        while (i > 0 && *get_key(queue, (i - 1) / 2) < *get_key(queue, i)) {
            size_t par = (i - 1) / 2;
            swap_elements(queue, i, par);
            i = par;
        }
        return true;
    }
}

void priqueue_insert(priqueue_t *queue, const void *item, int64_t key) {
    *(int64_t *)(queue->buffer) = INT64_MIN;
    memcpy(queue->buffer + sizeof(int64_t), item, queue->el_size);
    vec_push(&queue->heap, queue->buffer);
    priqueue_increase_key(queue, queue->heap.len - 1, key);
}

void priqueue_insert_increase(priqueue_t *queue, const void *item,
                              int64_t key) {
    void *loc = hashmap_get(queue->map, item);
    if (loc) {
        size_t i = *(size_t *)(loc + queue->el_size);
        priqueue_increase_key(queue, i, key);
    } else {
        priqueue_insert(queue, item, key);
    }
}
