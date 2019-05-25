// bool function(Population*); 
#ifndef STOP_CRTERIONS
#define STOP_CRTERIONS
#include"../Structures/Population.h"
 
bool alwaysTrue(Population * p)
{
    return true;
}

bool IterationExceeded(Population * p)
{
    return p->numberOfIterations==p->parameters->trainOptions.maxIterations;
}

bool FitnessEqualToMaxFitnessAndNoBadEdges (Population * p)
{
    return 
    p->population[0].fitness==p->parameters->maxFitness && 
    p->population[0].nbrOfBadEdges==0;
}

bool IterationExceededOrFitnessEqualToMaxFitnessAndNoBadEdges (Population * p)
{
    return p->numberOfIterations==p->parameters->trainOptions.maxIterations || 
    p->population[0].fitness==p->parameters->maxFitness && 
    p->population[0].nbrOfBadEdges==0;
}

bool FitnessEqualToMaxFitness (Population * p)
{
    return p->population[0].fitness==p->parameters->maxFitness;
}

bool IterationExceededOrFitnessEqualToMaxFitness (Population * p)
{
    return p->numberOfIterations==p->parameters->trainOptions.maxIterations || 
    p->population[0].fitness==p->parameters->maxFitness;
}
#endif
