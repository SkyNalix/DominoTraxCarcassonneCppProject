#ifndef CARCASSONNE_HPP
#define CARCASSONNE_HPP

#include <random>

#include "Terrain.hpp"
#include "TuileCarcassonne.hpp"
#include "Main.hpp"

using namespace sf;
using namespace std;


class Carcassonne {
    public :
        map<Tile, int> available_tiles{};
        vector<TuileCarcassonne *> tuiles{};
        CarColor player = RED;
        vector<int> scores;
        Carcassonne();
        void start();

    private:
        TuileCarcassonne* getRandomTuileCarcassonne();
        TuileCarcassonne * getTuile(int y, int x);
        bool tryPlaceTuile(int y, int x, TuileCarcassonne *tuile);
        bool placeTuile(int y, int x, TuileCarcassonne* tuile);
        tuple <int, CarColor> calculScore_rec(TuileCarcassonne *tuile, int score, Tile_Bord bord, Direction direction);
        void calculScore(int y, int x, TuileCarcassonne *tuile);
        void closeApp(RenderWindow* app);
};


#endif