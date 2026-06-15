#pragma once

#include <stdint.h>

typedef uint8_t  signal;
typedef int8_t   weight;

typedef int16_t potential;
typedef uint16_t threshold;

typedef uint32_t index;

typedef struct
{
    signal *data;
    index size;

} SignalBuffer;