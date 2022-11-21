//tuile composé de vector<Bord>
#include "Tuile.hpp"
#include "BordDomino.hpp"

Tuile::Tuile(vector<Bord *> b) : bords{b} {}

vector<Bord *> Tuile::getBords() {
    return this->bords;
}

void Tuile::setOneBord(size_t cible, Bord *b) { //le bord de this d'index cible devient b
    if (cible < this->bords.size()) {       //si l'index n'existe pas ne fait rien
        this->bords[cible] = b;
    }
}

void Tuile::setAllBord(vector<Bord *> b) { //les bords de this prennent la valeur des bords de b
    for (size_t i = 0; i < b.size(); i++) {
        this->setOneBord(i, b[i]);
    }
}

string Tuile::getId() {
    return this->id;
}

void Tuile::setId(string nouveau) {
    this->id = nouveau;
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
        out << " Bord(" << bord.face << ") : " << bord ;
    }
    return out;
}

int piocherTuileDomino(vector <Tuile> pioche) {
    srand((unsigned) time(NULL));
    return rand() % (pioche.size());
}


int calculTuileDomino(const string& face, Tuile a, BordDomino b) {
//    int points = 0;
    vector<Bord *> bord_list = a.getBords();
    for (size_t i = 0; i < a.getBords().size(); i++) {
        BordDomino *x = (BordDomino *) bord_list[i];
        if (face == x->face) {
            return x->pointGagner(b);
        }
    }
    return 0;
}

bool peutPoserSansConflict(int x, int y, Tuile *a, vector <vector<Tuile *>> liste) {
    if (liste[x][y + 1] == nullptr && liste[x][y - 1] == nullptr && liste[x + 1][y] == nullptr &&
        liste[x - 1][y] == nullptr) {
        return false;
    } else {

    }
    return true;
}

bool isTuileVide(Tuile *x) {
    if (((BordDomino *) x->getBords()[0])->face == "vide") { return true; }
    return false;
}

// liste est la grille de jeu
int
placerDomino(int x, int y, Tuile a, vector <vector<Tuile>> liste) { // un terrain est composé de Tuile vide avec null
    int point = 0;
//    if (liste[x][y] == nullptr) {
        cout << "je suis entrer en " << x << "|" << y << endl;
//        if (liste[x][y + 1] != nullptr) {// tuile à droite
            BordDomino tmp = *(BordDomino*) &(liste[x][y +1].getBords()[3]); // on prend le bord gauche de la tuile droite
            point += calculTuileDomino("est", a, tmp);
//        }
//        if (liste[x + 1][y] != nullptr) {// tuile au dessus
            tmp = *(BordDomino*) &(liste[x + 1][y].getBords()[1]);
            point += calculTuileDomino("est", a, tmp);
//        }
//        if (liste[x][y - 1] != nullptr) {// tuile à gauche
            tmp = *(BordDomino*) &(liste[x][y - 1].getBords()[0]);
            point += calculTuileDomino("est", a, tmp);
//        }
//        if (liste[x - 1][y] != nullptr) {//tuile en dessous
            tmp = *(BordDomino*) &(liste[x][y].getBords()[2]);
            point += calculTuileDomino("est", a, tmp);
//        }

        liste[x][y] = a; // vérifier avant que l'on peut poser la tuile
//    }
    return point; // renvoie -1 si on ne peut pas placer la tuile
}


Tuile TuileVide(){
    BordDomino w {"vide",-1,-1,-1};
    BordDomino x {"vide",-1,-1,-1};
    BordDomino y {"vide",-1,-1,-1};
    BordDomino z {"vide",-1,-1,-1};
    return Tuile { vector<Bord*>{&w,&x,&y,&z} };
}

static vector <vector<Tuile>> creerTerrain(int x, int y) {
    BordDomino *w = new BordDomino {"vide",-1,-1,-1};
    vector<Bord*> bords{w,w,w,w};
    Tuile t{bords};
    vector <vector<Tuile>> plateau;
    for (int i = 0; i < x; i++) {
        vector < Tuile > tmp{};
        for (int j = 0; j < y; j++) {
            tmp.push_back(t);
        }
        plateau.push_back(tmp);
    }
    return plateau;
}

int main() {

    BordDomino w = BordDomino{"nord", 1, 2, 3};
    cout << w << endl;
    BordDomino x = BordDomino{"est", 2, 3, 4};
    cout << x << endl;
    BordDomino y = BordDomino{"sud", 3, 4, 1};
    cout << y << endl;
    BordDomino z = BordDomino{"ouest", 4, 1, 2};
    cout << z << endl;

    vector <Bord *> vectA {&w,&x,&y,&z};
//    delete &y;

    Tuile tuileA = Tuile{vectA};
//    cout << *((BordDomino *) tuileA.getBords()[0]) << endl;
    cout << tuileA << endl;

    vector<vector<Tuile>> terrain = creerTerrain(4,4);
    Tuile A = terrain[0][0];
//    cout << A << endl;
    //BordDomino *B = (BordDomino *) A->getBords()[0]; 

    //placerDomino(1,1,tuileA,terrain);

    cout << "Fin Programme" << endl;
    return EXIT_SUCCESS;
} 