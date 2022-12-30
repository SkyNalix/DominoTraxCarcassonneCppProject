#include "TuileCarcassonne.hpp"

TuileCarcassonne::TuileCarcassonne(Tile tile) : tile{tile} {}


void TuileCarcassonne::turn() {
    rotation = (rotation+1)%4;
    Tile_Bord tmp = bords[3];
    bords[3] = bords[2];
    bords[2] = bords[1];
    bords[1] = bords[0];
    bords[0] = tmp;
}