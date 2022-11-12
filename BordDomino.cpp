#include "BordDomino.hpp"
#include <iostream>
#include <vector>
using namespace std;

BordDomino::BordDomino(vector<int> valeur): valeur{valeur} {
    if(valeur.size() > 4){throw ("Trop de valeur dans ce bord de domino");}
}

vector<int> creerVector(int a,int b,int c,int d){
    vector<int> x ;
    x.push_back(a); x.push_back(b); x.push_back(c); x.push_back(d);
    return x; 
}

BordDomino::BordDomino(int a,int b,int c,int d) :valeur{creerVector(a,b,c,d)} {
}

vector<int> BordDomino::getValeur(){
    return this->valeur;
}

void BordDomino::setValeur(vector<int> v){
    this->valeur = v;
}

void BordDomino::setValeur(int a,int b,int c,int d){
    this->valeur[0] = a;
    this->valeur[1] = b;
    this->valeur[2] = c;
    this->valeur[3] = d;
}


ostream& operator<<(ostream& out,  BordDomino x) {
    out << "[" << x.valeur[0] << "," << x.valeur[1] << "," << x.valeur[2] << "]";
    return out;
}

bool BordDomino::memeBord(BordDomino x){
    for(int i =0; i < x.valeur.size();i++){
        if(this->valeur[i] != x.valeur[i]){return false;}
    }
    return true;
}

