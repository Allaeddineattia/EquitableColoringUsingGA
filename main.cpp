#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <time.h>
#include <bits/stdc++.h> 
#include "Population.h"
using namespace std;

void mutation(Individual * I){

}

vector<Individual> crossOverOX1(Individual * parent1,Individual *  parent2 ){
    int V =parent1->graph->numberofVertics;
    Graph * g= parent1->graph;
    srand(time(NULL));
    int pivot = rand() % (V-1) + 1 ;
    cout<<"le pivot: " <<pivot<<endl;
    int chromosome1 [V];
    int chromosome2 [V];
    for (int i=0; i<parent1->graph->numberofVertics; i++){
        
        if (i <= pivot){
            chromosome1[i]=parent1->chromosome[i];
            chromosome2[i]=parent2->chromosome[i];}
        else {chromosome1[i]=parent2->chromosome[i];
            chromosome2[i]=parent1->chromosome[i];
            }
    }
    vector<Individual>  childrens;
    Individual child1(g, chromosome1);
    Individual child2(g, chromosome2);
    childrens.push_back(child1);
    childrens.push_back(child2);
    cout<<childrens.size()<<endl;
    return childrens;

}

Individual * selection (Population* p){
    int p1,p2;
    p1 = rand () % p->size;
    p2 = rand () % p->size;
    if (p->population[p1] < p->population[p2])
        return p->population[p2];
    else return p->population[p1];
}
void integrateChildrenUsingSteadyStateStrategy( Population *p,vector<Individual*> childrens){
    
}

int main(){
    float temps;
    clock_t t1,t2;
    
    
    char nomFichier[255]= "../test.col";
    Graph g(nomFichier);
    //g.construire(nomFichier);
    g.printEdges();
    cout<<g.numberofVertics;
    //strcpy(g.fileName,nomFichier);
    g.printEdges();
    g.powellWelshColoring();
    g.greedyColoring();
    PopulationOptions op;
    op.maxFitness=200;
    op.maxIterations=200;
    op.mutationRate=50;
    op.initialisationOptions.equitable=false;
    op.initialisationOptions.feasible=false;
    op.mutationMethode=mutation;
    op.crossOverFunction=crossOverOX1;
    op.selectionFunction=selection;
    op.childrenIntegrationMethode=integrateChildrenUsingSteadyStateStrategy;
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

