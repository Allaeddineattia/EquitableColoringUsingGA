

#include "Individual.h"
#include <bits/stdc++.h> 

class Population{
    vector<Individual> population;
    Graph * graph;
    int count=0;
    int popSize;
    void initGraph(char* nomFichier,int V);
    void initGraph(char* nomFichier,int V, int chromaticNumber);
    public:
    Population(char * nomFichier ,int V, int cardinality);
    Population(char * nomFichier ,int V, int cardinality, int chromaticNumber);
    void initPopulation();
    void addIndividual(int * colors);
    void print();
    void sortPopulationByFitness();
};

Population::Population(char * nomFichier , int V , int cardinality){
    initGraph(nomFichier,V);
    this->cardinality=cardinality;

    cout<<"the cromatique number is:"<<graph->chromaticNumber<<endl;
    initPopulation();
};


Population::Population(char * nomFichier ,int V, int cardinality, int chromaticNumber){
    initGraph(nomFichier,V,chromaticNumber);
    this->cardinality=cardinality;
    cout<<"the chromatique number is: "<<graph->chromaticNumber<<endl;
    initPopulation();
};
void Population::initGraph(char* nomFichier,int V){
    graph = new Graph(V);
    graph->construire(nomFichier);
    strcpy(graph->fileName,nomFichier);
    graph->greedyColoring();
    graph->powellWelshColoring();
    int GRmax =graph->printGRMax();
    int PWmax =graph->printPWMax();
    if(GRmax>PWmax){
        graph->chromaticNumber=PWmax;
        addIndividual(graph->PW);
    }
    else
    {
        graph->chromaticNumber=GRmax;
        addIndividual(graph->GR);

    }
};

void Population::initGraph(char* nomFichier,int V,int chromaticNumber)
{
    graph = new Graph(V);
    strcpy(graph->fileName,nomFichier);
    graph->construire(nomFichier);
    this->graph->chromaticNumber=chromaticNumber;
};

void Population::addIndividual(int * colors)
{

    Individual i=Individual(graph,colors);
    population.push_back(i);
    size++;
};


void Population::initPopulation(){
    int v=10;
    while(size<cardinality){
        cout<<size<<endl;
        v+=10;
        graph->randomColoring(v);
        cout<<"kamel"<<endl;
        addIndividual(graph->RandColors);
    }
};



// Compares two intervals according to staring times. 
bool compareIndividual(Individual i1, Individual i2) 
{ 
    return (i1.fitness < i2.fitness); 
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
        i.print();
        cout<<"}"<<endl<<endl;
    }

}

typedef struct populationOptions{
    int popsize;
    int mutationRate;
    int maxIterations;
    int maxFitness;
    void (*mutationFunction)();
    vector<Individual> (*crossOver)(Individual*,Individual*);
    Individual* (*Selection) (Individual*,Individual*);
} populationOption;


int main(){
    float temps;
    clock_t t1,t2;
    
    
    char nomFichier[255]= "DSJC1000.1.col";
    populationOption op;
    op.maxFitness=200;
    op.maxIterations=200;
    op.mutationFunction=mutation;
    op.
    // graph g();
    // population p(g,CreerIndividue_methode,fitness_func,populationStruct,)
    // Population p(nomFichier,1001,10,300);
    // p.sortPopulationByFitness();
    // p.print();

	temps = (float)(t2-t1)/CLOCKS_PER_SEC;

    return(0);


}