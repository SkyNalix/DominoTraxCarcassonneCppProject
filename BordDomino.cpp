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


vector<int> BordDomino::getValeur() const{
    return this->valeur;
}

void BordDomino::setValeur(const vector<int>& v){
    this->valeur = v;
}

void BordDomino::setValeur(int a,int b,int c){
    this->valeur[0] = a;
    this->valeur[1] = b;
    this->valeur[2] = c;
}


ostream& operator<<(ostream& out,  BordDomino x) {
    out << "[" << x.valeur[0] << "," << x.valeur[1] << "," << x.valeur[2] << "]";
    return out;
}

bool comparaisonFace(const BordDomino& a, const BordDomino& x){
    if(a.face == "est" && x.face != "ouest"){
        return true;   
    } else if(a.face == "ouest" && x.face != "est"){
        return true;
    } else if(a.face == "nord" && x.face != "sud"){
        return true;
    } else if(a.face == "sud" && x.face != "nord"){
        return true;
    }
    return false;
}

bool BordDomino::memeBord(BordDomino x){
    if(!comparaisonFace(*this, x)) {
        return false;
    }
    for(size_t i =0; i < x.valeur.size();i++){
        if(this->valeur[i] != x.valeur[i]){return false;}
    }
    return true;
}

int BordDomino::pointGagner(BordDomino b){
    if(this->memeBord(b)){
        return(this->getValeur()[0]+this->getValeur()[1]+this->getValeur()[2]);
    }
    return 0;
}

BordDomino::~BordDomino(){
//    cout << "destruction d'un bordDomino" << endl;
}