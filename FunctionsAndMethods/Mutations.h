#ifndef FOO_HPP
#define FOO_HPP
#include"../Structures/Individual.h"
void noMutation(Individual * I)
{
    
}
void makeItFeasible(Individual * I)
{
    I->makeTheColorationRealisable();
}
void makeItEquitable(Individual * I)
{
    I->makeTheColorationEquitableUsingHeuristicMethode();
}
void makeItFeasibleAndEquitable(Individual * I)
{
    I->makeTheColorationRealisable();
    I->makeTheColorationEquitableUsingHeuristicMethode();
    I->cal_fitness();
}
#endif
