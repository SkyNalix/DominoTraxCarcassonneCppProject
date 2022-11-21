#ifndef TUILE
#define TUILE
#include <vector>
#include "Bord.hpp"
#include <iostream>
class Tuile {
    private :
        vector<Bord *> bords;
        string id;
    public :
        Tuile(vector<Bord *> bords);
        void addBord(Bord ajout);
        vector<Bord *> getBord();
        void setAllBord(vector<Bord *> bords);
        void setOneBord(size_t cible,Bord *bord);
        string getId();
        void setId(string nouveau);
};
ostream& operator<<(ostream &out, Tuile t);

#endif 