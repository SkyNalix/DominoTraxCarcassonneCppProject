//tuile composé de vector<Bord>
#include "Tuile.hpp"
#include "BordDomino.hpp"

Tuile::Tuile(vector<Bord *> b): bords{b} {}

vector<Bord *> Tuile::getBord(){
    return this->bords;
}

void Tuile::setOneBord(size_t cible,Bord *b){ //le bord de this d'index cible devient b 
    if(cible < this->bords.size()){       //si l'index n'existe pas ne fait rien
        this->bords[cible] = b;
    }
}

void Tuile::setAllBord(vector<Bord *> b){ //les bords de this prennent la valeur des bords de b
    for(size_t i =0; i < b.size();i++){
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
    vector<Bord *> bords = t.getBord();
    for(size_t i =0;i < bords.size();i++){
        str += " bords : " + std::to_string(i);
    }
    return str;
}

ostream& operator<<(ostream &out, Tuile t){
    out << "Tuile : " + t.getId();
    for (size_t i =0; i < t.getBord().size();i++){
        out << " Bord : " << t.getBord()[i];
    }
    return out;
}

int piocherTuileDomino(vector<Tuile> pioche){
   srand((unsigned)time(NULL)); 
   return rand()%(pioche.size());
}


int calculTuileDomino(string face,Tuile *a,BordDomino *b){
    int points = 0;
    for(size_t i =0; i < a->getBord().size();i++){
        BordDomino *x = (BordDomino *) a->getBord()[i];
        if(face.compare(x->face) == 0 ){
            return x->pointGagner(b);
        }
    }
    return 0;
}

bool peutPoserSansConflict(int x,int y, Tuile *a,vector<vector<Tuile *>> liste){
    if(liste[x][y+1] == nullptr && liste[x][y-1] == nullptr  && liste[x+1][y] == nullptr && liste[x-1][y] == nullptr  ){
        return false;
    }else{
        
    }
    return true;
}

bool isTuileVide(Tuile *x){
    if(x->getBord()[0]->face.compare("vide")){return true;}
    return false;
}

// liste est la grille de jeu
int placerDomino(int x,int y, Tuile *a,vector<vector<Tuile *>> liste){ // un terrain est composé de Tuile vide avec null
    int point = 0;
    if(liste[x][y]  == nullptr){
            cout << "je suis entrer en " << x << "|" << y << endl;
            if(liste[x][y+1] != nullptr){// tuile à droite
                BordDomino *tmp = (BordDomino * ) liste[x][y+1]->getBord()[3]; // on prend le bord gauche de la tuile droite
                point += calculTuileDomino("est",a,tmp);
            }if(liste[x+1][y] != nullptr){// tuile au dessus 
                BordDomino *tmp = (BordDomino * ) liste[x+1][y]->getBord()[1];
                point += calculTuileDomino("est",a,tmp);
            }if(liste[x][y-1] != nullptr){// tuile à gauche
                BordDomino *tmp = (BordDomino * ) liste[x][y-1]->getBord()[0];
                point += calculTuileDomino("est",a,tmp);
            }if(liste[x-1][y] != nullptr){//tuile en dessous
                BordDomino *tmp = (BordDomino * ) liste[x][y]->getBord()[2];
                point += calculTuileDomino("est",a,tmp);
            }

            liste[x][y] = a; // vérifier avant que l'on peut poser la tuile
    }
    return point; // renvoie -1 si on ne peut pas placer la tuile
}


Tuile *TuileVide(){
    BordDomino w {"vide",-1,-1,-1,-1};
    BordDomino x {"vide",-1,-1,-1,-1};
    BordDomino y {"vide",-1,-1,-1,-1}; 
    BordDomino z {"vide",-1,-1,-1,-1};
    vector<Bord *> vectA; vectA.push_back(&w); vectA.push_back(&x); vectA.push_back(&y); vectA.push_back(&z);
    Tuile *tuileA = new Tuile {vectA};
    return tuileA;
}

static vector<vector<Tuile *>> creerTerrain(int x,int y){
    vector<vector<Tuile *>> plateau;
    for(int i =0; i < x;i++){
        vector<Tuile *> tmp;
        for(int j=0; j < y;j++){
            Tuile *tuile = TuileVide();
            tmp.push_back(tuile);
            //plateau[i].push_back(TuileVide());
        }
        plateau.push_back(tmp);
    }
}

int main(){
    
    BordDomino *w = new BordDomino{"nord",1,2,3,4};
    BordDomino *x = new BordDomino{"est",2,3,4,1};
    BordDomino *y = new BordDomino{"sud",3,4,1,2}; 
    BordDomino *z = new BordDomino{"ouest",4,1,2,3};
    vector<Bord *> vectA; vectA.push_back(w); vectA.push_back(x); vectA.push_back(y); vectA.push_back(z);
    //delete &y;
    
    Tuile *tuileA = new Tuile {vectA};

    vector<vector<Tuile *>> terrain = creerTerrain(4,4);
    Tuile *A = terrain[0][0] ;
    //BordDomino *B = (BordDomino *) A->getBord()[0]; 

    //placerDomino(1,1,tuileA,terrain);

    cout << "Fin Programme" << endl;
    return EXIT_SUCCESS;
} 