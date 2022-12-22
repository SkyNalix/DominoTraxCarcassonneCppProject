#include "Trax.hpp"

Trax::Trax(int p): player{p} {}


string updateTuile(string tuile){
        cout << "Tuile :" << tuile << endl;
    if(tuile.compare("./resources/TraxBlancBlancRougeRouge.png") == 0){
        cout << "blanc blanc rouge rouge -> rouge blanc blanc rouge" << endl;
        return "./resources/TraxRougeBlancBlancRouge.png";
    }else if(tuile.compare("./resources/TraxRougeBlancBlancRouge.png") == 0){
        cout << "rouge blanc blanc rouge -> rouge rouge blanc blanc" << endl;
        return "./resources/TraxRougeRougeBlancBlanc.png";
    }else if(tuile.compare("./resources/TraxRougeRougeBlancBlanc.png") == 0){
        cout << "rouge rouge blanc blanc -> blanc rouge rouge blanc" << endl;
        return "./resources/TraxBlancRougeRougeBlanc.png";
    }else if(tuile.compare("./resources/TraxBlancRougeRougeBlanc.png") == 0){
        cout << "rouge rouge blanc blanc -> blanc blanc rouge rouge" << endl;
        return "./resources/TraxBlancBlancRougeRouge.png";
    }else if(tuile.compare("./resources/TraxBlancRougeBlancRouge.png") == 0){
        return "./resources/TraxRougeBlancRougeBlanc.png";
    }else if (tuile.compare("./resources/TraxRougeBlancRougeBlanc.png") == 0){
        cout << "Rouge Blanc Rouge Blanc -> Blanc Rouge Blanc Rouge" << endl;
        return "./resources/TraxBlancRougeBlancRouge.png";
    }
    return tuile;
}

// return false si le placement a echoué, true sinon
bool Trax::tryPlaceTuile(int y, int x, TuileTrax *tuile) {
    if( x < 0 || width <= x || y < 0 || height <= y || terrain.getTuile(y, x) != nullptr ) 
        return false;
    
    if(terrain.getTuile(y, x+1) == nullptr 
        && terrain.getTuile(y, x-1) == nullptr 
        && terrain.getTuile(y+1, x) == nullptr 
        && terrain.getTuile(y-1, x) == nullptr 
        && terrain.isEmpty() ) {
        return true;
    }

    if( terrain.getTuile(y, x+1) != nullptr) {
        if (tuile->bords[1] == terrain.getTuile(y,x+1)->bords[3])
            return true;
    }
    if( terrain.getTuile(y, x-1) != nullptr) {
        if (tuile->bords[3] == terrain.getTuile(y,x-1)->bords[1])
            return true;
    }
    if( terrain.getTuile(y-1, x) != nullptr) {
        if (tuile->bords[0] == terrain.getTuile(y-1,x)->bords[2])
            return true;
    }
    if( terrain.getTuile(y+1, x) != nullptr) {
        if (tuile->bords[2] == terrain.getTuile(y+1, x)->bords[0])
            return true;
    }
    return false;
}

bool Trax::placeTuile(int y, int x, TuileTrax* tuile) {
    bool n = tryPlaceTuile(y, x, tuile);
    if(n == false)
        return false;
    terrain.terrain[y][x] = tuile;
    return true;
}


void Trax::angleForcedPlays(int y, int x) {
    TuileTrax * top = terrain.getTuile(y-1,x);
    TuileTrax * right = terrain.getTuile(y,x+1);
    TuileTrax * bottom = terrain.getTuile(y+1,x);
    TuileTrax * left = terrain.getTuile(y,x-1);
    if(
        top != nullptr && left != nullptr
        && top->bords[2] == left->bords[1]
    ) {
        BordColor c1 = top->bords[2];
        BordColor c2 = c1 == white ? red : white;
        placeTuile(y,x, new TuileTrax(vector<BordColor>{c1,c2,c2,c1}));
        return;
    }
    if(
        top != nullptr && right != nullptr
        && top->bords[2] == right->bords[3]
    ) {
        BordColor c1 = top->bords[2];
        BordColor c2 = c1 == white ? red : white;
        placeTuile(y,x, new TuileTrax(vector<BordColor>{c1,c1,c2,c2}));
        return;
    }

    if(
        bottom != nullptr && left != nullptr
        && bottom->bords[0] == left->bords[1]
    ) {
        BordColor c1 = bottom->bords[0];
        BordColor c2 = c1 == white ? red : white;
        placeTuile(y,x, new TuileTrax(vector<BordColor>{c2,c2,c1,c1}));
        return;
    }
    if(
        bottom != nullptr && right != nullptr
        && bottom->bords[0] == right->bords[3]
    ) {
        BordColor c1 = bottom->bords[0];
        BordColor c2 = c1 == white ? red : white;
        placeTuile(y,x, new TuileTrax(vector<BordColor>{c2,c1,c1,c2}));
        return;
    }
}

void Trax::lineForcedPlays(int y, int x) {
    TuileTrax * top = terrain.getTuile(y-1,x);
    TuileTrax * bottom = terrain.getTuile(y+1,x);
    if(
        top != nullptr && bottom != nullptr
        && top->bords[2] == bottom->bords[0]
    ) {
        BordColor c1 = top->bords[2];
        BordColor c2 = c1 == white ? red : white;
        placeTuile(y,x, new TuileTrax(vector<BordColor>{c1,c2,c1,c2}));
        return;
    }
    TuileTrax * left = terrain.getTuile(y,x-1);
    TuileTrax * right = terrain.getTuile(y,x+1);
    if(
        left != nullptr && right != nullptr
        && left->bords[1] == right->bords[3]
    ) {
        BordColor c1 = left->bords[1];
        BordColor c2 = c1 == white ? red : white;
        placeTuile(y,x, new TuileTrax(vector<BordColor>{c2,c1,c2,c1}));
    } 
    return;
}


void Trax::doAllForcedPlays() {
    for(int y = 0 ; y < terrain.height; y++) {
        for(int x = 0; x < terrain.width; x++) {
            if(terrain.getTuile(y,x) == nullptr)
                angleForcedPlays(y,x);
            if(terrain.getTuile(y,x) == nullptr)
                lineForcedPlays(y,x);
        }
    }
}



vector<tuple<int, TuileTrax *>> unionLists(vector<tuple<int, TuileTrax *>> a, vector<tuple<int, TuileTrax *>> b) {
    for(size_t i = 0; i < b.size(); i++ ) {
        a.push_back(b[i]);
    }
    return a;
}

/*
bool listContainTuile(vector<tuple<int, TuileTrax *>> l, tuple<int, TuileTrax *> *t) {
    for(size_t i = 0; i < l.size(); i++ ) {
        if(get<0>(l[i]) == get<0>(*t))
            return true;
    }
    return false;
}

tuple <bool, vector<tuple<int, TuileTrax *>>> Trax::checkVictoryOnPath
        (vector<tuple<int, TuileTrax *>> visited,
                int player,
                tuple<int, TuileTrax *> current
                 ) {

    if(get<1>(current) == nullptr || listContainTuile(visited, &current)) 
                return make_tuple(true, visited);
}
*/

// cherche et renvoi un joueur gagnant
int Trax::checkVictory() {
    /*
    vector<tuple<int, TuileTrax *>> visited{};
    for(int y = 0; y < terrain.height; y++) {
        for(int x = 0; x < terrain.getWidth(); x++) {
            TuileTrax* tuile = terrain.getTuile(y,x);
            int player = 0;
            tuple<int, TuileTrax *> current = make_tuple(player, tuile);
            if(tuile == nullptr || listContainTuile(visited, &current)) continue;
        
            tuple <bool, vector<tuple<int, TuileTrax *>>> path_search 
                    = checkVictoryOnPath({}, player, current);
            if( get<0>(path_search)) 
                return player;
            visited = unionLists(visited, get<1>(path_search));
        }
    }
    */
    return -1;
}

void Trax::start(){
    int victory = -1;

    int DRAW_WIDTH = 800;
    int DRAW_HEIGHT = 700;
    int controller_start_x = DRAW_WIDTH*0.75;
    int controller_width = DRAW_WIDTH*0.25;
    int block_width = controller_start_x/terrain.width;
    int block_height = DRAW_HEIGHT/terrain.height;
    Font font;
    font.loadFromFile("./resources/arial.ttf");

    TuileTrax defaultTuile = TuileTrax(vector<BordColor>{white,red,white,red});
    TuileTrax *pick = new TuileTrax(defaultTuile);
    

    Texture retour_texture;
    retour_texture.loadFromFile("./resources/Retour.jpg");
    Sprite retour_sprite;
    retour_sprite.setTexture(retour_texture);
    retour_sprite.setScale(1.5,1.5);
    retour_sprite.move(controller_start_x+(controller_width*0.25),620);
    FloatRect retour_bounds = retour_sprite.getGlobalBounds();

    Texture turn_texture;
    turn_texture.loadFromFile("./resources/turn.jpg");
    Sprite turn_sprite;
    turn_sprite.setTexture(turn_texture);
    turn_sprite.setScale(0.3, 0.3);
    turn_sprite.move(controller_start_x+(controller_width*0.25),300);
    FloatRect turn_bounds = turn_sprite.getGlobalBounds();

    Texture flip_texture;
    flip_texture.loadFromFile("./resources/flip.png");
    Sprite flip_sprite;
    flip_sprite.setTexture(flip_texture);
    flip_sprite.setScale(0.4, 0.4);
    flip_sprite.move(controller_start_x+(controller_width*0.30),430);
    FloatRect flip_bounds = flip_sprite.getGlobalBounds();


    Text player_text;
    player_text.setFont(font);
    player_text.setString("Joueur 1");
    player_text.setFillColor(Color::Black);
    player_text.setCharacterSize(20);
    player_text.move(controller_start_x+(controller_width*0.25), 6);


    RenderWindow app(VideoMode(DRAW_WIDTH, DRAW_HEIGHT, 32), "Trax");
    while (app.isOpen()){
        Event event;
        while (app.pollEvent(event)){
            switch (event.type) {
                case Event::Closed:
                    app.close(); break;
                case Event::MouseButtonPressed: {
                    if (victory==-1 && event.mouseButton.button == sf::Mouse::Left) {
                        Vector2f mouse = app.mapPixelToCoords(Mouse::getPosition(app));
                        if(retour_bounds.contains(mouse)){
                            app.close();
                            openMenuPrincipal();
                        } else if(turn_bounds.contains(mouse)){
                            pick->turn();
                        } else if(flip_bounds.contains(mouse)) {
                            if(pick->bords[0] == pick->bords[1] || pick->bords[1] == pick->bords[2]) {
                                // pick = tuile AABB avec n'importe quel rotation
                                pick = new TuileTrax(vector<BordColor>{white,red,white,red});
                            } else {
                                // pick = tuile ABAB
                                pick = new TuileTrax(vector<BordColor>{white,white,red,red});
                            }
                        }
                        if(0 < mouse.x && mouse.x < DRAW_WIDTH-200 && 0 < mouse.y && mouse.y < DRAW_HEIGHT) {

                            int x = mouse.x / block_width;
                            int y = mouse.y / block_height;
                            if(0 <= x && x < terrain.width && 0 <= y && y < terrain.height) {
                            
                                if(placeTuile(y,x, pick)) {
                                    doAllForcedPlays();
                                    pick = new TuileTrax(defaultTuile);
                                    player = (player+1) %2;

                                    string player_str = player==0 ? "blanc" : "rouge";
                                    player_text.setString("Joueur " + player_str);

                                    victory = checkVictory();
                                }
                           }
                        }
                    } 
                    break;
                }
                default: break;
            }
        }
        app.clear();
        app.draw(RectangleShape(Vector2f(DRAW_WIDTH, DRAW_HEIGHT))); // fond blanc

        // affichage de la ligne separation entre le jeu et les controlles
        RectangleShape line(Vector2f(5, DRAW_HEIGHT));
        line.move(controller_start_x, 0);
        line.setFillColor(Color(0,0,0));
        app.draw(line);

        // affichage du terrain de jeu
        terrain.draw(&app, controller_start_x, DRAW_HEIGHT);

        // affichage des controlles
        app.draw(player_text);
        int pick_start_x = controller_start_x+(controller_width*0.3);
        int pick_end_x = controller_start_x+(controller_width*0.9);
        pick->draw(&app, 
            pick_start_x, 120, 
            pick_end_x-pick_start_x, 
            pick_end_x-pick_start_x
            );
        

        if(victory > -1) {
            // TODO victory
        }
        
        app.draw(retour_sprite);
        app.draw(turn_sprite);
        app.draw(flip_sprite);
        app.display();
    } 
}

