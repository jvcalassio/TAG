#ifndef W_GRAPH_H
#define W_GRAPH_H

#include <vector>
#include <map>
#include <stack>
#include <queue>

using namespace std;

class WeightedGraph{

    private:
        int n; //numero de vertices
        vector<vector<pair<int,int>>> graph;    
        map<string, int> index;              //mapa que associa um indice a cada disciplina
        stack<int> ordenacao_topologica;

        void dot2img(string file);
        bool searchEdge(queue<int> v, int i, int j);
        bool contains(queue<int> v, queue<int> u);
        void copyQueue(queue<int> &a, queue<int> &b);
        int getPathSize(queue<int> a);

    public:
        //um vetor com os codigos das materias
        WeightedGraph(int size);
        vector<vector<pair<int, int>>> getGraph();
        vector<queue<int>> getCriticalPaths();
        map<string, int> getIndexMap();
        string getName(int n);
        stack<int> getOrdenacao();
        void addEdge(string begin, string end, int weight);
        void txtInput(string file_name);
        void OrdenacaoDFS(int vertex, vector<int> &visited);
        void ordenacaoTopologica();
        void generateDAGImage();
        void generateTOImage();
        void generateCPImage();
};

#endif