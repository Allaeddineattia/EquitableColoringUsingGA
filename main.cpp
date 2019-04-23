#include "FunctionsAndMethods/Selections.h"
#include "FunctionsAndMethods/Mutations.h"
#include "FunctionsAndMethods/StopCrterions.h"
#include "FunctionsAndMethods/ChildrensIntegrationsStrategies.h"
#include "FunctionsAndMethods/CrossOvers.h"
#include <bits/stdc++.h> 
#include "Structures/Population.h"
using namespace std;

void setOptions(PopulationOptions * op){
    op->maxFitness=200;
    op->maxIterations=200;
    op->mutationRate=50;
    op->initialisationOptions.equitable=false;
    op->initialisationOptions.feasible=false;
    op->mutationMethode=mutation;
    op->crossOverFunction=crossOverOX1;
    op->selectionFunction=selectBestOfTwo;
    op->childrenIntegrationMethode=integrateChildrenUsingSteadyStateStrategy;
    
}

int main(){
    float temps;
    clock_t t1,t2;
    char nomFichier[255]= "../test.col";
    Graph g(nomFichier);
    cout<<"V: "<<g.numberofVertics<<endl;
    g.printEdges();
    g.powellWelshColoring();
    g.greedyColoring();
    PopulationOptions op;
    setOptions(& op);
    Population p(&g,&op);
    cout<<p.graph->numberofVertics<<endl;
    
    Individual parent1(&g,g.GR);

    Individual parent2(&g,g.PW);
    cout<<"------parent1-----"<<endl;
    parent1.printChromosome();
    //parent1.printFitness();
    cout<<endl<<"------parent2-----"<<endl;
    parent2.printChromosome();
    //parent2.printFitness();
    vector<Individual> childrens ;
    childrens = p.parameters->crossOverFunction(&parent1,&parent2);
     cout<<childrens.size()<<endl;
    for(auto & child : childrens)
    {
        cout<<endl<<endl<<"printing child"<<endl;
        child.printChromosome();
    }
    for(int i=1;i<=parent1.maxColor;i++){
        cout<<"la couleur "<<i<<" :{"<<endl;
        for  (auto & j:parent1.colorsClass[i]){
            cout<<"la sommet:"<<j<<", ";
        }
        cout<<"}"<<endl;
    }
    // graph g();
    // population p(g,CreerIndividue_methode,fitness_func,populationStruct,)
    // Population p(nomFichier,1001,10,300);
    // p.sortPopulationByFitness();
    // p.print();

	//temps = (float)(t2-t1)/CLOCKS_PER_SEC;

    return(0);


}

