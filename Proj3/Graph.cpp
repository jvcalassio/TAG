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