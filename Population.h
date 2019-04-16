

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
    void (*childrenIntegrationMethode) (Population *,vector<Individual*>) ;
    bool (*stopCrterion)(Population*);  
} PopulationOptions;



class Population{
    private:

    public:
    vector<Individual * > population;
    Graph * graph;
    PopulationOptions * parameters;
    int count=0;
    int size;
    // void initGraph(char* nomFichier,int V);
    // void initGraph(char* nomFichier,int V, int chromaticNumber);
    // Population(char * nomFichier ,int V, int size);
    // Population(char * nomFichier ,int V, int size, int chromaticNumber);
    Population(Graph * graph, PopulationOptions * parameters);
    void initPopulation();
    void addIndividual(int * colors);
    void train();
    void mutateChildrens(vector<Individual*> childrens);
    void print();
    void sortPopulationByFitness();
};

// Population::Population(char * nomFichier , int V , int size){
//     initGraph(nomFichier,V);
//     this->size=size;

//     cout<<"the cromatique number is:"<<graph->chromaticNumber<<endl;
//     initPopulation();
// };

void Population::mutateChildrens(vector<Individual*> childrens){

};


// Population::Population(char * nomFichier ,int V, int size, int chromaticNumber){
//     initGraph(nomFichier,V,chromaticNumber);
//     this->size=size;
//     cout<<"the chromatique number is: "<<graph->chromaticNumber<<endl;
//     initPopulation();
// };

Population::Population(Graph * graph, PopulationOptions * parameters){
    this->graph=graph;
    this->parameters=parameters;
};
void Population::train(){
    initPopulation();
    while(!parameters->stopCrterion(this)){
        Individual * parent1= parameters->selectionFunction(this);
        Individual * parent2= parameters->selectionFunction(this);
        parent1->printChromosome();
        parent2->printChromosome();
        vector<Individual*> childrens ;
        //parameters->crossOverFunction(parent1,parent2,childrens);
        this->mutateChildrens(childrens);
        parameters->childrenIntegrationMethode(this,childrens);
    }
};
// void Population::initGraph(char* nomFichier,int V){
//     graph = new Graph(V);
//     graph->construire(nomFichier);
//     strcpy(graph->fileName,nomFichier);
//     graph->greedyColoring();
//     graph->powellWelshColoring();
//     int GRmax =graph->printGRMax();
//     int PWmax =graph->printPWMax();
//     if(GRmax>PWmax){
//         graph->chromaticNumber=PWmax;
//         addIndividual(graph->PW);
//     }
//     else
//     {
//         graph->chromaticNumber=GRmax;
//         addIndividual(graph->GR);

//     }
// };

// void Population::initGraph(char* nomFichier,int V,int chromaticNumber)
// {
//     graph = new Graph(V);
//     strcpy(graph->fileName,nomFichier);
//     graph->construire(nomFichier);
//     this->graph->chromaticNumber=chromaticNumber;
// };

void Population::addIndividual(int * colors)
{

    Individual i=Individual(graph,colors);
    population.push_back(& i);
    size++;
};


void Population::initPopulation(){
    
    int v=10;
    while(size<size){
        cout<<size<<endl;
        v+=10;
        graph->randomColoring(v);
        if(parameters->initialisationOptions.feasible) //make it feasible;
        if(parameters->initialisationOptions.equitable) //make it equitable;
        cout<<"kamel"<<endl;
        addIndividual(graph->RandColors);
    }
};



// Compares two intervals according to staring times. 
bool compareIndividual(Individual * i1, Individual * i2) 
{ 
    return (i1->fitness < i2->fitness); 
} 

void Population::sortPopulationByFitness(){
    sort(this->population.begin(), this->population.end(), compareIndividual);
}

void Population::print(){
    int count=1;
    for(auto&& i : population)
    {   
        cout<<"individue"<<count<<": {"<<endl;
        count++;        
        i->printChromosome();
        cout<<"}"<<endl<<endl;
    }

}




