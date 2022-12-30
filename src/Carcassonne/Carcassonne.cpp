#include "Carcassonne.hpp"


#define stringify( name ) #name
vector<string> string_of_tilebord {
    stringify(GRASS),
    stringify(CITY),
    stringify(PROT_CITY),
    stringify(SOLO_CITY),
    stringify(JUNCTION),
    stringify(ABBEY),
    stringify(START_PATH),
    stringify(PATH), 
};

vector<string> string_of_tile {
    stringify(T_CITY_GATE_AT_BOTTOM),
    stringify(T_PATH_TOP_BOTTOM),
    stringify(T_CITY_ON_TOP_JUNCTION),
    stringify(T_CITY_DIAGONAL),
    stringify(T_CITY_ON_TOP_PATHS_LEFT_RIGHT),
    stringify(T_CITY_ON_TOP_PATHS_BOTTOM_RIGHT),
    stringify(T_CITY_DIAGONAL_PATH_BOTTOM_RIGHT),
    stringify(T_CITY_GATE_AT_BOTTOM_PROTECTED),
    stringify(T_CITY_ON_TOP),
    stringify(T_CITY_ON_TOP_OTHER_LEFT),
    stringify(T_CITY_ON_LEFT_RIGHT_PROTECTED ),
    stringify(T_CITY_ON_TOP_PATH_BOTTOM_LEFT ),
    stringify(T_JUNCTION ),
    stringify(T_CITY_ON_TOP_OTHER_BOTTOM),
    stringify(T_CITY_PROTECTED ),
    stringify(T_PATH_BOTTOM_LEFT ),
    stringify(T_JUNCTION_BOTTOM_LEFT_RIGHT ),
    stringify(T_ABBEY ),
    stringify(T_ABBEY_PATH_BOTTOM ),
    stringify(T_FULL_CITY_PROTECTED ),
    stringify(T_CITY_ON_LEFT_RIGHT ),
    stringify(T_CITY_DIAGONAL_PROTECTED ),
    stringify(T_CITY_DIAGONAL_PATH_BOTTOM_RIGHT_PROTECTED ),
    stringify(T_CITY)
};


// Nord, est, sud, ouest, centre
vector<vector<Tile_Bord>> tile_bords_list {
    {CITY,CITY,START_PATH,CITY}, // T_CITY_GATE_AT_BOTTOM
    {PATH,GRASS,PATH,GRASS}, // T_PATH_TOP_BOTTOM
    {SOLO_CITY,START_PATH,START_PATH,START_PATH}, // T_CITY_ON_TOP_JUNCTION
    {CITY,GRASS,GRASS,CITY}, // T_CITY_DIAGONAL
    {SOLO_CITY, PATH, GRASS, PATH}, // T_CITY_ON_TOP_PATHS_LEFT_RIGHT
    {SOLO_CITY,PATH,PATH,GRASS}, // T_CITY_ON_TOP_PATHS_BOTTOM_RIGHT
    {CITY,PATH,PATH,CITY}, // T_CITY_DIAGONAL_PATH_BOTTOM_RIGHT
    {PROT_CITY,PROT_CITY,START_PATH,PROT_CITY}, // T_CITY_GATE_AT_BOTTOM_PROTECTED
    {SOLO_CITY,GRASS,GRASS,GRASS}, // T_CITY_ON_TOP
    {SOLO_CITY,GRASS,GRASS,SOLO_CITY}, // T_CITY_ON_TOP_OTHER_LEFT
    {GRASS,PROT_CITY,GRASS,PROT_CITY}, // T_CITY_ON_LEFT_RIGHT_PROTECTED 
    {SOLO_CITY,GRASS,PATH,PATH}, // T_CITY_ON_TOP_PATH_BOTTOM_LEFT 
    {START_PATH,START_PATH,START_PATH,START_PATH}, // T_JUNCTION 
    {SOLO_CITY,GRASS,SOLO_CITY,GRASS}, // T_CITY_ON_TOP_OTHER_BOTTOM
    {PROT_CITY,PROT_CITY,GRASS,PROT_CITY}, // T_CITY_PROTECTED 
    {GRASS,GRASS,PATH,PATH}, // T_PATH_BOTTOM_LEFT 
    {GRASS,START_PATH,START_PATH,START_PATH}, // T_JUNCTION_BOTTOM_LEFT_RIGHT 
    {ABBEY,ABBEY,ABBEY,ABBEY}, // T_ABBEY
    {ABBEY,ABBEY,START_PATH,ABBEY}, // T_ABBEY_PATH_BOTTOM 
    {PROT_CITY,PROT_CITY,PROT_CITY,PROT_CITY}, // T_FULL_CITY_PROTECTED 
    {GRASS,CITY,GRASS,CITY}, // T_CITY_ON_LEFT_RIGHT 
    {PROT_CITY,GRASS,GRASS,PROT_CITY}, // T_CITY_DIAGONAL_PROTECTED 
    {PROT_CITY,PATH,PATH,PROT_CITY}, // T_CITY_DIAGONAL_PATH_BOTTOM_RIGHT_PROTECTED 
    {CITY,CITY,GRASS,CITY} // T_CITY
};


vector<IntRect> tiles_rect {};

void loadTiles() {
    for(int i = 0; i <= 3; i++) {
        int max = i==3 ? 2:6;
        for(int j = 0; j <= max; j++) {
            tiles_rect.push_back(
                IntRect( j *256, i *256, 256, 256)
            );
        }
    }
}


map<Tile, int> default_available_tiles{
    { T_CITY_GATE_AT_BOTTOM, 1},
    { T_PATH_TOP_BOTTOM, 8},
    { T_CITY_ON_TOP_JUNCTION, 3},
    { T_CITY_DIAGONAL, 3},
    { T_CITY_ON_TOP_PATHS_LEFT_RIGHT, 4},
    { T_CITY_ON_TOP_PATHS_BOTTOM_RIGHT, 3},
    { T_CITY_DIAGONAL_PATH_BOTTOM_RIGHT, 3},
    { T_CITY_GATE_AT_BOTTOM_PROTECTED, 2},
    { T_CITY_ON_TOP, 5},
    { T_CITY_ON_TOP_OTHER_LEFT, 2},
    { T_CITY_ON_LEFT_RIGHT_PROTECTED, 2}, 
    { T_CITY_ON_TOP_PATH_BOTTOM_LEFT, 3}, 
    { T_JUNCTION, 1}, 
    { T_CITY_ON_TOP_OTHER_BOTTOM, 3},
    { T_CITY_PROTECTED, 1}, 
    { T_PATH_BOTTOM_LEFT, 9}, 
    { T_JUNCTION_BOTTOM_LEFT_RIGHT, 4}, 
    { T_ABBEY, 4}, 
    { T_ABBEY_PATH_BOTTOM, 2}, 
    { T_FULL_CITY_PROTECTED, 1}, 
    { T_CITY_ON_LEFT_RIGHT, 1}, 
    { T_CITY_DIAGONAL_PROTECTED, 2}, 
    { T_CITY_DIAGONAL_PATH_BOTTOM_RIGHT_PROTECTED, 2}, 
    { T_CITY, 3 }
};

Carcassonne::Carcassonne() : available_tiles{default_available_tiles} {}


TuileCarcassonne* Carcassonne::getRandomTuileCarcassonne() {
    Tile tile; //temp
    do {
        tile = static_cast<Tile>(rand() % 24);
    } while(available_tiles[tile] == 0);
    TuileCarcassonne *tuile = new TuileCarcassonne(tile);
    tuile->bords = tile_bords_list[tuile->tile];
    return tuile;
}


TuileCarcassonne * Carcassonne::getTuile(int y, int x) {
    for(size_t i = 0; i < tuiles.size(); i++ )
        if(tuiles[i]->x == x && tuiles[i]->y == y)
            return tuiles[i];
    return nullptr;
}

// simplifie les les TileBord pour facilement tester les égalités
Tile_Bord simplifyTileBord(Tile_Bord b1) {
    switch(b1) {
        case SOLO_CITY: case PROT_CITY: return CITY; break;
        case START_PATH: return PATH; break;
        case ABBEY: return PATH; break;
        default: return b1;
    }
    return b1;
}



// return false si le placement a echoué, true sinon
bool Carcassonne::tryPlaceTuile(int y, int x, TuileCarcassonne *tuile) {
    if(getTuile(y,x) != nullptr) {
        cout << "exit 1\n" << endl;;
        return false;
    }
    
    TuileCarcassonne *top = getTuile(y-1,x);
    TuileCarcassonne *right = getTuile(y,x+1);
    TuileCarcassonne *bottom = getTuile(y+1,x);
    TuileCarcassonne *left = getTuile(y,x-1);

    if(top == nullptr && right == nullptr && bottom == nullptr && left == nullptr ) {
        cout << "exit 2\n" << endl;;
        return false;
    }

    if(top != nullptr) {
        if( simplifyTileBord(top->bords[2])
                        != simplifyTileBord(tuile->bords[0])) {
            cout << "exit top " 
                    << string_of_tilebord[tile_bords_list[top->tile][2]]
                    << "(" << string_of_tile[top->tile] << ")"
                    << " != "
                    << string_of_tilebord[tuile->bords[0]]
                    << "(" << string_of_tile[tuile->tile] << ")"
                     << endl;
            return false;
        }
    }
    if(right != nullptr) {
        if( simplifyTileBord(right->bords[3])
                        != simplifyTileBord(tuile->bords[1])) {
            cout << "exit right " 
                    << string_of_tilebord[tile_bords_list[right->tile][3]]
                    << "(" << string_of_tile[right->tile] << ")"
                    << " != "
                    << string_of_tilebord[tuile->bords[1]] 
                    << "(" << string_of_tile[tuile->tile] << ")"
                    << endl;
            return false;
        }
    }
    if(bottom != nullptr) {



        if( simplifyTileBord(bottom->bords[0])
                        != simplifyTileBord(tuile->bords[2])) {
            cout << "exit bottom " 
                    << string_of_tilebord[tile_bords_list[bottom->tile][0]]
                    << "(" << string_of_tile[bottom->tile] << ")"
                    << " != "
                    << string_of_tilebord[tuile->bords[2]]
                    << "(" << string_of_tile[tuile->tile] << ")"
                    << endl;
            return false;
        }
    }
    if(left != nullptr) {
        if( simplifyTileBord(left->bords[1])
                        != simplifyTileBord(tuile->bords[3])) {
            cout << "exit left " 
                    << string_of_tilebord[tile_bords_list[left->tile][1]]
                    << "(" << string_of_tile[left->tile] << ")"
                    << " != "
                    << string_of_tilebord[tuile->bords[3]]
                    << "(" << string_of_tile[tuile->tile] << ")"
                    << endl;
            return false;
        }
    }
    printf("TRUE\n");
    return true;
}


bool Carcassonne::placeTuile(int y, int x, TuileCarcassonne* tuile) {
    bool n = tryPlaceTuile(y, x, tuile);
    if(n == false)
        return false;
    tuile->x = x;
    tuile->y = y;
    tuiles.push_back(tuile);
    return true;
}


int Carcassonne::checkVictory() {
    return -1;
}

void Carcassonne::start(){

    loadTiles();

    int victory = -1;

    int DRAW_WIDTH = 900;
    int DRAW_HEIGHT = 700;
    int controller_start_x = DRAW_WIDTH*0.75;
    int controller_width = DRAW_WIDTH*0.25;

    int blocks_on_screen = 5;
    int block_length = controller_start_x/blocks_on_screen;
    Font font;
    font.loadFromFile("./resources/arial.ttf");

    TuileCarcassonne *defaultTuile = new TuileCarcassonne(T_JUNCTION);
    defaultTuile->bords = tile_bords_list[defaultTuile->tile];
    defaultTuile->x = 0; defaultTuile->y = 0;
    tuiles.push_back(defaultTuile);
    TuileCarcassonne *t1 = new TuileCarcassonne(T_CITY_GATE_AT_BOTTOM_PROTECTED);
    t1->bords = tile_bords_list[t1->tile];
    t1->x = 0; t1->y = -1;
    tuiles.push_back(t1);
    t1 = new TuileCarcassonne(T_CITY_ON_TOP_PATH_BOTTOM_LEFT);
    t1->bords = tile_bords_list[t1->tile];
    t1->turn(); t1->turn();
    t1->x = -1; t1->y = 0;
    tuiles.push_back(t1);

    // TuileCarcassonne *pick = getRandomTuileCarcassonne();
    TuileCarcassonne *pick = new TuileCarcassonne(T_CITY_ON_TOP_PATHS_BOTTOM_RIGHT);
    pick->bords = tile_bords_list[pick->tile];
    


    Texture retour_texture;
    retour_texture.loadFromFile("./resources/Retour.jpg");
    Sprite retour_sprite;
    retour_sprite.setTexture(retour_texture);
    retour_sprite.setScale(1.5,1.5);
    retour_sprite.setPosition(controller_start_x+(controller_width*0.25),620);
    FloatRect retour_bounds = retour_sprite.getGlobalBounds();

    Texture turn_texture;
    turn_texture.loadFromFile("./resources/turn.jpg");
    Sprite turn_sprite;
    turn_sprite.setTexture(turn_texture);
    turn_sprite.setScale(0.3, 0.3);
    turn_sprite.setPosition(controller_start_x+(controller_width*0.25),300);
    FloatRect turn_bounds = turn_sprite.getGlobalBounds();

    Texture cross_texture;
    cross_texture.loadFromFile("./resources/cross.jpg");
    Sprite cross_sprite;
    cross_sprite.setTexture(cross_texture);
    cross_sprite.setScale(0.4, 0.4);
    cross_sprite.setPosition(controller_start_x+(controller_width*0.25),430);
    FloatRect cross_bounds = cross_sprite.getGlobalBounds();

    Text player_text;
    player_text.setFont(font);
    player_text.setString("Joueur 1");
    player_text.setFillColor(Color::Black);
    player_text.setCharacterSize(20);
    player_text.setPosition(controller_start_x+(controller_width*0.25), 6);


    Texture tilemap;
    tilemap.loadFromFile("resources/carcassonne_tilemap.png");
    float tilemapscale = ((float)block_length)/256.0 ;

    Sprite pick_sprite;
    pick_sprite.setTexture(tilemap);
    pick_sprite.scale(0.5,0.5);
    pick_sprite.setPosition(controller_start_x + 80, 120);
    pick_sprite.setTextureRect(tiles_rect[pick->tile]);

    pick_sprite.setOrigin(
            pick_sprite.getLocalBounds().width / 2.f, 
                    pick_sprite.getLocalBounds().height / 2.f
            );

    int tiles_start_x = -2;
    int tiles_start_y = -2;

    RenderWindow app(VideoMode(DRAW_WIDTH, DRAW_HEIGHT, 32), "Carcassonne");
    while (app.isOpen()){
        Event event;
        while (app.pollEvent(event)){
            switch (event.type) {
                case Event::Closed:
                    app.close(); break;
                case Event::KeyPressed : {
                    if(event.key.code == Keyboard::Left && tiles_start_x > -20)
                        tiles_start_x--;
                    if(event.key.code == Keyboard::Right && tiles_start_x < 20-blocks_on_screen)
                        tiles_start_x++;
                    if(event.key.code == Keyboard::Up && tiles_start_y > -20)
                        tiles_start_y--;
                    if(event.key.code == Keyboard::Down && tiles_start_y < 20-blocks_on_screen)
                        tiles_start_y++;
                    if(event.key.code == Keyboard::PageDown || event.key.code == Keyboard::PageUp) {
                        if(event.key.code == Keyboard::PageDown)
                            blocks_on_screen = min(blocks_on_screen+1, 20);
                        if(event.key.code == Keyboard::PageUp)
                            blocks_on_screen = max(3,blocks_on_screen-1);
                        block_length = controller_start_x/blocks_on_screen;
                        tilemapscale = ((float)block_length)/256.0 ;
                    }
                    break;
                }
                case Event::MouseButtonPressed: {
                    if (victory==-1 && event.mouseButton.button == sf::Mouse::Left) {
                        Vector2f mouse = app.mapPixelToCoords(Mouse::getPosition(app));
                        if(retour_bounds.contains(mouse)){
                            app.close();
                            openMenuPrincipal();
                        } else if(cross_bounds.contains(mouse)) {
                            
                            pick = getRandomTuileCarcassonne();
                            pick_sprite.setTextureRect(tiles_rect[pick->tile]);
                            pick_sprite.setRotation(0);  

                        } else if(turn_bounds.contains(mouse)){
                            pick->turn();
                            pick_sprite.setRotation(90*pick->rotation);       
                        }
                        if(0 < mouse.x && mouse.x < DRAW_WIDTH-200 && 0 < mouse.y && mouse.y < DRAW_HEIGHT) {

                            int x = (mouse.x / block_length);
                            int y = (mouse.y / block_length);
                            x+= tiles_start_x - (x<0 ? 1 : 0); 
                            y+= tiles_start_y - (y<0 ? 1 : 0);
                            
                            if(placeTuile(y,x, pick)) {

                                available_tiles[pick->tile] = available_tiles[pick->tile]-1;
                                pick = getRandomTuileCarcassonne();
                                pick_sprite.setTextureRect(tiles_rect[pick->tile]);

                                // player = (player+1) %2;
                                // string player_str = player==0 ? "blanc" : "rouge";
                                // player_text.setString("Joueur " + player_str);
                                // victory = checkVictory();
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
        line.setPosition(controller_start_x, 0);
        line.setFillColor(Color(0,0,0));
        app.draw(line);

        // affichage du terrain de jeu
        for(size_t i = 0; i < tuiles.size(); i++) {
            TuileCarcassonne *tuile = tuiles[i];
            
            if(tuile->x < tiles_start_x || tuile->x > tiles_start_x+(blocks_on_screen-1)
                || tuile->y < tiles_start_y || tuile->y > tiles_start_y+(blocks_on_screen-1))
                continue;

            int x = abs(tuile->x-tiles_start_x);
            int y = abs(tuile->y-tiles_start_y);

            Sprite sprite;
            sprite.setTexture(tilemap);
            sprite.scale(tilemapscale,tilemapscale);
            sprite.setTextureRect(tiles_rect[tuile->tile]);
            sprite.setPosition(block_length*x, block_length*y);

            if(tuile->rotation > 0) {
                sprite.setOrigin(
                        sprite.getLocalBounds().width / 2.f, 
                        sprite.getLocalBounds().height / 2.f
                        );
                sprite.setRotation(tuile->rotation * 90);
                sprite.move(block_length/2, block_length/2);
            }
            app.draw(sprite);
        }

        // affichage des controlles
        app.draw(player_text);
        app.draw(pick_sprite);
        

        if(victory > -1) {
            // TODO victory
        }
        
        app.draw(retour_sprite);
        app.draw(turn_sprite);
        app.draw(cross_sprite);
        app.display();
    } 
}

