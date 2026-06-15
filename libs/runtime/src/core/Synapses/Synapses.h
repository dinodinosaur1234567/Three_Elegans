#pragma once

#include "utils/types/types.h"
#include "utils/DynamicArray/DynamicArray.h"

typedef struct
{
    DynamicArray da_synapses_sources;
    DynamicArray da_synapses_weights;
    DynamicArray da_synapses_targets;

    index *synapses_sources;
    weight *synapses_weights;
    index *synapses_targets;
    
} Synapses;

void SynapsesInit(Synapses *synapses);
void SynapsesDelete(Synapses *synapses);
