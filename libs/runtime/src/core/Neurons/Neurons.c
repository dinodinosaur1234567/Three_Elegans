#include "core/Neurons/Neurons.h"

void NeuronsInit(Neurons *neurons)
{
    DaSpawn(&neurons->da_neurons_potentials, sizeof(potential));
    DaSpawn(&neurons->da_neurons_thresholds, sizeof(threshold));
    DaSpawn(&neurons->da_neurons_signals, sizeof(signal));

    neurons->neurons_potentials = (potential*)neurons->da_neurons_potentials.data;
    neurons->neurons_thresholds = (threshold*)neurons->da_neurons_thresholds.data;
    neurons->neurons_signals = (signal*)neurons->da_neurons_signals.data;
}

void NeuronsDelete(Neurons *neurons)
{
    DaDelete(&neurons->da_neurons_potentials);
    DaDelete(&neurons->da_neurons_signals);
    DaDelete(&neurons->da_neurons_thresholds);

    neurons->neurons_potentials = NULL;
    neurons->neurons_thresholds = NULL;
    neurons->neurons_signals = NULL;
}