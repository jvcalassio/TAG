#ifndef W_GRAPH_H
#define W_GRAPH_H

#include <vector>
#include <map>

using namespace std;

class WeightedGraph{

    private:
        int n; //numero de vertices
        vector<vector<pair<int,int>>> graph;    
        map<string, int> index;              //mapa que associa um indice a cada disciplina

    public:
        //um vetor com os codigos das materias
        WeightedGraph(int size);
        void addEdge(string begin, string end, int weight);
        void txtInput(string file_name);
        vector<vector<pair<int, int>>> getGraph();
        map<string, int> getIndexMap();

};

#endif