#ifndef BORDDOMINO
#define BORDDOMINO
#include "Bord.hpp"
#include <vector>

class BordDomino : public Bord {
    public : 
        vector<int> valeur;
        BordDomino(string s,vector<int> v);
        BordDomino(string s,int a,int b,int c,int d);
        vector<int> getValeur();
        void setValeur(vector<int> valeur);
        void setValeur(int a,int b,int c,int d);
        bool memeBord(BordDomino *x);
        int pointGagner(BordDomino *b);
        virtual ~BordDomino();
};

ostream& operator<<(ostream &out, BordDomino b);

#endif 