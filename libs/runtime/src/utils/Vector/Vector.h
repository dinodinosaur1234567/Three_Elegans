#pragma once

#include <stdint.h>
#include <stddef.h>

typedef struct
{
    void *data;
    uint32_t count;
    uint32_t capacity;
    size_t elem_size;

} Vector;

void VecSpawn(Vector *vec, size_t elem_size);
void VecPush(Vector *vec, const void *element);
void VecDelete(Vector *vec);