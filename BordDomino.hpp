#ifndef BORDDOMINO
#define BORDDOMINO
#include "Bord.hpp"
#include <vector>

class BordDomino : public Bord {
    public : 
        vector<int> valeur;
        BordDomino(string s,const vector<int>& v);
        BordDomino(string s,int a,int b,int c);
        vector<int> getValeur() const override;
        void setValeur(const vector<int>& valeur);
        void setValeur(int a,int b,int c);
        bool memeBord(BordDomino x);
        int pointGagner(BordDomino b);
        virtual ~BordDomino();
};

ostream& operator<<(ostream &out, BordDomino b);

#endif 