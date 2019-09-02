/**
 * Joao Victor de Souza Calassio - 18/0033808
 * 117901 - Teoria e Aplicacao de Grafos - 2019/2
 * */
#ifndef _GRAPH
#define _GRAPH
#include <vector>
#include <string>

class Graph {
    private:
        std::vector<std::vector<int>> graph; // lista de adjacencias
        int cols = 0;
        int rows = 0;
        int edges = 0; // qtd vertices
        float cma = 0.0; // coeficiente medio de aglomeracao

        void read_from_file(std::string filename);
        void print_vector(std::vector<int> v);
        void bron_kerbosch(std::vector<int> r, std::vector<int> p, std::vector<int> x);
        std::vector<int> uniao(std::vector<int> a, std::vector<int> b);
        std::vector<int> intersecao(std::vector<int> a, std::vector<int> b);
        std::vector<int> diferenca(std::vector<int> a, std::vector<int> b);
        bool search(std::vector<int> &v, int l);

    public:
        Graph(std::string filename);
        void print_degree();
        void print_cliques();
        void print_ica();
        void print_cma();
};

#endif
