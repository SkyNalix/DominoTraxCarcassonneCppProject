#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <iostream>
#include "Tuile.hpp"
#include "BordDomino.hpp"
using namespace std;

class Terrain {
    private:
        int height;
        int width;
        vector<vector<Tuile *>> terrain{};
    public:
        Terrain(int height, int width);
        Tuile * getTuile(int x , int y) const;
        int placeTuile(int x, int y, Tuile* tuile);
        vector<vector<Tuile *>> getTerrain() const;
        int getHeight() const;
        int getWidth() const;
        int tryPlaceTuile(int y, int x, Tuile *tuile);
};

#endif //TERRAIN_HPP
