#ifndef TUILE
#define TUILE

#include <iostream>
#include <vector>
#include "Bord.hpp"
#include "BordDomino.hpp"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;


class Tuile {
    private :
        vector<BordDomino *> bords;
        string id;
    public :
        Tuile(const vector<BordDomino *> &bords);
        vector<BordDomino *> getBords() const;
        BordDomino * getBord(const string& face) const;
        string getId() const;
        void draw(RenderWindow *app, int start_x, int start_y, int ZONE_WIDTH, int ZONE_HEIGHT );
        void turn();
};
ostream& operator<<(ostream &out, const Tuile &t);
Tuile* getRandomTuile();

#endif 