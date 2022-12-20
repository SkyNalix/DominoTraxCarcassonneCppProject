#ifndef TUILE_DOMINO_HPP
#define TUILE_DOMINO_HPP

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "common/Bord.hpp"

using namespace std;
using namespace sf;

class TuileDomino {
    public :
        vector<Bord<vector<int>>> bords;
        TuileDomino(const vector<Bord<vector<int>>> &bords);
        void draw(RenderWindow *app, int start_x, int start_y, int ZONE_WIDTH, int ZONE_HEIGHT ); 
        void turn(); 
};
TuileDomino* getRandomTuileDomino();


#endif 