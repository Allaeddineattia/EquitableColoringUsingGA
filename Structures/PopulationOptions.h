#ifndef POPULATION_OPTIONS
#define POPULATION_OPTIONS
#include <bits/stdc++.h> 
#include "Population.h"
#include "HeuristicEquitableColorationMethodeOptions.h"
class Population;
typedef struct InitialisationOptions
{
    bool equitable;
    bool feasible;
}InitialisationOptions;

typedef struct TrainOptions
{   
    int mutationRate;
    int maxIterations;
    void (*mutationMethode)(Individual*);
    vector<Individual> (*crossOverFunction)(Individual*,Individual*);
    Individual* (*selectionFunction)(Population *);
    void (*childrenIntegrationMethode) (Population *,vector<Individual>) ;
    bool (*stopCrterion)(Population*); 

}TrainOptions;

typedef struct PopulationOptions
{
    InitialisationOptions initialisationOptions;
    TrainOptions trainOptions;
    HeuristicEquitableColorationMethodeOptions heuristicEquitableColorationMethodeOptions;
    int popsize;
    int maxFitness;
    
     
} PopulationOptions;
#endif