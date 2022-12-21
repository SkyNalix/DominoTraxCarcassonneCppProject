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

    private:
        bool tryPlaceTuile(int y, int x, TuileTrax *tuile);
        vector<vector<bool>> getPossiblePlacements(TuileTrax *tuile);
        bool placeTuile(int y, int x, TuileTrax* tuile);
        void doAllForcedPlays();
        void angleForcedPlays(int y, int x);
        void lineForcedPlays(int y, int x);
        tuple <bool, vector<tuple<int, TuileTrax *>>> checkVictoryOnPath(
                vector<tuple<int, TuileTrax *>> visited,
                int player,
                tuple<int, TuileTrax *> current
            );
        int checkVictory();


};

#endif