#include "WeightedGraph.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
#include <queue>
#include <algorithm>
#include <stdlib.h>

using namespace std;

WeightedGraph::WeightedGraph(int size){
    n = size;
    graph.resize(size);
}

void WeightedGraph::addEdge(string begin, string end, int weight){

    if(!index.count(begin)){
        index[begin] = index.size();
    }
    if(!index.count(end)){
        index[end] = index.size();
    }
    // index["117901"] = ordem de aparicao no arquivo texto.
    // index["113476"] = 0, index["116319"] = 1
    // graph[0] = {1, 6}; ------- ligacao do vertice 0 ao vertice 1 com peso 6
    int b = index[begin];
    int e = index[end];
    graph[b].push_back(make_pair(e, weight));
}

void WeightedGraph::txtInput(string file_name){

    ifstream input_file;
    input_file.open(file_name);
    
    if(input_file.fail()){
        cout << "Error opening file" << endl;
    }
    else{
        string line;
        while(getline(input_file, line)){
            
            string begin, end;
            int weight;
            stringstream stream(line);
            stream >> begin >> end >> weight;
            addEdge(begin, end, weight);

            line.clear();
        }
    }
}

vector<queue<int>> WeightedGraph::getCriticalPaths() {
    queue<int> longest_path;
    queue<int> slongest_path;

    // testa a distancia de todos os vertices para todos os vertices
    for(int k=0;k<graph.size();k++) {

        vector<int> dist(graph.size(), -1e9); // distancias de k a todos os vertices
        vector<int> temp_origs(graph.size());

        priority_queue<pair<int,int>, vector<pair<int,int>>, less<pair<int,int>>> pq;

        dist[k] = 0;
        temp_origs[k] = -1;
        pq.emplace(dist[k], k);

        // dijikstra p/ maior caminho
        while(!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            for(pair<int,int> edge : graph[u]) {
                int v = edge.first;
                int dv = edge.second;

                if(dist[v] < dist[u] + dv) {
                    dist[v] = dist[u] + dv;
                    temp_origs[v] = u;
                    pq.emplace(dist[v], v);
                }
            }
        }

        int tmax_dist = -1e9;
        int tmax_node = 0;
        for(int i=0;i<dist.size();i++) { // decisao do vertice mais distante de k
            if(dist[i] > tmax_dist) {
                tmax_dist = dist[i];
                tmax_node = i;
            }
        } 

        // testar todos os caminhos de k ate tmax_node, colocar o maior em longest_path e o segundo maior em slongest_path
        // retornar ambos
        if(tmax_dist > getPathSize(longest_path)) {
            // faz caminho
            copyQueue(longest_path, slongest_path);

            int it = tmax_node;
            while(it != k) {
                longest_path.push(it);
                it = temp_origs[it];
            }
            longest_path.push(it);
        } else if(tmax_dist > getPathSize(slongest_path)) {
            // computa caminho
            queue<int> temp_smax;
            int it = tmax_node;
            while(it != k) {
                temp_smax.push(it);
                it = temp_origs[it];
            }
            temp_smax.push(it);

            // se nao for subcaminho do maior caminho, salva
            if(!contains(longest_path, temp_smax)) {
                copyQueue(temp_smax, slongest_path);
            }
        }
    }

    vector<queue<int>> res;
    res.push_back(longest_path);
    res.push_back(slongest_path);
    return res;
}


void WeightedGraph::OrdenacaoDFS(int start, vector<int> &visited){
    visited[start] = 1;
    for(pair<int,int> edge : graph[start]){
        if(!visited[edge.first]){
            OrdenacaoDFS(edge.first, visited);
        }
    }
    string vname = getName(start);
    if(vname != "0" && vname != "")
        ordenacao_topologica.push(start);
}

void WeightedGraph::ordenacaoTopologica() {
    vector<int> visited(graph.size(), 0);

    for(int i = 0; i<graph.size(); i++){
        if(!visited[i]){
            OrdenacaoDFS(i, visited);
        }
    }
}
/*******************************************************************
 * Geracao de Imagens
 * *****************************************************************/

// directed acyclic graph
void WeightedGraph::generateDAGImage() {
    string to_print = "digraph CIC { labelloc=\"t\"; label=\"Ciencia da Computacao\";\n";
    for(int i=0;i<graph.size();i++) {
        string srcnode = getName(i);

        if(srcnode == "0" || srcnode == "")
            continue;
        
        for(pair<int,int> edge : graph[i]) {
            string targetnode = getName(edge.first);

            if(targetnode == "0" || targetnode == ""){
                to_print += srcnode + ";\n";
                continue;
            }    

            to_print += srcnode + " -> " + targetnode + "[label = \"" + to_string(edge.second) + "\"];\n";
        }
    }

    to_print += "}";
    ofstream out;
    string filename = "dag";
    out.open(filename + ".dot");
    out << to_print;
    out.close();
    dot2img(filename);
}

// critical paths
void WeightedGraph::generateCPImage() {
    vector<queue<int>> cps = getCriticalPaths();

    // critical path (maior)
    string to_print = "digraph CIC { labelloc=\"t\"; label=\"Ciencia da Computacao\nMaior Caminho Critico (em vermelho)\nPeso total do caminho critico: " + to_string(getPathSize(cps[0])) + "\";\n";
    for(int i=0;i<graph.size();i++) {
        string srcnode = getName(i);

        if(srcnode == "0" || srcnode == "")
            continue;
        
        for(pair<int,int> edge : graph[i]) {
            string targetnode = getName(edge.first);

            if(targetnode == "0" || targetnode == ""){
                to_print += srcnode + ";\n";
                continue;
            }    

            if(searchEdge(cps[0], i, edge.first))
                to_print += srcnode + " -> " + targetnode + "[label = \"" + to_string(edge.second) + "\", color=\"red\"];\n";
            else
                to_print += srcnode + " -> " + targetnode + "[label = \"" + to_string(edge.second) + "\"];\n";
        }
    }

    to_print += "}";
    ofstream out;
    string filename = "cam_critico1";
    out.open(filename + ".dot");
    out << to_print;
    out.close();
    dot2img(filename);

    // segundo maior critical path
    to_print = "digraph CIC { labelloc=\"t\"; label=\"Ciencia da Computacao\nSegundo maior Caminho Critico (em azul)\nPeso total do caminho critico: " + to_string(getPathSize(cps[1])) + "\";\n";
    for(int i=0;i<graph.size();i++) {
        string srcnode = getName(i);

        if(srcnode == "0" || srcnode == "")
            continue;
        
        for(pair<int,int> edge : graph[i]) {
            string targetnode = getName(edge.first);

            if(targetnode == "0" || targetnode == ""){
                to_print += srcnode + ";\n";
                continue;
            }    

            if(searchEdge(cps[1], i, edge.first))
                to_print += srcnode + " -> " + targetnode + "[label = \"" + to_string(edge.second) + "\", color=\"blue\"];\n";
            else
                to_print += srcnode + " -> " + targetnode + "[label = \"" + to_string(edge.second) + "\"];\n";
        }
    }

    to_print += "}";
    filename = "cam_critico2";
    out.open(filename + ".dot");
    out << to_print;
    out.close();
    dot2img(filename);
}

// topological order
void WeightedGraph::generateTOImage() {
    string to_print = "digraph CIC { labelloc=\"t\"; label=\"Ciencia da Computacao\nOrdenacao Topologica\";\n";
    //to_print += "node [shape=doublecircle];\n";
    to_print += "subgraph {\n";
    to_print += "rank=same;\n";
    
    for(pair<string,int> s : index) {
        if(s.first != "" && s.first != "0") {
            to_print += s.first + ";\n";
        }
    }

    to_print += "}\n ranksep=5;\n";

    stack<int> s = getOrdenacao();

    while(!s.empty()) {
        int i = s.top();
        s.pop();
        string srcnode = getName(i);

        if(srcnode == "0" || srcnode == "")
            continue;
        
        for(pair<int,int> edge : graph[i]) {
            string targetnode = getName(edge.first);

            if(targetnode == "0" || targetnode == ""){
                to_print += srcnode + ";\n";
                continue;
            }    

            to_print += srcnode + " -> " + targetnode + "[label = \"" + to_string(edge.second) + "\"];\n";
        }
    }

    to_print += "}";
    ofstream out;
    string filename = "ord_topologica";
    out.open(filename + ".dot");
    out << to_print;
    out.close();
    dot2img(filename);
}


/*******************************************************************
 * Funcoes auxiliares 
 * *****************************************************************/
void WeightedGraph::dot2img(string file) {
    string s = "dot -Tpng " + file + ".dot -o " + file + ".png";
    system(s.c_str());
}

bool WeightedGraph::searchEdge(queue<int> v, int i, int j) {
    while(!v.empty()) {
        int num = v.front();
        if(num == j){
            v.pop();
            int num2 = v.front();
            if(num2 == i) {
                return true;
            }
        } else {
            v.pop();
        }
    }    

    return false;
}

bool WeightedGraph::contains(queue<int> v, queue<int> u) {
    vector<int> lv, lu;

    while(!v.empty()) {
        lv.push_back(v.front());
        v.pop();
    }

    while(!u.empty()) {
        lu.push_back(u.front());
        u.pop();
    }


    for(int i : lv) {
        for(int j : lu) {
            if(i == j && i != 0) 
                return true;
        }
    }
    return false;
}

string WeightedGraph::getName(int n) {
    for(pair<string,int> p : index) {
        if(p.second == n){
            return p.first;
        }
    }
    return "";
}

void WeightedGraph::copyQueue(queue<int> &a, queue<int> &b) {
    while(!b.empty()) {
        b.pop();
    }

    while(!a.empty()) {
        b.push(a.front());
        a.pop();
    }
}

int WeightedGraph::getPathSize(queue<int> a) {
    int s = 0;
    while(!a.empty()) {
        int l = a.front();
        a.pop();
        int r = a.front();

        for(int i=0;i<graph[r].size();i++) {
            if(graph[r][i].first == l) {
                s += graph[r][i].second;
                break;
            }
        }
    }
    return s;
}

/*************************************************************
 * Getters / Setters
 * ***********************************************************/
vector<vector<pair<int, int>>> WeightedGraph::getGraph(){
    return graph;
}

map<string,int> WeightedGraph::getIndexMap(){
    return index;
}

stack<int> WeightedGraph::getOrdenacao(){
    return ordenacao_topologica;
}