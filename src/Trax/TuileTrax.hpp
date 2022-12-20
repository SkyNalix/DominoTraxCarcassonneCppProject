#ifndef TUILE_TRAX_HPP
#define TUILE_TRAX_HPP

#include <iostream>
#include <vector>
#include "common/Bord.hpp"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;


class TuileTrax {
    private :
        int bord;
    public :
        TuileTrax(int &bord);
        vector<Bord<vector<int>>> getBords() const;
        Bord<vector<int>> getBord(const string& face) const;
        void draw(RenderWindow *app, int start_x, int start_y, int ZONE_WIDTH, int ZONE_HEIGHT );
        void turn();
};
Tuile* getRandomTuile();
