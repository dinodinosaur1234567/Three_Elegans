#include "core/Synapses/Synapses.h"

void SynapsesInit(Synapses *synapses)
{
    DaSpawn(&synapses->da_synapses_sources, sizeof(index));
    DaSpawn(&synapses->da_synapses_weights, sizeof(weight));
    DaSpawn(&synapses->da_synapses_targets, sizeof(index));

    synapses->synapses_sources = (index*)synapses->da_synapses_sources.data;
    synapses->synapses_weights = (weight*)synapses->da_synapses_weights.data;
    synapses->synapses_targets = (index*)synapses->da_synapses_targets.data;
}

void SynapsesDelete(Synapses *synapses)
{
    DaDelete(&synapses->da_synapses_sources);
    DaDelete(&synapses->da_synapses_weights);
    DaDelete(&synapses->da_synapses_targets);

    synapses->synapses_sources = NULL;
    synapses->synapses_weights = NULL;
    synapses->synapses_targets = NULL;
}