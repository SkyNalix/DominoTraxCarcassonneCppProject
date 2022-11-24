#ifndef BORD
#define BORD
#include<iostream>
#include <vector>
using namespace std;

class Bord {
    public :
        string face;
        Bord(const string &face);
        virtual ~Bord();
};
ostream & operator<<(ostream &out, const Bord &b);

#endif
