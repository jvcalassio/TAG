#include "WeightedGraph.h"

#include <iostream>

using namespace std;

string findinmap(map<string,int> l, int n) {
    for(pair<string,int> p : l) {
        if(p.second == n){
            return p.first;
        }
    }
    return "";
}


int main () {
    
    WeightedGraph a(40);
    a.txtInput("input.txt");

    vector<vector<pair<int,int>>> g = a.getGraph();
    map<string,int> map = a.getIndexMap();

    int i = 0;
    for(vector<pair<int,int>> e : g){
        cout << findinmap(map, i) << ": ";
        for(pair<int, int> p : e){
            //cout << p.first << " " << p.second << "; ";
            cout << findinmap(map, p.first) << " " << p.second << "; ";
        }
        i++;
        cout << endl;
    }

    return 0;

}
