#include "WeightedGraph.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>

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
    if(weight != 0)
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

vector<vector<pair<int, int>>> WeightedGraph::getGraph(){
    return graph;
}

map<string,int> WeightedGraph::getIndexMap(){
    return index;
}