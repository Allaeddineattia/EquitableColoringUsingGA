
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
    Population(Graph * graph, PopulationOptions * parameters);
    void initPopulation();
    void addIndividual(int * colors);
    void train();
    void mutateChildrens(vector<Individual> childrens);
    void print();
    void sortPopulationByFitness();
};


void Population::mutateChildrens(vector<Individual> childrens){

};



Population::Population(Graph * graph, PopulationOptions * parameters){
    this->graph=graph;
    this->parameters=parameters;
};

void Population::initPopulation(){
    
    int v=10;
    graph->greedyColoring();
    graph->powellWelshColoring();
    Individual TPW(graph,graph->PW);
    Individual TGR(graph,graph->GR);
    TGR.makeTheColorationEquitableUsingHeuristicMethode();
    TPW.makeTheColorationEquitableUsingHeuristicMethode();
    graph->chromaticNumber=TGR.colorSet.size()>TPW.colorSet.size()?TGR.colorSet.size():TPW.colorSet.size();
    while(size<=parameters->popsize){
        cout<<size<<endl;
        v+=10;
        graph->randomColoring(v);
        Individual randomI(graph,graph->RandColors);
        if(parameters->initialisationOptions.feasible) 
        {
            cout<<"Make the coloration feasible"<<endl;
            randomI.makeTheColorationRealisable();
        } 
        if(parameters->initialisationOptions.equitable) {
            cout<<"Make the coloration equitable"<<endl;
            randomI.makeTheColorationEquitableUsingHeuristicMethode();
        } 
        population.push_back(randomI);
        size++;
    }
};
void Population::train(){
    initPopulation();
    // while(!parameters->stopCrterion(this)){
    //     Individual * parent1= parameters->selectionFunction(this);
    //     Individual * parent2= parameters->selectionFunction(this);
    //     parent1->printChromosome();
    //     parent2->printChromosome();
    //     vector<Individual> childrens = this->parameters->crossOverFunction(parent1,parent2);
    //     //parameters->crossOverFunction(parent1,parent2,childrens);
    //     this->mutateChildrens(childrens);
    //     parameters->childrenIntegrationMethode(this,childrens);
    // }
};


void Population::addIndividual(int * colors)
{

    Individual i=Individual(graph,colors);
    population.push_back(i);
    size++;
};






// Compares two intervals according to staring times. 
bool compareIndividual(Individual i1, Individual  i2) 
{ 
    return (i1.fitness < i2.fitness); 
} 

void Population::sortPopulationByFitness(){
    sort(this->population.begin(), this->population.end(), compareIndividual);
}

void Population::print(){
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
