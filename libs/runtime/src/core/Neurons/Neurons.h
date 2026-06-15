#pragma once

#include "utils/types/types.h"
#include "utils/DynamicArray/DynamicArray.h"

typedef struct
{
    DynamicArray da_neurons_potentials;
    DynamicArray da_neurons_thresholds;
    DynamicArray da_neurons_signals;

    potential *neurons_potentials;
    threshold *neurons_thresholds;
    signal *neurons_signals;
    
} Neurons;

void NeuronsInit(Neurons *neurons);
void NeuronsDelete(Neurons *neurons);