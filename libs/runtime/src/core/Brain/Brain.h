#pragma once

#include "utils/types/types.h"
#include "core/Neurons/Neurons.h"
#include "core/Synapses/Synapses.h"

typedef struct
{
    Neurons neurons;
    Synapses synapses;
    
    index sensory_neurons_count;
    index inter_neurons_count;
    index motor_neurons_count;

    index synapses_count;

} Brain;

void BrainInit(Brain *brain);
void BrainTick(Brain *brain, SignalBuffer *input, SignalBuffer *output);
void BrainDelete(Brain *brain);
