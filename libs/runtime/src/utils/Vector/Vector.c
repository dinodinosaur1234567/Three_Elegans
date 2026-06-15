#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/Vector/Vector.h"
#include "core/Logger/Logger.h"

void VecSpawn(Vector *vec, size_t elem_size)
{
    vec->data = NULL;
    vec->count = 0;
    vec->capacity = 0;
    vec->elem_size = elem_size;
}

void VecPush(Vector *vec, const void *element)
{
    if (vec->count >= vec->capacity)
    {
        uint32_t new_capacity;

        if (vec->capacity == 0)
            new_capacity = 4;
        else
            new_capacity = vec->capacity * 2;

        void *tmp = realloc(
            vec->data,
            new_capacity * vec->elem_size
        );

        if (!tmp) LogMessage(ERROR, "VecPush: allocation failed\n");

        vec->data = tmp;
        vec->capacity = new_capacity;
    }

    memcpy(
        (char*)vec->data + (vec->count * vec->elem_size),
        element,
        vec->elem_size
    );

    vec->count++;
}

void VecDelete(Vector *vec)
{
    free(vec->data);
    vec->data = NULL;
    vec->count = 0;
    vec->capacity = 0;
    vec->elem_size = 0;
}