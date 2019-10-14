#include "WeightedGraph.h"

#include <iostream>

using namespace std;

int main () {
    
    WeightedGraph a(40);
    a.txtInput("input.txt");

    vector<vector<pair<int,int>>> g = a.getGraph();
    map<string,int> map = a.getIndexMap();

    a.ordenacaoTopologica();
    a.getCriticalPaths();
    a.generateDAGImage();
    a.generateCPImage();
    a.generateTOImage();
    return 0;
}
