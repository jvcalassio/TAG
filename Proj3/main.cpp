#include <iostream>
#include "Graph.hpp"

using namespace std;

int main () {
    Graph graph;
    graph.txtInput("entradaProj3TAG.txt");

    vector<Node> gr = graph.getGraph();

    for(Node g : gr) {
        if(g.getTipo() == 0){
            cout << "Professor " << g.getCodigo() << " tem " << g.getHabilitacoes() << " habilitacoes e as preferencias:" << endl;
            cout << "\t";
            for(int i : g.getPrefs()) {
                cout << i << " ";
            }
            cout << endl;
        } else {
            cout << "Escola " << g.getCodigo() << " precisa de " << g.getHab1() << " e " << g.getHab2() << endl;
        }
    }
    return 0;
}