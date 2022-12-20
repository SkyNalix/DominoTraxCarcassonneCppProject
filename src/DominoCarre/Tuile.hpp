#ifndef TUILE_HPP
#define TUILE_HPP

#include <iostream>
#include <vector>
#include "common/Bord.hpp"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;


class Tuile {
    private :
        vector<Bord<vector<int>>> bords;
    public :
        Tuile(const vector<Bord<vector<int>>> &bords);
        vector<Bord<vector<int>>> getBords() const;
        Bord<vector<int>> getBord(const string& face) const;
        void draw(RenderWindow *app, int start_x, int start_y, int ZONE_WIDTH, int ZONE_HEIGHT );
        void drawTrax(RenderWindow *app, int start_x, int start_y, int ZONE_WIDTH, int ZONE_HEIGHT,Sprite sprite);
        void turn();
};
Tuile* getRandomTuile();
Tuile* getRandomTuileTrax();

#endif 