#ifndef TRAX_HPP
#define TRAX_HPP

#include <iostream>
#include <vector>
#include "Terrain.hpp"
#include <SFML/Graphics.hpp>
#include "Main.hpp"

using namespace sf;
using namespace std;

class Trax{
    public :
        int player = 0;
        Trax(int p);
        void start();

};

#endif