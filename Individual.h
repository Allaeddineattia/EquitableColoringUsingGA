#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <time.h>
#include "Graphe.h"
#include "operationTableau.h"
#include <bits/stdc++.h> 
using namespace std;

class Individual
{   
    int * sortedCopie;
    
    public:
    int maxColor;
        Graph * graph;
        int * chromosome;
        int fitness;
        list<int> * colorsClass;//array of vertics indexed by colors 
        set<int> color_set;
        int ** colors_occurence;
    //----------------    
        Individual(Graph * graph, int * chromosome); 
        int cal_fitness(); 
        int nbBadEdges();
        int classMax();
        int classMin();
        int getNbrChromatique(); 
        void initColorsOccurence();  
        bool operator < (const Individual&) const;
        void printFitness();
        void printChromosome();
         
};





Individual::Individual(Graph * graph, int * chromosome){
    this->graph=graph;
    this->chromosome=new int[graph->numberofVertics];
    int i;
    maxColor=0;
    for( i=1; i<graph->numberofVertics+1;i++){
        this->chromosome[i]=chromosome[i];
        color_set.insert(chromosome[i]);
        if(maxColor<chromosome[i])maxColor=chromosome[i];
    }
    cout<<maxColor<<endl;
    colorsClass= new list<int>[maxColor+1];
    for( i=1; i<graph->numberofVertics+1;i++){
        colorsClass[chromosome[i]].push_back(i);
    }
    cout<<color_set.size()<<" ? "<<endl;
    fitness=cal_fitness();
};



void Individual::initColorsOccurence(){

    colors_occurence= new int * [maxColor];
    for (int i=1;i<=maxColor;i++){
        colors_occurence[i-1]=new int [2];
        colors_occurence[i-1][0]=i;
        colors_occurence[i-1][1]=colorsClass[i].size();
    }
    cout<<"mrigle"<<endl;
    quicksort_Matrix_Nx2(colors_occurence,0,graph->chromaticNumber-1);
};

int Individual::classMax(){
    initColorsOccurence();
    return colors_occurence[graph->chromaticNumber-1][1];
}

int Individual::classMin(){
    return colors_occurence[0][1];
}

int Individual::getNbrChromatique(){
    int max=0;
    for (int i=1 ; i<graph->numberofVertics ; i++){if (chromosome[i]>max) max=chromosome[i];}
    return max;
}

int Individual::nbBadEdges(){
    //cout<<"dkhalbad: "<<graph->fileName<<endl;
    int copie[graph->numberofVertics];
    int i;
    int result=0;
    ifstream fich(graph->fileName,ios::in);  // on ouvre le fichier en lecture
    cout<<graph->fileName;
    if(fich)  // si l'ouverture a réussi
    {
        //cout << "on a pu ouvrir le fichier\n";
        string ligne;
        int s1,s2;
        while(getline(fich, ligne)){
            if (ligne[0]=='e'){
                s1=sommet(ligne,2);
                s2=sommet(ligne,3);
                
                if(chromosome[s1]==chromosome[s2]){
                    cout<<"bad edge e "<<s1<<" "<<s2<<endl;
                    result++;
                }
            }
        }
        fich.close();  // on ferme le fichier 
    }
    else {
            cout << graph->fileName;
            cerr << "Impossible d'ouvrir le fichier !" << endl;}
    cout<<"dkhalbad"<<endl;
    return(result);      
};



int Individual::cal_fitness(){
    int max=0;
    return nbBadEdges()+(classMax()-classMin());    
};



void Individual::printFitness(){
    cout<<"fitness: "<<this->fitness<<endl;
    
};
void Individual::printChromosome(){
    for (int i=1;i<graph->numberofVertics;i++){
        cout<<"["<<i<<": "<<chromosome[i]<<"] \t";
        if(i%10==0)cout<<endl;
    }
    cout<<endl;
}

// bool Individual::operator<(const Individual& guest) const
// {
//     return this->fitness < guest.fitness;
// }
