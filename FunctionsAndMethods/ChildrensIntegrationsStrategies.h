#ifndef MUTATIONS
#define MUTATIONS
#include "../Structures/Population.h"
#include "../Structures/Individual.h"
void integrateChildrenUsingSteadyStateStrategy( Population *p,vector<Individual> childrens)
{
    for(auto & children:childrens)
    {
        p->population.push_back(children);
    } 
    p->sortPopulationByFitness();
    p->population.erase(p->population.begin()+p->parameters->popsize, p->population.end());
}
#endif
