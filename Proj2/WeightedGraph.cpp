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

string WeightedGraph::getName(int n) {
    for(pair<string,int> p : index) {
        if(p.second == n){
            return p.first;
        }
    }
    return "";
}

// dijikstra com maior caminho
vector<vector<int>> WeightedGraph::getCriticalPaths() {
    vector<int> dist(graph.size(), -1e9);
    vector<int> path(graph.size());

    priority_queue<pair<int,int>, vector<pair<int,int>>, less<pair<int,int>>> pq;

    int w = 0; // w = primeiro elemento
    dist[w] = 0;
    path[w] = -1; // vertice w eh inicial, portanto vem de -1
    pq.emplace(dist[w], w);


    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for(pair<int,int> edge : graph[u]) {
            int v = edge.first;
            int dv = edge.second;

            if(dist[v] < dist[u] + dv) {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
                path[v] = u;
            }
        }
    }

    vector<int> max_path;
    vector<int> s_max_path;

    for(int j=0;j<graph.size();j++){
        int k = j;
        vector<int> tmp;
        while(path[k] != -1) {
            tmp.push_back(k);
            k = path[k];
        }
        tmp.push_back(w);

        if(tmp.size() > max_path.size()) {
            max_path = tmp;
        }
    }

    for(int j=0;j<graph.size();j++){
        int k = j;
        vector<int> tmp;
        while(path[k] != -1) {
            tmp.push_back(k);
            k = path[k];
        }
        tmp.push_back(w);

        if(tmp.size() > s_max_path.size() && tmp.size() < max_path.size()) {
            s_max_path = tmp;
        }
    }
    vector<vector<int>> ans;
    ans.push_back(max_path);
    ans.push_back(s_max_path);
    return ans;
}

void WeightedGraph::generateDAGImage() {
    string to_print = "digraph CIC {\n";
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
    out.open("dag.dot");
    out << to_print;
    out.close();
    dot2img("dag.dot");
}

bool WeightedGraph::searchEdge(vector<int> v, int i, int j) {
    for(int k=0;k<v.size()-1;k++){
        if(i == v[k+1] && j == v[k])
            return true;
    }

    return false;
}

void WeightedGraph::generateCPImage() {
    string to_print = "digraph CIC {\n";
    vector<vector<int>> cps = getCriticalPaths();
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
    out.open("crit_path.dot");
    out << to_print;
    out.close();
    dot2img("crit_path.dot");


    // second critical path
    to_print = "digraph CIC {\n";
    cps = getCriticalPaths();

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
    out.open("second_crit_path.dot");
    out << to_print;
    out.close();
    dot2img("second_crit_path.dot");
}

void WeightedGraph::generateTOImage() {
    string to_print = "digraph CIC {\n";
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
    out.open("ord_topologica.dot");
    out << to_print;
    out.close();
    dot2img("ord_topologica.dot");
}

void WeightedGraph::dot2img(string file) {
    string filen = file.substr(0, file.size() - 4);
    string s = "dot -Tpng " + filen + ".dot -o " + filen + ".png";
    system(s.c_str());
}

vector<vector<pair<int, int>>> WeightedGraph::getGraph(){
    return graph;
}

map<string,int> WeightedGraph::getIndexMap(){
    return index;
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

stack<int> WeightedGraph::getOrdenacao(){
    return ordenacao_topologica;
}