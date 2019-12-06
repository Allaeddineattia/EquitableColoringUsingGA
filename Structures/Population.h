
#ifndef POPULATION
#define POPULATION
#include "Individual.h"
#include <bits/stdc++.h> 
#include "PopulationOptions.h"


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
    vector<Individual> mutateChildrens(vector<Individual> childrens);
    void print();
    void sortPopulationByFitness();
};


vector<Individual> Population::mutateChildrens(vector<Individual> childrens){
    srand(time(NULL)+10);
    vector<Individual> result;
    for(auto & children:childrens)
    {
        int v=rand() % 100+1;
        if (v<=(parameters->trainOptions.mutationRate))
        {
            // cout<<"before mutaion bad edges: ";
            // children.print();
            parameters->trainOptions.mutationMethode(&children);
            // cout<<"after mutaion bad edges: "<<endl;
            // children.print();
        }
        result.push_back(children);
    }
    cout<<"New childrens Are: "<<endl;
    for(auto & children:result){
        children.print();
    }
    return result;
};



Population::Population(Graph * graph, PopulationOptions * parameters){
    this->graph=graph;
    this->parameters=parameters;
};

void Population::initPopulation()
{
    cout<<"Initializing the Population"<<endl;
    int v=10;
    cout<<"Coloring the graph using the greed way "<<endl;
    graph->greedyColoring();
    cout<<"Coloring the graph using the powerWelsh way "<<endl;
    graph->powellWelshColoring();
    cout<<"Creating an individual based on PW coloring"<<endl;
    Individual TPW(graph,graph->PW,parameters->heuristicEquitableColorationMethodeOptions);
    cout<<"Creating an individual based on Creedy coloring"<<endl;
    Individual TGR(graph,graph->GR,parameters->heuristicEquitableColorationMethodeOptions);
    TGR.makeTheColorationEquitableUsingHeuristicMethode();
    cout<<"Chromatique number of Greedy after making it Equitable: "<<TGR.colorSet.size()<<endl;
    TPW.makeTheColorationEquitableUsingHeuristicMethode();
    cout<<"Chromatique number of PW after making it Equitable: "<<TPW.colorSet.size()<<endl;
    graph->chromaticNumber=TGR.colorSet.size()>TPW.colorSet.size()?TGR.colorSet.size():TPW.colorSet.size();
    population.push_back(TPW);
    population.push_back(TPW);
    size += 2;
    while(size<parameters->popsize){
        cout<<"Creating Member of population number: "<<size<<endl;
        v+=10;
        graph->randomColoring(v);
        Individual randomI(graph,graph->RandColors,parameters->heuristicEquitableColorationMethodeOptions);
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
    while(!parameters->trainOptions.stopCrterion(this))
    {
        Individual * parent1= parameters->trainOptions.selectionFunction(this);
        Individual * parent2= parameters->trainOptions.selectionFunction(this);
        vector<Individual> childrens = parameters->trainOptions.crossOverFunction(parent1,parent2);
        vector<Individual> mutatedChildrens = this->mutateChildrens(childrens);
        parameters->trainOptions.childrenIntegrationMethode(this,mutatedChildrens);
        numberOfIterations++;
        cout<<"Iteration: "<<numberOfIterations<<": "<<this->population[0].colorSet.size()<<endl;
        cout<<"New populotion:"<<endl; this->print();
    }
};









// Compares two intervals according to staring times. 
bool compareIndividual(Individual i1, Individual  i2) 
{ 
    i1.cal_fitness();
    i2.cal_fitness();
    if(i1.fitness == i2.fitness){
        return (i1.colorSet.size()<i2.colorSet.size());
    }
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
        i.print();
        count++;        
        //i.printColorClasses();
        //cout<<"}"<<endl<<endl;
    }

}
#endif
