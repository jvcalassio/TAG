#include "Graph.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <regex>

using namespace std;

vector<string> normalize(string line){
    vector<string> aux;
    regex reg(":|,");
    regex reg2(" ");
    line = regex_replace(line,reg2,"");
    
    regex reg1("|\\(|\\)|");
    line = regex_replace(line,reg1,"");
    line = regex_replace(line,reg," ");
    
    string pars = " ";
    int pos = 0;
    while((pos = line.find(pars)) != string::npos){
        aux.push_back(line.substr(0,pos));
        line.erase(0,pos+pars.length());
    }
    aux.push_back(line);
    return aux;
}

void Graph::txtInput(string file_name) {
    ifstream in;
    in.open(file_name);
    if(in.fail()) {
        cout << "Error opening file" << endl;
    } else {
        string l;
        while(getline(in, l)) {
            if(l[0] != '/' && l[0] != ' '){
                Node n(0);
                vector<string> nl = normalize(l);
                n.setCodigo( stoi(nl[0].substr(1)) );
                if(nl[0][0] == 'P') {
                    n.setHabilitacoes(stoi(nl[1]));
                    vector<int> np;
                    for(int i=2;i<nl.size();i++) {
                        np.push_back( stoi(nl[i].substr(1)) );
                    }
                    n.setPrefs(np);
                } else {
                    n.setTipo(1);
                    n.setHab1(stoi(nl[1]));
                    if(nl.size() > 2)
                        n.setHab2(stoi(nl[2]));
                    else
                        n.setHab2(0);
                }
                this->graph.push_back(n);
                nl.clear();
            }
        }
    }
}

vector<Node> Graph::getGraph() {
    return this->graph;
}

int getEscola(vector<Node> graph, int codigo){
    int i = 0;
    for(Node n : graph){
        if(n.getTipo() == 1 && n.getCodigo() == codigo) return i;
        i++;
    }
    return -1;
}

//retorna o primeiro professor livre
int free_prof(vector<Node> graph){
    for(int i = 0; i<graph.size(); i++){
        if(graph[i].getTipo() == 0 && graph[i].free == true)
            if(graph[i].count < graph[i].getPrefs().size()) return i;
    }
    return -1;
}

//homens = professores
//mulheres = escolas
vector<pair<Node,Node>> Graph::GaleShapley() {
    
    vector<pair<Node,Node>> emp;
    vector<Node> graph = getGraph();

    //inicializando os estados
    for(int i = 0; i<graph.size(); i++){
        graph[i].free = true;
        if(graph[i].getHab2() != 0)
            graph[i].free2 = true;
        graph[i].count = 0;
    }

    //int index = free_prof(graph);

    for(Node node : graph){
        
        //se o nó é um professor
        if(node.getTipo() == 0){

            Node* professor = &node;

            for(int escola_pref : professor->getPrefs()){
                
                //Node* escola = getEscola(graph, pref);
                Node* escola = &graph[getEscola(graph, escola_pref)];
                if(escola->free == true){ //primeira vaga vazia
                    if(professor->getHab1() >= escola->getHab1()){ //professor com habilidades suficientes
                        emp.push_back(make_pair(*professor, *escola));
                        professor->free = false;
                        escola->free = false;
                        break;
                    }
                    professor->count++;
                }
                else if(escola->free2 == true){ //segunda vaga vazia
                    if(professor->getHab1() >= escola->getHab2()){ //professor com habilidades suficientes
                        emp.push_back(make_pair(*professor, *escola));
                        professor->free = false;
                        escola->free2 = false;
                        break;
                    }
                    professor->count++;
                }
                else
                    professor->count++;
            }
            //professor->free = false;
            //index = free_prof(graph);
        }
    }

    return emp;
}

Node::Node(int tipo) {
    this->tipo = tipo;
}

int Node::getCodigo() {
    return this->codigo;
}
int Node::getTipo() {
    return this->tipo;
}
int Node::getHabilitacoes() {
    return this->v1;
}
int Node::getHab1() {
    return this->v1;
}
int Node::getHab2() {
    return this->v2;
}
vector<int> Node::getPrefs() {
    return this->prefs;
}

void Node::setCodigo(int val) {
    this->codigo = val;
}
void Node::setTipo(int val) {
    this->tipo = val;
}
void Node::setHabilitacoes(int val) {
    this->v1 = val;
}
void Node::setHab1(int val) {
    this->v1 = val;
}
void Node::setHab2(int val) {
    this->v2 = val;
}
void Node::setPrefs(vector<int> prefs) {
    this->prefs = prefs;
}