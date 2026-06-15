#pragma once

#include <stdint.h>

typedef struct
{
    void *data;
    uint32_t count;
    size_t elem_size;
    
} DynamicArray;

void DaSpawn(DynamicArray *da, size_t elem_size);
void DaResize(DynamicArray *da, uint32_t count);
void DaDelete(DynamicArray *da);