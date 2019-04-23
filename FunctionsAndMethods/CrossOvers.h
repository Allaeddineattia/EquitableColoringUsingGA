//vector<Individual> function(Individual *,Individual *)
#ifndef CROSS_OVERS
#define CROSS_OVERS
#include"../Structures/Population.h"
#include "../Structures/Individual.h"
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
#endif



