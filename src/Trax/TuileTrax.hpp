#ifndef TUILE_TRAX_HPP
#define TUILE_TRAX_HPP

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class TuileTrax {
    public :
        vector<int> bords;
        TuileTrax(const vector<int> &bords);
        void draw(RenderWindow *app, int start_x, int start_y, int ZONE_WIDTH, int ZONE_HEIGHT );
        void turn();
        String toTexturePath();
};
TuileTrax* getRandomTuileTrax();

#endif 