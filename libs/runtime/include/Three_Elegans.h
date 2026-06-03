#pragma once

#include <stdint.h>

typedef struct 
{
    uint8_t something;
} Neuron;

typedef struct
{
    int neuron_count;
    Neuron *neurons;
} Brain;

void InitBrain(Brain* b);