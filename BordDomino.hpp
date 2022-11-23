#ifndef BORDDOMINO
#define BORDDOMINO
#include "Bord.hpp"
#include <vector>

class BordDomino : public Bord {
    public : 
        vector<int> valeur;
        BordDomino(string s,const vector<int>& v);
        BordDomino(string s,int a,int b,int c);
        vector<int> getValeurs() const override;
        virtual ~BordDomino();
};

ostream& operator<<(ostream &out, BordDomino b);

#endif 