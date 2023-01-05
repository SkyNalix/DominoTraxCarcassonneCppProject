#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <iostream>
#include "Tuile.hpp"
#include "Bord.hpp"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Terrain {
    private:
        int height;
        int width;
        vector<vector<Tuile *>> terrain{};
    public:
        Terrain(int height, int width);
        Tuile * getTuile(int y, int x) const;
        int placeTuile(int y, int x, Tuile* tuile);
        vector<vector<Tuile *>> getTerrain() const;
        int getHeight() const;
        int getWidth() const;
        int tryPlaceTuile(int y, int x, Tuile *tuile);
        void draw(RenderWindow *app, int WIDTH, int HEIGHT);
        void drawTrax(RenderWindow *app, int WIDTH, int HEIGHT,Sprite sprite);
        vector<vector<int>> getPossiblePlacements(Tuile *tuile);
        bool propage(int x,int y);
        bool isEmpty();
};

#endif //TERRAIN_HPP