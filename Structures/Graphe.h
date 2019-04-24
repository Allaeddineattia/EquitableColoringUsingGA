// A C++ program to implement greedy algorithm for graph coloring
#ifndef GRAPH
#define GRAPH
#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <time.h>
#include <bits/stdc++.h>
using namespace std;

// A class that represents an undirected graph
class Graph
{
    int V; // No. of vertices
    public:
    int numberofVertics;
    list<pair<int,int>> edges;
	list<int> *adj; // A dynamic array of adjacency lists
    int *GR;
    int *PW;
    int *degres;
    int *PWVT;
    int *RandColors;
    int chromaticNumber=1;
    char fileName[255];
    //Adjency matrix

	// Constructor and destructor
	Graph(int V) { 
    this->V = V+1;
    numberofVertics=V;
    adj = new list<int>[V+1]; }
    Graph(char fileName[255] ){
        strcpy(this->fileName,fileName);
        this->construire(fileName);
    }
	~Graph()	 { delete [] adj; }

    // function to add an edge to graph
    void addEdge(int v, int w);

    //fonction pour la construction du graphe a partir d un fichier
    void construire(char * nomfichier);

    // Prints greedy coloring of the vertices
    void greedyColoring();
    void greedyPrintResult();
    void randomColoring(int v);
    void calculerDegres();
    void powellWelshColoring();
    void imprimer();
    bool notADJ(int x, list<int> y);
    int printGRMax();
    int printPWMax();
    void printEdges();
};


int sommet (string chaine,int ordre){
    int i,j;
    i=0;
    j=0;
    string num_s;
    while ((j < ordre) && (i< chaine.size())) {
        while (chaine[i] == ' ') i++;
        num_s="";
        while ((chaine[i]!=' ') && (i<chaine.size())) {
            num_s = num_s + chaine[i];
            i++;
        }
        j++;
    }
    if ((j == ordre) && (ordre > 0)) return (stoi(num_s));
    else return (-1);

}

void Graph::addEdge(int v, int w)
{
    edges.push_back({v,w});
	adj[v].push_back(w);
	adj[w].push_back(v); // Note: the graph is undirected
}

void skipFileHeader(ifstream * in)
{
    ifstream& IN = *in;
    string inp;
    IN >> inp;
    while (!IN.eof() && inp!="edge"){
        IN >> inp;
    }
}
int getVertixNumber(ifstream * in){
    int res;
    ifstream& IN = *in;
    IN >> res;//read number of vertixs
    //cout<<"vertix number  :"<<res<<endl;
    return res;
}
void Graph::construire(char * nomfichier){
    ifstream fich(nomfichier,ios::in);  // on ouvre le fichier en lecture
    if(fich)  // si l'ouverture a réussi
    {
        string ligne;
        int s1,s2;
        // instructions
        //cout << "on a pu ouvrir le fichier\n";
        skipFileHeader(&fich);
        numberofVertics=getVertixNumber(&fich);
        V=numberofVertics+1;
        adj = new list<int>[V+1]; 
        //cout<<V;
        while(getline(fich, ligne)){
            if (ligne[0]=='e'){
                s1=sommet(ligne,2);
                s2=sommet(ligne,3);
               // cout << "adding " << s1 << " and " << s2 << "\n";
                addEdge(s1,s2);
            }
        }

        fich.close();  // on ferme le fichier
    }
    else {
            cout << nomfichier;
            cerr << "Impossible d'ouvrir le fichier !" << endl;}
}
// Assigns colors (starting from 0) to all vertices and prints
// the assignment of colors

void Graph::greedyColoring()
{
	// Assign the first color to first vertex
    GR = (int *) calloc(V,sizeof(int));
    GR[1] = 1;

	// Initialize remaining V-1 vertices as unassigned
	for (int u = 2; u < V; u++)
        GR[u] = -1; // no color is assigned to
	// A temporary array to store the available colors. True
	// value of available[cr] would mean that the color cr is
	// assigned to one of its adjacent vertices
	bool available[V];
	for (int cr = 1; cr < V; cr++)
		available[cr] = false;

	// Assign colors to remaining V-1 vertices
	for (int u = 2; u < V; u++)
	{
        // Process all adjacent vertices and flag their colors
		// as unavailable
		list<int>::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
			if (GR[*i] != -1) available[GR[*i]] = true;

		// Find the first available color
		int cr;
		for (cr = 1; cr < V; cr++)
			if (available[cr] == false) break;

        GR[u] = cr; // Assign the found color
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
			if (GR[*i] != -1) available[GR[*i]] = false;
	}
 
    //for (int j=1;j<V;j++) cout <<GR[j]<<" ";
    cout << endl;
}


void Graph::greedyPrintResult(){//print the result

    for (int u = 1; u < V; u++)
        cout << "Sommet " << u << " ---> Color "
             << GR[u] << endl;
}

void Trier (int *S,int *D,int n){
    int j=n-1;
    int val;
    bool permut=true;
    while ((permut)&&(j>1)){
        permut = false;
        for (int i=1;i<j;i++){
            if (D[S[i]]<D[S[i+1]]) { permut =true; val=S[i]; S[i] = S[i+1];S[i+1]=val;}
        }
        j--;
    }
}

void Graph::calculerDegres(){
    degres = (int *) calloc(V,sizeof(int));
    for (int u=1 ;u < V ; u++) degres[u]= adj[u].size();
}

void Graph::imprimer(){
    list<int>::iterator i;
    for (int u = 1; u < V; u++){
        cout << u << " : ";
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            cout << *i << " ";
        cout << endl;
    }
}

bool Graph::notADJ(int x,list <int> l){
    bool nadj = true;
    list<int>::iterator i,j;
    for (i=l.begin();i!=l.end(); ++i){
        for (j=adj[*i].begin();j!=adj[*i].end(); ++j){
            if (*j==x){nadj=false;break;}
        }
        if (nadj == false) break;
    }
    return nadj;
}

void Graph::powellWelshColoring(){

    list<int>::iterator a;
    int col = 0;
    PW = (int *) calloc(V,sizeof(int));
    for (int u=1 ; u<V ; u++) 
        PW[u]=-1;
    calculerDegres();
    PWVT = (int *) calloc(V,sizeof(int));
    for (int i = 0 ; i < V ; i++) PWVT[i] = i;
    Trier(PWVT,degres,V);
    //for (int u=1;u<V;u++) cout << PWVT[u] << " ";

// coloration
    for (int k = 1 ; k < V ; k++ ){
        if (PW[PWVT[k]] == -1){
            list<int> L;
            col = col + 1;
            L.push_back(PWVT[k]);
            for (int j=k+1 ; j < V ; j++ ){
                if ((notADJ(PWVT[j],L))&& (PW[PWVT[j]] == -1)) L.push_back(PWVT[j]);
                //cout << j << " ";
            }
            for (a = L.begin(); a != L.end(); ++a) PW[*a]=col;
        }

    }
    //for (int j=1;j<V;j++) cout <<PW[j]<<" ";
    //cout << endl;
}

int Graph::printGRMax(){
    int max=0;
    for (int i=1 ; i<V ; i++){if (GR[i]>max) max=GR[i];}
    cout << "Greedy : " << max << endl;
    return max;
}
int Graph::printPWMax(){
    int max=0;
    for (int i=1 ; i<V ; i++){if (PW[i]>max) max=PW[i];}
    cout << "Powell_Welsh : " << max << endl;
    return max;
}

void Graph::randomColoring(int v){

    srand(time(NULL)+v);
    RandColors= new int[V];
    RandColors[0]=0;
    for (int i=1;i<V;i++) {
        RandColors[i]= rand() % chromaticNumber+1;   
    }
};

void Graph::printEdges(){
    for(auto &i:edges){
        cout<<"e "<<i.first<<" "<<i.second<<endl;
    }

};
#endif
