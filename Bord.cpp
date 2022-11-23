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

vector<int> Bord::getValeurs() const{
    vector<int> x;
    x.push_back(-1);
    cout << "un bord " << this->face << " " << x[0] << endl;
    return x;
}

Bord::~Bord(){
//    cout << "destruction d'un Bord" << endl;
}
