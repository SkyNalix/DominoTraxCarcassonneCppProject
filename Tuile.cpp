//tuile composÃ© de vector<Bord>
#include "Tuile.hpp"
#include "BordDomino.hpp"

Tuile::Tuile(vector<Bord> b): bords{b} {}

vector<Bord> Tuile::getBord(){
    return this->bords;
}

void Tuile::setOneBord(int cible,Bord b){ //le bord de this d'index cible devient b 
    if(cible < this->bords.size()){       //si l'index n'existe pas ne fait rien
        this->bords[cible] = b;
    }
}

void Tuile::setAllBord(vector<Bord> b){ //les bords de this prennent la valeur des bords de b
    for(int i =0; i < b.size();i++){
        this->setOneBord(i,b[i]);
    }
}

string Tuile::getId(){
    return this->id;
}

void Tuile::setId(string nouveau){
    this->id = nouveau;
}

string afficherTuile(Tuile t){
    string str = "Tuile :" +  t.getId();
    vector<Bord> bords = t.getBord();
    for(int i =0;i < bords.size();i++){
        str += " bords : " + std::to_string(i);
    }
    return str;
}

ostream& operator<<(ostream &out, Tuile t){
    out << "Tuile : " + t.getId();
    for (int i =0; i < t.getBord().size();i++){
        out << " Bord : " << t.getBord()[i];
    }
    return out;
}

int piocherTuileDomino(vector<Tuile> pioche){
   srand((unsigned)time(NULL)); 
   return rand()%(pioche.size());
}

int main(){
    
    BordDomino w {1,2,3,4};
    BordDomino x {2,3,4,1};
    BordDomino y {3,4,1,2}; 
    BordDomino z {4,1,2,3};
   // vector<Bord> bordA ; bordA.push_back(w); bordA.push_back(x); bordA.push_back(y); bordA.push_back(z);
   // Tuile test {bordA};
    cout << "hello" << endl;
    return EXIT_SUCCESS;
}