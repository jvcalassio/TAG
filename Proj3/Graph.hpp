#ifndef __GRAPH__
#define __GRAPH__

#include <string>
#include <vector>

using namespace std;

class Node {
    private:
        int codigo;
        int tipo; // 0 = professor, 1 = escola
        int v1; // se professor, v1 = nº de habilitacoes; se escola, v1 = habilitacao 1 desejada
        int v2; // hab2 desejadas, se escola
        vector<int> prefs; // preferencias, se professor

    public:
        Node();
        Node(int tipo);
        int getCodigo();
        int getTipo();
        int getHabilitacoes();
        int getHab1();
        int getHab2();
        vector<int> getPrefs();
        void setCodigo(int val);
        void setTipo(int val);
        void setHabilitacoes(int val);
        void setHab1(int val);
        void setHab2(int val);
        void setPrefs(vector<int> prefs);
};

class Graph {
    private:
        vector<Node> graph;

    public:
        void txtInput(string file_name);
        vector<Node> getGraph();
};


#endif