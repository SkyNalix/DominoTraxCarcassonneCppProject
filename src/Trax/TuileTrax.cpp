#include "TuileTrax.hpp"
// #include "Bord.hpp"
#include "common/Bord.hpp"

TuileTrax::TuileTrax(const vector<Bord<int>> &bords) : bords{bords} {}



TuileTrax* getRandomTuileTrax(){
    vector<Bord<int>> bords{};

    // blanc = 0, rouge = 1

    int random = rand() % 2;
    if(random == 0){ // blanc rouge blanc rouge   
        bords.push_back(0);
        bords.push_back(1);
        bords.push_back(0);
        bords.push_back(1);  
    } else if(random == 1){ // blanc blanc rouge rouge
        bords.push_back(0);
        bords.push_back(0);
        bords.push_back(1);
        bords.push_back(1);
    }
    return new TuileTrax{bords};
}

void TuileTrax::draw(RenderWindow *app, int start_x, int start_y, int ZONE_WIDTH, int ZONE_HEIGHT){
    Texture texture; texture.loadFromFile("./resources/TraxBlancBlancRougeRouge.png");
    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(0.05,0.05);
    sprite.move(ZONE_WIDTH,ZONE_HEIGHT);
    app->draw(sprite);
    app->display();
}

void TuileTrax::turn() {
    
}