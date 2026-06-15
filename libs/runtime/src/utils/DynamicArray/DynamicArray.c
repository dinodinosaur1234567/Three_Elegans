#include <stdio.h>
#include <stdlib.h>

#include "utils/DynamicArray/DynamicArray.h"
#include "core/Logger/Logger.h"

void DaSpawn(DynamicArray *da, size_t elem_size)
{
    da->data = NULL;
    da->count = 0;
    da->elem_size = elem_size;
}

void DaResize(DynamicArray *da, uint32_t count)
{
    if (count == 0)
    {
        free(da->data);
        da->data = NULL;
        da->count = 0;
        da->elem_size = 0;
        return;
    }

    void *tmp = realloc(da->data, count * da->elem_size);

    if (tmp) 
    {
        da->data = tmp;
        da->count = count;
    }
    else LogMessage(ERROR, "DaResize: allocation failed\n");
}

void DaDelete(DynamicArray *da)
{
    free(da->data);
    da->data = NULL;
    da->count = 0;
    da->elem_size = 0;
}