#pragma once

#include "Three_Elegans.h"
#include <stdint.h>

typedef struct 
{
    uint8_t something;
} Neuron;

struct Brain 
{
    int neuron_count;
    float* state;
};

void BrainInit(Brain* b)
{
    
}