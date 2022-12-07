#include "BordDomino.hpp"
#include <iostream>
#include <vector>
using namespace std;

BordDomino::BordDomino(const string &s, const vector<int>& v): Bord{s}, valeurs{v} { 
    if (valeurs.size() >= 4) {
        throw invalid_argument("Trop de value dans ce bord de domino");
    }
}

vector<int> creerVector(int a,int b,int c){
    vector<int> x ;
    x.push_back(a); x.push_back(b); x.push_back(c);
    return x; 
}

BordDomino::BordDomino(const string& s,int a,int b,int c) : Bord{s}, valeurs{creerVector(a,b,c)} {
}


vector<int> BordDomino::getValeurs() const{
    return this->valeurs;
}

ostream& operator<<(ostream& out, const BordDomino &x) {
    out << "[" << x.getValeurs()[0] << "," << x.getValeurs()[1] << "," << x.getValeurs()[2] << "]";
    return out;
}

BordDomino::~BordDomino(){
//    cout << "destruction d'un bordDomino" << endl;
}

void BordDomino::setValeurs(const vector<int> &v) {
    valeurs = v;
}