#ifndef DOMINOCARRE_HPP
#define DOMINOCARRE_HPP

#include <iostream>
#include <vector>
#include "Terrain.hpp"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class DominoCarre {
    public:
        int height;
        int width;
        int player = 0;
        int score1 = 0;
        int score2 = 0;
        int bag;
        DominoCarre(int h, int w);
        void start();
};

#endif