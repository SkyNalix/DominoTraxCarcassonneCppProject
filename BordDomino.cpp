#include "BordDomino.hpp"
#include <iostream>
#include <vector>
using namespace std;

BordDomino::BordDomino(string s,const vector<int>& valeur): Bord{s}, valeur{valeur} { // les valeurs du bordDomino
    if (valeur.size() >= 4) {
        throw invalid_argument("Trop de value dans ce bord de domino");
    }
    // sont dans sens horaires nord=[0] est =1, sud=[2] ouest=[3]
}

vector<int> creerVector(int a,int b,int c){
    vector<int> x ;
    x.push_back(a); x.push_back(b); x.push_back(c);
    return x; 
}

BordDomino::BordDomino(string s,int a,int b,int c) : Bord{s}, valeur{creerVector(a,b,c)} {
}


vector<int> BordDomino::getValeurs() const{
    return this->valeur;
}

ostream& operator<<(ostream& out,  BordDomino x) {
    out << "[" << x.valeur[0] << "," << x.valeur[1] << "," << x.valeur[2] << "]";
    return out;
}

BordDomino::~BordDomino(){
//    cout << "destruction d'un bordDomino" << endl;
}