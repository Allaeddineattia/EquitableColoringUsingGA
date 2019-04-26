
#ifndef POPULATION
#define POPULATION
#include "Individual.h"
#include <bits/stdc++.h> 

class Population;

typedef struct InitialisationOptions
{
    bool equitable;
    bool feasible;
}InitialisationOptions;

typedef struct PopulationOptions
{
    int popsize;
    int mutationRate;
    int maxIterations;
    int maxFitness;
    InitialisationOptions initialisationOptions;
    void (*mutationMethode)(Individual*);
    vector<Individual> (*crossOverFunction)(Individual*,Individual*);
    Individual* (*selectionFunction)(Population *);
    void (*childrenIntegrationMethode) (Population *,vector<Individual>) ;
    bool (*stopCrterion)(Population*);  
} PopulationOptions;


class Population
{
    public:
    vector<Individual > population;
    Graph * graph;
    PopulationOptions * parameters;
    int size;
    int maxFitness;
    int numberOfIterations=0;
    Population(Graph * graph, PopulationOptions * parameters);
    void initPopulation();
    void addIndividual(Individual I);
    void train();
    void mutateChildrens(vector<Individual> childrens);
    void print();
    void sortPopulationByFitness();
};


void Population::mutateChildrens(vector<Individual> childrens){
    srand(time(NULL)+10);
    for(auto & children:childrens)
    {
        int v=rand() % 100+1;
        if (v<=(parameters->mutationRate))
        {
            cout<<"before mutaion bad edges: "<<children.nbBadEdges()<<" fitness: "<<children.fitness<<endl;
            parameters->mutationMethode(&children);
            cout<<"before mutaion bad edges: "<<children.nbBadEdges()<<" fitness: "<<children.fitness<<endl;
        }
    }
};



Population::Population(Graph * graph, PopulationOptions * parameters){
    this->graph=graph;
    this->parameters=parameters;
};

void Population::initPopulation()
{
    cout<<"Initializing the Population"<<endl;
    int v=10;
    graph->greedyColoring();
    graph->powellWelshColoring();
    Individual TPW(graph,graph->PW);
    Individual TGR(graph,graph->GR);
    TGR.makeTheColorationEquitableUsingHeuristicMethode();
    TPW.makeTheColorationEquitableUsingHeuristicMethode();
    graph->chromaticNumber=TGR.colorSet.size()>TPW.colorSet.size()?TGR.colorSet.size():TPW.colorSet.size();
    while(size<=parameters->popsize){
        cout<<"Size of the Population: "<<size<<endl;
        v+=10;
        graph->randomColoring(v);
        Individual randomI(graph,graph->RandColors);
        if(parameters->initialisationOptions.feasible) 
        {
            cout<<"Making the coloration feasible."<<endl;
            randomI.makeTheColorationRealisable();
        } 
        if(parameters->initialisationOptions.equitable) 
        {
            cout<<"Making the coloration equitable."<<endl;
            randomI.makeTheColorationEquitableUsingHeuristicMethode();
        } 
        population.push_back(randomI);
        size++;
    }
    sortPopulationByFitness();
};

void Population::addIndividual(Individual I)
{
    population.push_back(I);
    size++;
    maxFitness=I.colorSet.size()>maxFitness?I.colorSet.size():maxFitness;
};

void Population::train()
{
    initPopulation();
    while(!parameters->stopCrterion(this))
    {
        Individual * parent1= parameters->selectionFunction(this);
        Individual * parent2= parameters->selectionFunction(this);
        vector<Individual> childrens = parameters->crossOverFunction(parent1,parent2);
        this->mutateChildrens(childrens);
        parameters->childrenIntegrationMethode(this,childrens);
        numberOfIterations++;
        cout<<"Iteration: "<<numberOfIterations<<endl;
    }
};









// Compares two intervals according to staring times. 
bool compareIndividual(Individual i1, Individual  i2) 
{ 
    return (i1.fitness < i2.fitness); 
} 

void Population::sortPopulationByFitness()
{
    sort(this->population.begin(), this->population.end(), compareIndividual);
}

void Population::print()
{
    int count=1;
    for(auto& i : population)
    {   
        cout<<"individue"<<count<<": chromaticnumber "<<i.colorSet.size()<<" nb bad edges:"<<i.nbBadEdges()<<"{"<<endl;
        count++;        
        i.printColorClasses();
        cout<<"}"<<endl<<endl;
    }

}
#endif
