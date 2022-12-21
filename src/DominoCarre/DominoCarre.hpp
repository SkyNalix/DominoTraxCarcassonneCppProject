#ifndef DOMINOCARRE_HPP
#define DOMINOCARRE_HPP

#include <iostream>
#include <vector>
#include "unistd.h"
#include <SFML/Graphics.hpp>

#include "Terrain.hpp"
#include "Main.hpp"
#include "TuileDomino.hpp"
using namespace sf;
using namespace std;

class DominoCarre {
    public:
        int height;
        int width;
        Terrain<TuileDomino> terrain;
        int player = 0;
        int score1 = 0;
        int score2 = 0;
        int bag;
        DominoCarre(int h, int w);
        void start();
        
        int tryPlaceTuile(int y, int x, TuileDomino *tuile);
        vector<vector<int>> getPossiblePlacements(TuileDomino *tuile);
        int placeTuile(int y, int x, TuileDomino* tuile);

};
int calculPoints(vector<int> bord1, vector<int> bord2);

#endif