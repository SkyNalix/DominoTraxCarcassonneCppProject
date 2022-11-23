#ifndef TUILE
#define TUILE

#include <iostream>
#include <vector>
#include "Bord.hpp"
#include "BordDomino.hpp"

class Tuile {
    private :
        vector<Bord *> bords;
        string id;
    public :
        Tuile(vector<Bord *> bords);
        vector<Bord *> getBords();
        Bord * getBord(const string& face);
        string getId();
};
ostream& operator<<(ostream &out, Tuile t);

#endif 