//tuile composé de vector<Bord>
#include "Tuile.hpp"
#include "BordDomino.hpp"

Tuile::Tuile(vector<Bord *> b) : bords{b} {}

vector<Bord *> Tuile::getBords() {
    return this->bords;
}


string Tuile::getId() {
    return this->id;
}

Bord *Tuile::getBord(const string& face) {
    if(face=="nord")
        return bords[0];
    if(face=="est")
        return bords[1];
    if(face=="sud")
        return bords[2];
    if(face=="ouest")
        return bords[3];
    return nullptr;
}

string afficherTuile(Tuile t) {
    string str = "Tuile :" + t.getId();
    vector<Bord *> bords = t.getBords();
    for (size_t i = 0; i < bords.size(); i++) {
        str += " bords : " + std::to_string(i);
    }
    return str;
}

ostream &operator<<(ostream &out, Tuile t) {
    out << "Tuile : " + t.getId();
    for (size_t i = 0; i < t.getBords().size(); i++) {
        BordDomino bord = *((BordDomino *) t.getBords()[i]);
        if(bord.face == "vide")
            out << "Bord(vide)";
        else
            out << "Bord(" << bord.face << ") : " << bord ;
        if(i < t.getBords().size()-1)
            out << "; ";
    }
    return out;
}

int piocherTuileDomino(vector <Tuile> pioche) {
    srand((unsigned) time(NULL));
    return rand() % (pioche.size());
}



