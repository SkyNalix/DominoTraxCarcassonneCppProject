// bord different pour chaque jeu
#include "Bord.hpp"
#include "BordDomino.hpp"
#include "Tuile.hpp"
Bord::Bord(const string &face): face{face} {

}

ostream & operator<<(ostream &out, const Bord &b) {
    out << "un Bord(" << b.face << ")";
    return out; 
}

Bord::~Bord(){
//    cout << "destruction d'un Bord" << endl;
}
