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
#include "HeuristicEquitableColorationMethodeOptions.h"
using namespace std;

class Individual
{   
    int * sortedCopie;// of the coloration
    int counterForColorsOccurence;
    void createNewColor();
    void colorizeTheVerticByANewColor(int vertic,int newcolor,int oldColor);
    void initChromosome(int* chromosome);
    void initColorClasses();
    public:
        int maxColor;// the maximum value of colors
        Graph * graph;
        int * chromosome;//array reprsenting the coloration
        int fitness;
        int nbrOfBadEdges;
        list<int> * colorsClass;//each color have a list of vertics wich the vertics are colored by the color 
        set<int> colorSet;
        HeuristicEquitableColorationMethodeOptions heursticMethodeOptions;
        int ** colorsOccurences;// matrix nx2 wich the first colomn represent the color and the second the number of vertics colored by the color
    //----------------    
        Individual(Graph * graph, int * chromosome,HeuristicEquitableColorationMethodeOptions HeuristicEquitableColorationMethodeOptions); 
        int cal_fitness();//calculate fitness 
        int nbBadEdges();// calculate number of bad edges
        int classMax();//the color that colored the maximum number of vertics
        int classMin();//the color that colored the minimum number of vertic
        int getNbrChromatique(); // calculate the chromatic number
        void initColorsOccurence();   
        bool operator < (const Individual& I2) const{
            return(this->fitness<I2.fitness);
        };
        void makeTheColorationEquitableUsingHeuristicMethode();
        bool canColorizeTheVerticByTheColor(int vertic,int color);
        int getAVerticFromABadEdge();
        void makeTheColorationRealisable();
        void printColorSet();
        void printColorClasses();
        void printColorOccurence();
        void printFitness();
        void printChromosome();
        void print();

        
         
};





Individual::Individual(Graph * graph, int * chromosome, 
HeuristicEquitableColorationMethodeOptions heursticOptions)
{
    this->graph=graph;
    this->chromosome=new int[graph->numberofVertics+1];
    this->heursticMethodeOptions=heursticOptions;
    initChromosome(chromosome);
    initColorClasses();
    initColorsOccurence();
    cal_fitness();
};

void Individual::initChromosome(int* chromosome)
{
    maxColor=0;
    for(int i=1; i<(graph->numberofVertics)+1;i++){
        this->chromosome[i]=chromosome[i];
        colorSet.insert(chromosome[i]);
        if(maxColor<chromosome[i])maxColor=chromosome[i];
    }
};

void Individual::initColorClasses()
{
    colorsClass= new list<int>[graph->numberofVertics+1];
    for(int i=1; i<graph->numberofVertics+1;i++){
        colorsClass[chromosome[i]].push_back(i);
    }
};

void Individual::initColorsOccurence()
{
    colorsOccurences= new int * [graph->numberofVertics+1];
    counterForColorsOccurence=0;
    for(auto color:colorSet)//for each color in color set
    {
        colorsOccurences[counterForColorsOccurence]=new int [2];
        colorsOccurences[counterForColorsOccurence][0]=color;
        colorsOccurences[counterForColorsOccurence][1]=colorsClass[color].size();
        counterForColorsOccurence++;
    }
    quicksort_Matrix_Nx2(colorsOccurences,0,counterForColorsOccurence-1);
};

int Individual::cal_fitness()
{
    fitness=nbBadEdges() + (classMax()-classMin());
    return fitness;    
};

int Individual::nbBadEdges(){
    int result=0;
    for(auto &i:graph->edges)
    {
         if(chromosome[i.first]==chromosome[i.second])
         {
            result++;
        }
    } 
    nbrOfBadEdges=result;         
    return result; 
};

int Individual::classMax()
{
    return colorsOccurences[colorSet.size()-1][1];
}

int Individual::classMin()
{
    return colorsOccurences[0][1];
}


int Individual::getNbrChromatique(){
    int max=0;
    for (int i=1 ; i<graph->numberofVertics+1 ; i++){if (chromosome[i]>max) max=chromosome[i];}
    return max;
}


bool Individual::canColorizeTheVerticByTheColor(int vertic,int color)
{
    if(chromosome[vertic]==color)return false;
    for(auto aVerticColoredByColor:colorsClass[color])
    {
        for(auto aVerticPairedToVertic:graph->adj[vertic])
        {
            if (aVerticColoredByColor==aVerticPairedToVertic)
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
    //quicksort_Matrix_Nx2(colorsOccurences,0,counterForColorsOccurence-1);
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

void Individual::makeTheColorationEquitableUsingHeuristicMethode()
{
    bool changeMaked=false;
    int countUselessShuffle;
    int oldValue,uselessIteration=0,newValue;
    newValue=classMax()-classMin();
    int maxColorToAddWhenIterationExceeded=0;
    while (newValue>heursticMethodeOptions.differenceBetweenClasses )
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
        if(uselessIteration>=heursticMethodeOptions.maxUselessIteration)
        {
            if(maxColorToAddWhenIterationExceeded<heursticMethodeOptions.maxNewColorstoAddWhenMAxUselessiterationIsExceeded){
                createNewColor();
                maxColorToAddWhenIterationExceeded++;
            }
            else{
                //cout<<"Exiting because max useless iteration wish is \""<<heursticMethodeOptions.maxUselessIteration<<"\" is exceeded difference between class max is: "<<newValue<<" and numberColorAdded is "<<maxColorToAddWhenIterationExceeded<<endl;
                break;
            }
            
        }

        if(!changeMaked)
        {
            createNewColor();
        }
    }
    this->cal_fitness();
};
int Individual::getAVerticFromABadEdge(){
    for(auto &i:graph->edges)
    {
        if(chromosome[i.first]==chromosome[i.second])
        {
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
void Individual::print(){
    cout<<"individue"<<": chromaticnumber "<<colorSet.size()<<", nb bad edges:"<<this->nbBadEdges()<<", class difference: "<<this->classMax()-this->classMin()<<", fitness:"<<cal_fitness()<<endl;
}

#endif
