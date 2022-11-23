#include "Terrain.hpp"

Terrain::Terrain(int height, int width) : height{height}, width{width} {
    vector <vector<Tuile *>> plateau;
    for (int i = 0; i < height; i++) {
        vector < Tuile *> tmp{};
        for (int j = 0; j < width; j++) {
            tmp.push_back(nullptr);
        }
        plateau.push_back(tmp);
    }
    terrain = plateau;
}

Tuile * Terrain::getTuile(int y, int x) const {
    return getTerrain()[y][x];
}

vector<vector<Tuile *>> Terrain::getTerrain() const {
    return terrain;
}

int Terrain::getHeight() const {
    return height;
}

int Terrain::getWidth() const {
    return width;
}




bool checkBordsValues(Bord *bord1, Bord *bord2) {
    vector<int> bord1_val = ((BordDomino *) bord1)->getValeurs();
    vector<int> bord2_val = ((BordDomino *) bord2)->getValeurs();
    if(bord1_val.size() != bord2_val.size())
        return false;
    for(size_t i = 0; i < bord2_val.size(); i++){
        if (bord1_val[i] != bord2_val[i]) {
            return false;
        }
    }
    return true;
}

int calculPoints(Bord *bord1, Bord *bord2) {
    vector<int> bord1_val = ((BordDomino *) bord1)->getValeurs();
    vector<int> bord2_val = ((BordDomino *) bord2)->getValeurs();
    int points = 0;
    for(size_t i = 0; i < bord2_val.size(); i++){
        points += bord1_val[i];
    }
    return points;
}

// return -1 si le placement a echoué, les points gagnés sinon
int Terrain::tryPlaceTuile(int y, int x, Tuile *tuile) {
    int points = 0;
    if( x < width-1 && getTuile(y, x+1) != nullptr) {
        Bord * bord1 = tuile->getBord("est");
        Bord * bord2 = getTuile(y,x+1)->getBord("ouest");
        if (!checkBordsValues(bord1,bord2))
            return -1;
        points += calculPoints(bord1, bord2);
    }
    if( 0 < x && getTuile(y, x-1) != nullptr) {
        Bord * bord1 = tuile->getBord("ouest");
        Bord * bord2 = getTuile(y,x-1)->getBord("est");
        if (!checkBordsValues(bord1,bord2))
            return false;
        points += calculPoints(bord1, bord2);
    }
    if( 0 < y && getTuile(y-1, x) != nullptr) {
        Bord * bord1 = tuile->getBord("nord");
        Bord * bord2 = getTuile(y-1,x)->getBord("sud");
        if (!checkBordsValues(bord1,bord2))
            return false;
        points += calculPoints(bord1, bord2);
    }
    if( y < height-1 && getTuile(y+1, x) != nullptr) {
        Bord * bord1 = tuile->getBord("sud");
        Bord * bord2 = getTuile(y+1,x)->getBord("nord");
        if (!checkBordsValues(bord1,bord2))
            return false;
        points += calculPoints(bord1, bord2);
    }
    return points;
}

int Terrain::placeTuile(int y, int x, Tuile* tuile) {
    int n = tryPlaceTuile(y, x, tuile);
    if(n == -1)
        return -1;
    terrain[y][x] = tuile;
    return n;
}

