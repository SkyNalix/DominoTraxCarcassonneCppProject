#ifndef CARCASSONNE_HPP
#define CARCASSONNE_HPP

#include "Terrain.hpp"
#include "TuileCarcassonne.hpp"
#include "Main.hpp"

using namespace sf;
using namespace std;

class Carcassonne {
    public :
        map<Tile, int> available_tiles{};
        vector<TuileCarcassonne *> tuiles{};
        int player = 0;
        Carcassonne();
        void start();

    private:
        TuileCarcassonne* getRandomTuileCarcassonne();
        TuileCarcassonne * getTuile(int y, int x);
        bool tryPlaceTuile(int y, int x, TuileCarcassonne *tuile);
        bool placeTuile(int y, int x, TuileCarcassonne* tuile);
        int checkVictory();

};

#endif