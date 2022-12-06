#ifndef BORDDOMINO
#define BORDDOMINO
#include "Bord.hpp"
#include <vector>

class BordDomino : public Bord {
    private:
        vector<int> valeurs{};
    public : 
        BordDomino(const string &s, const vector<int>& v);
        BordDomino(const string &s,int a,int b,int c);
        vector<int> getValeurs() const;
        void setValeurs(const vector<int> &v);
        virtual ~BordDomino();
};

ostream& operator<<(ostream &out, const BordDomino &b);

#endif 