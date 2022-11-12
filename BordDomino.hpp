#ifndef BORDDOMINO
#define BORDDOMINO
#include "Bord.hpp"
#include <vector>

class BordDomino : public Bord {
    public : 
        vector<int> valeur;
        BordDomino(vector<int> v);
        BordDomino(int a,int b,int c,int d);
        vector<int> getValeur();
        void setValeur(vector<int> valeur);
        void setValeur(int a,int b,int c,int d);
        bool memeBord(BordDomino x);
};

ostream& operator<<(ostream &out, BordDomino b);

#endif 