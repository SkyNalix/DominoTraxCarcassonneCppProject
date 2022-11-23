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
        vector<Bord *> bords;
        string id;
    public :
        Tuile(vector<Bord *> bords);
        vector<Bord *> getBords();
        Bord * getBord(const string& face);
        string getId();
        void draw(RenderWindow *app, int start_x, int start_y, int ZONE_WIDTH, int ZONE_HEIGHT );
};
ostream& operator<<(ostream &out, Tuile t);

#endif 