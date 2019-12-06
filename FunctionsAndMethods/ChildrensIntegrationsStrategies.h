#ifndef CHILDRENS_INTEGRATION_STRATEGIES
#define CHILDRENS_INTEGRATION_STRATEGIES
#include "../Structures/Population.h"
#include "../Structures/Individual.h"
void integrateChildrenUsingSteadyStateStrategy( Population *p,vector<Individual> childrens)
{
    for(auto & children:childrens)
    {
        p->population.push_back(children);
    } 
    // cout<<"Before sorting"<<endl;
    // p->print();
    p->sortPopulationByFitness();
    //cout<<"After sorting"<<endl;
    //p->print();
    p->population.erase((p->population.begin())+(p->parameters->popsize), p->population.end());
    //cout<<"After deleting"<<endl;
    //p->print();
}
#endif
