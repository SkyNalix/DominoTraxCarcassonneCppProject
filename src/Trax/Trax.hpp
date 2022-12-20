#ifndef TRAX_HPP
#define TRAX_HPP

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Terrain.hpp"
#include "TuileTrax.hpp"
#include "Main.hpp"

using namespace sf;
using namespace std;

class Trax{
    public :
        int height = 8;
        int width = 8; 
        Terrain<TuileTrax> terrain{8,8};
        int player = 0;
        Trax(int p);
        void start();

        int tryPlaceTuile(int y, int x, TuileTrax *tuile);
        vector<vector<int>> getPossiblePlacements(TuileTrax *tuile);
        int placeTuile(int y, int x, TuileTrax* tuile);

};

#endif