#include "WeightedGraph.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>

using namespace std;

WeightedGraph::WeightedGraph(int size){
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

/*vector<vector<pair<int, int>>> WeightedGraph::getGraph(){
    return graph;
}*/

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