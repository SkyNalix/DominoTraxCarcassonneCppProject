#ifndef BORD
#define BORD
#include<iostream>
#include <vector>
using namespace std;

class Bord {
    public :
        string face;
        Bord(string face);
        virtual vector<int> getValeur() const;
        virtual ~Bord();
};
ostream & operator<<(ostream &out, Bord b);

#endif
