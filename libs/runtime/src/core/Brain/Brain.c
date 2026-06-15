#include <stdio.h>
#include <stdlib.h>

#include "core/Brain/Brain.h"

void BrainInit(Brain *brain)
{
    NeuronsInit(&brain->neurons);
    SynapsesInit(&brain->synapses);
}

void BrainTick(Brain *brain, SignalBuffer *input, SignalBuffer *output)
{
    // ----- Process all neurons -----
    
    // Process sensory neurons
    if(input->size != brain->sensory_neurons_count)
    {
        fprintf(
            stderr,
            "BrainTick: input buffer size mismatch. Expected %u sensory neurons, but got %u inputs.\n",
            brain->sensory_neurons_count,
            input->size
        );

        exit(EXIT_FAILURE);
    }

    for(index i = 0; i < brain->sensory_neurons_count; i++)
    {
        // Set potential
        brain->neurons.neurons_potentials[i] = input->data[i];

        // Activation function
        if (brain->neurons.neurons_potentials[i] >= brain->neurons.neurons_thresholds[i]) brain->neurons.neurons_signals[i] = 1;
        else brain->neurons.neurons_signals[i] = 0;

        // Reset potential
        brain->neurons.neurons_potentials[i] = 0;
    }

    // Process inter neurons
    for(index i = brain->inter_neurons_count; i < brain->sensory_neurons_count + brain->inter_neurons_count; i++)
    {
        // Activation function
        if (brain->neurons.neurons_potentials[i] >= brain->neurons.neurons_thresholds[i]) brain->neurons.neurons_signals[i] = 1;
        else brain->neurons.neurons_signals[i] = 0;

        // Reset potential
        brain->neurons.neurons_potentials[i] = 0;
    }

    // Process motor neurons
    if(output->size != brain->motor_neurons_count)
    {
        fprintf(
            stderr,
            "BrainTick: output buffer size mismatch. Expected %u motor neurons, but got %u outputs.\n",
            brain->motor_neurons_count,
            output->size
        );

        exit(EXIT_FAILURE);
    }

    for(index i = brain->inter_neurons_count + brain->sensory_neurons_count; i < brain->inter_neurons_count + brain->sensory_neurons_count + brain->motor_neurons_count; i++)
    {
        // Activation function
        if (brain->neurons.neurons_potentials[i] >= brain->neurons.neurons_thresholds[i]) 
            output->data[i - brain->inter_neurons_count - brain->sensory_neurons_count] = 1;
        else
            output->data[i - brain->inter_neurons_count - brain->sensory_neurons_count] = 0;

        // Reset potential
        brain->neurons.neurons_potentials[i] = 0;
    }

    // ----- Process all synapses -----
    for(index i = 0; i < brain->synapses_count; i++)
    {
        if(brain->neurons.neurons_signals[brain->synapses.synapses_sources[i]] > 0)
        {
            brain->neurons.neurons_potentials[brain->synapses.synapses_targets[i]] += brain->synapses.synapses_weights[i];
        }
    }
}

void BrainDelete(Brain *brain)
{
   NeuronsDelete(&brain->neurons);
   SynapsesDelete(&brain->synapses);
   
   brain->inter_neurons_count = 0;
   brain->motor_neurons_count = 0;
   brain->sensory_neurons_count = 0;
}