/**
 * Joao Victor de Souza Calassio - 18/0033808
 * 117901 - Teoria e Aplicacao de Grafos - 2019/2
 * */
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <iterator>
#include <iomanip>
#include "Graph.hpp"

using namespace std;

// le o grafo do arquivo especificado
Graph::Graph(string filename) {
    vector<int> l;
    for(int i=1;i<=62;i++)
        graph.push_back(l);
        
    read_from_file(filename);   
}

void Graph::print_degree() {
    if(cols != 0 && rows != 0 && edges != 0){
        for(int i=1;i<=rows;i++){
            cout << "Grau do vertice " << i << ": " << graph[i].size() << endl;
        }
    }
}

void Graph::print_cliques() {
    vector<int> r, p, x;
    for(int i=1;i<=rows;i++)
        p.push_back(i);

    bron_kerbosch(r, p, x);
}

void Graph::print_ica() {
    float total_sum = 0;
    for(int i=1;i<=rows;i++){
        int n = graph[i].size();
        // count edges
        int t = 0;
        for(unsigned int j=0;j<graph[i].size();j++){
            for(unsigned int k=j+1;k<graph[i].size();k++){
                if( search(graph[ graph[i][j] ], graph[i][k]) ){
                    t++;
                    //printf("comparando os vertices %d e %d\n", graph[i][j], graph[i][k]);
                }
            }
        }

        float denom = n * (n - 1);
        if(denom > 0){
            float coef = (float) (2 * t) / (n * (n-1));
            cout << std::setprecision(10) << "Coeficiente de aglomeracao do no " << i << ": " << coef << endl;
            total_sum += coef;
        } else {
            cout << "Coeficiente de aglomeracao do no " << i << ": 0" << endl;
        }
    }
    cma = (float) total_sum/rows;
}

void Graph::print_cma() {
    cout << setprecision(10) << "Coeficiente medio de aglomeracao do grafo: " << cma << endl;
}

// metodos auxiliares
bool Graph::search(vector<int> &v, int l){
    for(unsigned int i=0;i<v.size();i++){
        if(v[i] == l)
            return true;
    }
    return false;
}

void Graph::read_from_file(string filename) {
    ifstream file;
    file.open(filename);
    if(file.is_open()){
        string line;

        while(getline(file,line)){
            if(line[0] != '%'){
                if(cols == 0 && rows == 0 && edges == 0){
                    sscanf(line.c_str(), "%d %d %d", &cols, &rows, &edges);
                } else {
                    // monta o grafo
                    int orig, dest;
                    sscanf(line.c_str(), "%d %d", &orig, &dest);
                    graph[orig].push_back(dest);
                    graph[dest].push_back(orig);     
                }
            }
        }
        file.close();
    }
}

void Graph::bron_kerbosch(vector<int> r, vector<int> p, vector<int> x){
    if(p.empty() && x.empty()){
        cout << "Clique maximal de " << r.size() << " vertices encontrado: ";
        print_vector(r);
    }
    
    //for(int v : p){
    auto v = p.begin();
    while(!p.empty() && v!=p.end()){
        vector<int> nv, vsolo; 
        vsolo.push_back(*v);
        nv = graph[*v];

        bron_kerbosch(uniao(r, vsolo), intersecao(p, nv), intersecao(x, nv));

        p = diferenca(p, vsolo);
        x = uniao(x, vsolo);

        if(!p.empty())
            v = p.begin();
    }
}

vector<int> Graph::uniao(vector<int> a, vector<int> b){
    vector<int> result(rows);
    sort(a.begin(), a.end());
    //sort(b.begin(), b.end()); // nao necessario pois b.size() = 1
    auto it = set_union(a.begin(), a.end(), b.begin(), b.end(), result.begin());
    vector<int> r;
    for(auto i = result.begin(); i != it; i++){
        r.push_back(*i);
    }
    return r;
}

vector<int> Graph::intersecao(vector<int> a, vector<int> b){
    vector<int> result(rows);
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    auto it = set_intersection(a.begin(), a.end(), b.begin(), b.end(), result.begin());
    vector<int> r;
    for(auto i = result.begin(); i != it; i++){
        r.push_back(*i);
    }
    return r;
}

vector<int> Graph::diferenca(vector<int> a, vector<int> b){
    vector<int> result(rows);
    sort(a.begin(), a.end());
    //sort(b.begin(), b.end()); // nao necessario pois b.size() = 1
    auto it = set_difference(a.begin(), a.end(), b.begin(), b.end(), result.begin());
    vector<int> r;
    for(auto i = result.begin(); i != it; i++){
        r.push_back(*i);
    }
    return r;
}

void Graph::print_vector(vector<int> v){
    for(int l : v)
        cout << l << " ";
    cout << endl;
}
