#ifndef BORD
#define BORD
#include<iostream>
#include <vector>
using namespace std;

class Bord {
    public :
        string face;
        Bord(string face);
        vector<int> getValeur();
        virtual ~Bord();
};
ostream & operator<<(ostream &out, Bord b);

#endif
