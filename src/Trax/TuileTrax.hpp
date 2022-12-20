#ifndef TUILE_TRAX_HPP
#define TUILE_TRAX_HPP

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "common/Bord.hpp"

using namespace std;
using namespace sf;


class TuileTrax {
    public :
        vector<Bord<int>> bords;
        TuileTrax(const vector<Bord<int>> &bords);
        void draw(RenderWindow *app, int start_x, int start_y, int ZONE_WIDTH, int ZONE_HEIGHT );
        void turn();
};
TuileTrax* getRandomTuileTrax();

#endif 