#include "FunctionsAndMethods/Selections.h"
#include "FunctionsAndMethods/Mutations.h"
#include "FunctionsAndMethods/StopCrterions.h"
#include "FunctionsAndMethods/ChildrensIntegrationsStrategies.h"
#include "FunctionsAndMethods/CrossOvers.h"
#include <bits/stdc++.h> 
#include "Structures/Population.h"
using namespace std;



// PopulationOptions
// {
//     int popsize;
//     int mutationRate; 
//     int maxIterations;
//     int maxFitness;
//     initialisationOptions {
//                                  bool equitable;
//                                  bool feasible;
//                                  };
//     void (*mutationMethode)(Individual*);// methode de mutation
//     vector<Individual> (*crossOverFunction)(Individual*,Individual*);// Fonction de Cross over
//     Individual* (*selectionFunction)(Population *);// Fonction de selection 
//     void (*childrenIntegrationMethode) (Population *,vector<Individual>); Methode d'integration des enfants 
//     bool (*stopCrterion)(Population*);  // critere de stop
// }

// int main(){
//     float temps;
//     clock_t t1,t2;
//     char nomFichier[255]= "../test.col";
//     Graph g(nomFichier);
//     PopulationOptions op;
//     Population p(&g,&op);
//     p.train();
//     p.printFinalResult();

//     return(1);


// }


void setOptions(PopulationOptions * op){
    op->maxFitness=200;
    op->maxIterations=200;
    op->mutationRate=50;
    op->popsize=50;
    op->initialisationOptions.feasible=true;
    op->initialisationOptions.equitable=true;
    
    op->mutationMethode=mutation;
    op->crossOverFunction=crossOverOX1;
    op->selectionFunction=selectBestOfTwo;
    op->childrenIntegrationMethode=integrateChildrenUsingSteadyStateStrategy;
    
}
int main(){
    char nomFichier[255]= "../DSJC1000.1.col";
    Graph g(nomFichier);
    PopulationOptions op;
    setOptions(& op);
    Population p(&g,&op);
    cout<<"you choose the initialsization to Be:"<<endl;
    if(op.initialisationOptions.equitable){
        cout<<"Equitable"<<endl;
    }else{
        cout<<"Non Equitable"<<endl;
    }
    if(op.initialisationOptions.equitable){
        cout<<"Feasible"<<endl;
    }else{
        cout<<"Non Feasible"<<endl;
    }
    p.train();
    p.print();
}

// int main(){
//     float temps;
//     clock_t t1,t2;
//     char nomFichier[255]= "../DSJC1000.1.col";
//     Graph g(nomFichier);
//     cout<<"V: "<<g.numberofVertics<<endl;
//     //g.printEdges();
//     g.powellWelshColoring();
//     g.greedyColoring();
//     PopulationOptions op;
//     setOptions(& op);
//     Population p(&g,&op);
//     cout<<p.graph->numberofVertics<<endl;
    
//     Individual parent1(&g,g.GR);
    
//     Individual parent2(&g,g.PW);
    
//     cout<<"------parent1-----"<<endl;
//     parent1.printChromosome();
//     cout<<"chromatique number Begin: "<<parent1.colorSet.size()<<"\n\n\n\n";
//     parent1.makeTheColorationEquitableUsingHeuristicMethode();
//     cout<<"nbr bad edges: "<<parent1.nbBadEdges()<<endl;
//     parent1.printChromosome();
//     cout<<"\n\n\nnchromatique number END: "<<parent1.colorSet.size()<<"\n\n\n\n";
//     //parent1.printFitness();
//     cout<<endl<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n------parent2-----"<<endl;
//     cout<<"chromatique number Begin: "<<parent2.colorSet.size()<<"\n\n\n\n";
//     parent2.printChromosome();
//     parent2.makeTheColorationEquitableUsingHeuristicMethode();
//     cout<<"nbr bad edges: "<<parent2.nbBadEdges()<<endl;
//     parent2.printChromosome();
//     cout<<"\n\n\nnchromatique number END: "<<parent2.colorSet.size()<<"\n\n\n\n";
    
    
//     //parent2.printFitness();
//     // vector<Individual> childrens ;
//     // childrens = p.parameters->crossOverFunction(&parent1,&parent2);
//     //  cout<<childrens.size()<<endl;
//     // for(auto & child : childrens)
//     // {
//     //     cout<<endl<<endl<<"printing child"<<endl;
//     //     child.printChromosome();
//     // }
//     // for(int i=1;i<=parent1.maxColor;i++){
//     //     cout<<"la couleur "<<i<<" :{"<<endl;
//     //     for  (auto & j:parent1.colorsClass[i]){
//     //         cout<<"la sommet:"<<j<<", ";
//     //     }
//     //     cout<<"}"<<endl;
//     // }
//     // graph g();
//     // population p(g,CreerIndividue_methode,fitness_func,populationStruct,)
//     // Population p(nomFichier,1001,10,300);
//     // p.sortPopulationByFitness();
//     // p.print();

// 	//temps = (float)(t2-t1)/CLOCKS_PER_SEC;

//     return(0);


// }

// int main (){
//     char nomFichier[255]= "../DSJC1000.1.col";
//     Graph g(nomFichier);
    
//     g.greedyColoring();
//     g.powellWelshColoring();
//     Individual TPW(&g,g.PW);
//     Individual TGR(&g,g.GR);
//     TGR.makeTheColorationEquitableUsingHeuristicMethode();
//     TPW.makeTheColorationEquitableUsingHeuristicMethode();
//     g.chromaticNumber=TGR.colorSet.size()>TPW.colorSet.size()?TGR.colorSet.size():TPW.colorSet.size();
//     g.randomColoring(10);
//     Individual I1(&g,g.RandColors) ;
//     I1.printColorClasses();
//     cout<<"chromatic number"<<I1.colorSet.size()<<endl;
//     cout<<"Nbr Bad edges Begin: "<<I1.nbBadEdges()<<endl;
//     I1.makeTheColorationRealisable();
    
//     I1.printColorClasses();
//     cout<<"chromatic number"<<I1.colorSet.size()<<endl;
//     cout<<"Nbr Bad edges End: "<<I1.nbBadEdges()<<endl;

//     I1.makeTheColorationEquitableUsingHeuristicMethode();
//     I1.printColorClasses();
//     cout<<"chromatic number"<<I1.colorSet.size()<<endl;
//     cout<<"Nbr Bad edges End: "<<I1.nbBadEdges()<<endl;
//     return 1;
// }

