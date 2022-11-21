#include "BordDomino.hpp"
#include "Tuile.hpp"
#include <iostream>
#include <vector>
using namespace std;

BordDomino::BordDomino(string s,vector<int> valeur): Bord{s}, valeur{valeur} { // les valeurs du bordDomino
    if(valeur.size() > 4){throw ("Trop de valeur dans ce bord de domino");}     // sont dans sens horaires nord=[0] est =1
}                                                                           // sud=[2] ouest=[3]                

vector<int> creerVector(int a,int b,int c,int d){
    vector<int> x ;
    x.push_back(a); x.push_back(b); x.push_back(c); x.push_back(d);
    return x; 
}

BordDomino::BordDomino(string s,int a,int b,int c,int d) : Bord{s}, valeur{creerVector(a,b,c,d)} {
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

bool comparaisonFace(BordDomino *a,BordDomino *x){
    if(a->face.compare("est") == 0 && !(x->face.compare("ouest") == 0) ){
        return true;   
    } else if(a->face.compare("ouest") == 0 && !(x->face.compare("est") == 0) ){
        return true;
    } else if(a->face.compare("nord") == 0 && !(x->face.compare("sud") == 0) ){
        return true;
    } else if(a->face.compare("sud") == 0 && !(x->face.compare("nord") == 0) ){
        return true;
    }
    return false;
}

bool BordDomino::memeBord(BordDomino *x){
    if(comparaisonFace(this,x) == false){return false;}
    for(size_t i =0; i < x->valeur.size();i++){
        if(this->valeur[i] != x->valeur[i]){return false;}
    }
    return true;
}

int BordDomino::pointGagner(BordDomino *b){
    if(this->memeBord(b)){
        return(this->getValeur()[0]+this->getValeur()[1]+this->getValeur()[2]);
    }
    return 0;
}

BordDomino::~BordDomino(){
    cout << "destruction d'un bordDomino" << endl;
}