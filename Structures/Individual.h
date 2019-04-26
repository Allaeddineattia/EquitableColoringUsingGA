#ifndef INDIVIDUAL
#define INDIVIDUAL
#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <time.h>
#include "Graphe.h"
#include "../FunctionsAndMethods/operationTableau.h"
#include <bits/stdc++.h> 
using namespace std;

class Individual
{   
    int * sortedCopie;
    int counterForColorsOccurence;
    void createNewColor();
    void colorizeTheVerticByANewColor(int vertic,int newcolor,int oldColor);
    public:
        int maxColor;
        Graph * graph;
        int * chromosome;
        int fitness;
        int nbrOfBadEdges;
        list<int> * colorsClass;//array of vertics indexed by colors 
        set<int> colorSet;
        int ** colorsOccurences;
    //----------------    
        Individual(Graph * graph, int * chromosome); 
        int cal_fitness(); 
        int nbBadEdges();
        int classMax();
        int classMin();
        int getNbrChromatique(); 
        void initColorsOccurence();  
        bool operator < (const Individual& I2) const{
            return(this->fitness<I2.fitness);
        };
        void printFitness();
        void printChromosome();
        void makeTheColorationEquitableUsingHeuristicMethode();
        bool canColorizeTheVerticByTheColor(int vertic,int color);
        int getAVerticFromABadEdge();
        void makeTheColorationRealisable();
        void printColorSet();
        void printColorClasses();
        void printColorOccurence();
         
};





Individual::Individual(Graph * graph, int * chromosome){
    this->graph=graph;
    this->chromosome=new int[graph->numberofVertics+1];
    colorsClass= new list<int>[graph->numberofVertics+1];
    int i;
    maxColor=0;
    for( i=1; i<(graph->numberofVertics)+1;i++){
        this->chromosome[i]=chromosome[i];
        colorSet.insert(chromosome[i]);
        if(maxColor<chromosome[i])maxColor=chromosome[i];
    }
    for( i=1; i<graph->numberofVertics+1;i++){
        colorsClass[chromosome[i]].push_back(i);
    }
    colorsOccurences= new int * [graph->numberofVertics+1];
    initColorsOccurence();
    cal_fitness();
};



void Individual::initColorsOccurence(){

    
    counterForColorsOccurence=0;
    for(auto x:colorSet){
        colorsOccurences[counterForColorsOccurence]=new int [2];
        colorsOccurences[counterForColorsOccurence][0]=x;
        colorsOccurences[counterForColorsOccurence][1]=colorsClass[x].size();
        counterForColorsOccurence++;
    }
    quicksort_Matrix_Nx2(colorsOccurences,0,counterForColorsOccurence-1);
};

int Individual::classMax(){
    return colorsOccurences[colorSet.size()-1][1];
}

int Individual::classMin(){
    return colorsOccurences[0][1];
}

int Individual::getNbrChromatique(){
    int max=0;
    for (int i=1 ; i<graph->numberofVertics+1 ; i++){if (chromosome[i]>max) max=chromosome[i];}
    return max;
}

int Individual::nbBadEdges(){
    int result=0;
    for(auto &i:graph->edges){
         if(chromosome[i.first]==chromosome[i.second]){
            result++;
        }
    } 
    nbrOfBadEdges=result;         
    return result; 
};



int Individual::cal_fitness(){
    
    fitness=nbBadEdges()+(classMax()-classMin());
    return fitness;    
};





bool Individual::canColorizeTheVerticByTheColor(int vertic,int color)
{
    if(chromosome[vertic]==color)return false;
    for(auto verticsColoredByColor:colorsClass[color]){
        for(auto verticsPairedToVertic:graph->adj[vertic]){
            if (verticsColoredByColor==verticsPairedToVertic)
            return false;
        }
    }
    
    return true;
}

void Individual::colorizeTheVerticByANewColor(int vertic,int newColor,int oldColor)
{
    colorsClass[oldColor].remove(vertic);
    colorsClass[newColor].push_back(vertic);
    chromosome[vertic]=newColor;
    initColorsOccurence();
    quicksort_Matrix_Nx2(colorsOccurences,0,counterForColorsOccurence-1);
}

void Individual::createNewColor()
{
    maxColor++;
    int x =maxColor;
    colorSet.insert(maxColor);
    colorsOccurences[counterForColorsOccurence]=new int [2];
    colorsOccurences[counterForColorsOccurence][0]=x;
    colorsOccurences[counterForColorsOccurence][1]=colorsClass[x].size();
    //cout<<colorsOccurences[counterForColorsOccurence][0]<<" "<<colorsOccurences[counterForColorsOccurence][1]<<endl;
    counterForColorsOccurence++;
    quicksort_Matrix_Nx2(colorsOccurences,0,counterForColorsOccurence-1);
}

void Individual::makeTheColorationEquitableUsingHeuristicMethode(){
    bool changeMaked=false;
    int countUselessShuffle;
    int oldValue,uselessIteration=0,newValue;
    newValue=classMax()-classMin();
    while (newValue>1)
    {
        changeMaked=false;
        oldValue=newValue;
        for(int i = colorSet.size()-1 ;i>=colorSet.size()/2,colorsOccurences[i][1]==classMax() ;i--)
        {
            //cout<<"first for loop: "<<i<<"=="<<colorSet.size()/2<<endl;
            for(auto & vertic:colorsClass[colorsOccurences[i][0]])
            {
                //cout<<"second for loop: "<<vertic<<endl;
                for(int j = 0;j<=colorSet.size()/2,colorsOccurences[j][1]==classMin();j++ )
                {
                    //cout<<"first for loop: "<<j<<"=="<<colorSet.size()/2<<endl;
                    if(canColorizeTheVerticByTheColor(vertic,colorsOccurences[j][0]))
                    {  
                        //cout<<"can change"<<endl;
                        colorizeTheVerticByANewColor(vertic,colorsOccurences[j][0],colorsOccurences[i][0]);
                        changeMaked=true;
                    }
                }
                if(changeMaked)break;
            }
        }
        newValue=classMax()-classMin();
        if(newValue==oldValue)
        {
            uselessIteration++;
        }
        if(uselessIteration>=70)
        {
            cout<<"Exiting because max useless iteration in equitable is exceeded difference between class max is: "<<newValue<<endl;
            break;
        }
        if(!changeMaked)
        {
            createNewColor();
        }
    }
};
int Individual::getAVerticFromABadEdge(){
    for(auto &i:graph->edges){
         if(chromosome[i.first]==chromosome[i.second]){
            return(i.first);
        }
    }          
    return 0; 
};

void Individual::makeTheColorationRealisable(){
    bool changeMaked=false;
    int countUselessShuffle;
    int vertic = getAVerticFromABadEdge();
    while (vertic)
    {

        changeMaked=false;
        
        for(int j = 0;j<colorSet.size();j++ )
        {
            if(canColorizeTheVerticByTheColor(vertic,colorsOccurences[j][0]))
            {  
                colorizeTheVerticByANewColor(vertic,colorsOccurences[j][0],chromosome[vertic]);
                changeMaked=true;
            }
        }
        if(!changeMaked)
        {
            createNewColor();
        }
        vertic = getAVerticFromABadEdge();
    }
};

void Individual::printFitness(){
    cout<<"fitness: "<<this->fitness<<endl;
    
};

void Individual::printColorSet(){
    cout<<"the color set is:{ ";
    for (auto &x: colorSet){
        cout<<x<<", ";
    }
    cout<<"}\n";
}

void Individual::printColorClasses(){
    cout<<"The color classes are below:"<<endl;
    for (auto &x: colorSet){
        cout<<x<<" "<<colorsClass[x].size()<<" : [";
        for(auto &y:colorsClass[x]){
            cout<<y<<", ";
        }
        cout<<"]"<<endl;
    }
}
void Individual::printColorOccurence(){
    cout<<"colorSet size: "<<colorSet.size()<<endl;
    for(int i=0;i<colorSet.size();i++){
        cout<<"["<<colorsOccurences[i][0]<<" , "<<colorsOccurences[i][1]<<"] ";
    }
    cout<<endl;
}

void Individual::printChromosome(){
    cout<<"the colortion is:"<<endl;
    for (int i=1;i<graph->numberofVertics+1;i++){
        cout<<"["<<i<<": "<<chromosome[i]<<"] \t";
        if(i%9==0)cout<<endl;
    }
    cout<<endl;
}

#endif
