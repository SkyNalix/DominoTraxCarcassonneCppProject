// bord different pour chaque jeu
#include "Bord.hpp"
#include "BordDomino.hpp"
#include "Tuile.hpp"
Bord::Bord(string f): face{f} {

}

ostream & operator<<(ostream &out, Bord b) {
    out << "un Bord";
    return out; 
}

vector<int> Bord::getValeur(){
    vector<int> x;
    x.push_back(-1);
    cout << "un bord " << this->face << " " << x[0] << endl;
    return x;
}

Bord::~Bord(){
    cout << "destruction d'un Bord" << endl; 
}

/*int main(){
    //Bord *pere = vecteur[i]
    //BordDomino *domino =  (BordDomino *) &pere;
    
    Bord *pere = new Bord{"face"};
    BordDomino *enfant = new BordDomino{"enfant",1,2,3,4}; 
    vector<Bord *> x; x.push_back(enfant);
    Tuile tuile {x};
    BordDomino *domino = (BordDomino *) x[0];

    cout << *domino<< endl;
} */