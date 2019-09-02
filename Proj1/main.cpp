/**
 * Joao Victor de Souza Calassio - 18/0033808
 * 117901 - Teoria e Aplicacao de Grafos - 2019/2
 * */
#include <iostream>
#include "Graph.hpp"
#define HR "\n==============================================================\n"

using namespace std;

int main() {
    Graph dolphins("soc-dolphins.mtx");
    dolphins.print_degree();
    cout << HR << endl;
    dolphins.print_cliques();
    cout << HR << endl;
    dolphins.print_ica();
    cout << HR << endl;
    dolphins.print_cma();
    return 0;
}
