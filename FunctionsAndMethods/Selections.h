#ifndef SELECTIONS
#define SELECTIONS
#include"../Structures/Population.h"
#include"../Structures/Individual.h"

Individual * selectBestOfTwo (Population* p)
{
    int p1,p2;
    p1 = rand () % p->size;
    p2 = rand () % p->size;
    if (p->population[p1].fitness < p->population[p2].fitness)
        return &(p->population[p2]);
    else return &(p->population[p1]);
}
#endif
