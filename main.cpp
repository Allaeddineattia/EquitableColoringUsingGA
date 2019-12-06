#include "FunctionsAndMethods/Selections.h"
#include "FunctionsAndMethods/Mutations.h"
#include "FunctionsAndMethods/StopCrterions.h"
#include "FunctionsAndMethods/ChildrensIntegrationsStrategies.h"
#include "FunctionsAndMethods/CrossOvers.h"
#include <bits/stdc++.h> 
#include "Structures/Population.h"
using namespace std;

void setOptions(PopulationOptions * op){

    op->maxFitness=0;
    op->popsize=50;

    op->initialisationOptions.feasible=false;
    op->initialisationOptions.equitable=false;
    
    op->heuristicEquitableColorationMethodeOptions.differenceBetweenClasses=0;
    op->heuristicEquitableColorationMethodeOptions.maxUselessIteration=50;
    op->heuristicEquitableColorationMethodeOptions.maxNewColorstoAddWhenMAxUselessiterationIsExceeded=10;
    
    op->trainOptions.maxIterations=100;
    op->trainOptions.mutationRate=90;// per cent
    op->trainOptions.stopCrterion=IterationExceededOrFitnessEqualToMaxFitnessAndNoBadEdges;
    op->trainOptions.mutationMethode=makeItFeasibleAndEquitable;
    op->trainOptions.crossOverFunction=crossOverOX1;
    op->trainOptions.selectionFunction=selectBestOfTwo;
    op->trainOptions.childrenIntegrationMethode=integrateChildrenUsingSteadyStateStrategy;
    
}
int main(){
    char nomFichier[255]= "../DSJC1000.5.col";
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
    p.population[0].printColorSet();
    cout<<"number of bad edges"<<p.population[0].nbBadEdges()<<endl;
    cout<<"result"<<endl;
    p.population[0].print();
}

