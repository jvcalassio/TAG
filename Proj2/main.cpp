#include "WeightedGraph.h"

#include <iostream>

using namespace std;

int main () {
    
    WeightedGraph a(10);
    a.txtInput("input.txt");

    /*vector<vector<pair<int,int>>> g = a.getGraph();
    int i = 0;
    for(vector<pair<int,int>> e : g){
        cout << i << ": ";
        for(pair<int, int> p : e){
            cout << p.first << " " << p.second << "; ";
        }
        i++;
        cout << endl;
    }*/

    return 0;

}
