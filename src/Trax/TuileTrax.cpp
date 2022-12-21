#include "TuileTrax.hpp"

TuileTrax::TuileTrax(const vector<int> &bords) : bords{bords} {}



TuileTrax* getRandomTuileTrax(){
    // blanc = 0, rouge = 1
    if(rand() % 2 == 0){ 
        // blanc rouge blanc rouge   
        return new TuileTrax{vector<int>{0,1,0,1}};
    } else { 
        // blanc blanc rouge rouge 
        return new TuileTrax{vector<int>{0,0,1,1}};
    }
}

String TuileTrax::toTexturePath() {
    String path = "resources/trax/";
    for(int i = 0; i < 4; i++) {
        if(bords[i] == 0)
            path += "B";
        else
            path += "R";
    }
    return path + ".png";
}


void TuileTrax::draw(RenderWindow *app, int start_x, int start_y, int ZONE_WIDTH, int ZONE_HEIGHT){
    Texture texture;
    texture.loadFromFile(toTexturePath());
    Sprite sprite;
    sprite.setTexture(texture);
    sprite.scale(1,1);
    sprite.move(start_x, start_y);
    app->draw(sprite);
}

void TuileTrax::turn() {
    int tmp = bords[3];
    bords[3] = bords[2];
    bords[2] = bords[1];
    bords[1] = bords[0];
    bords[0] = tmp;
}