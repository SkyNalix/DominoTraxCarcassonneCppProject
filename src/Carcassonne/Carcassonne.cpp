#include "Carcassonne.hpp"




#define stringify( name ) #name
vector<string> string_of_direction {
    stringify(TOP),
    stringify(RIGHT),
    stringify(BOTTOM),
    stringify(LEFT)
};

vector<string> string_of_tilebord {
    stringify(GRASS),
    stringify(PATH),
    stringify(START_PATH),
    stringify(ABBEY),
    stringify(CITY),
    stringify(PROT_CITY),
    stringify(SOLO_CITY) 
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
    vector<int> positions {};
    for(int i = 0; i < 24; i++ ) {
        positions.push_back(i);
    }
    // shuffling
    for(int i = 0; i < 24; i++ ) {
        int j = rand() % 24;
        int tmp = positions[i];
        positions[i] = positions[j];
        positions[j] = tmp;
    }
    // selecting the first tile available
    for(int i = 0; i < 24; i++ ) {
        Tile tile = static_cast<Tile>(positions[i]);
        if(available_tiles[tile] != 0) {     
            TuileCarcassonne *tuile = new TuileCarcassonne(tile);
            tuile->initBords(tile_bords_list[tuile->tile]);
            return tuile;
        }
    }
    return nullptr;
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
        return false;
    }
    
    TuileCarcassonne *top = getTuile(y-1,x);
    TuileCarcassonne *right = getTuile(y,x+1);
    TuileCarcassonne *bottom = getTuile(y+1,x);
    TuileCarcassonne *left = getTuile(y,x-1);

    if(top == nullptr && right == nullptr && bottom == nullptr && left == nullptr ) {
        return false;
    }

    if(top != nullptr) {
        if( simplifyTileBord(top->bords[BOTTOM].tile)
                        != simplifyTileBord(tuile->bords[TOP].tile)) {
            return false;
        }
    }
    if(right != nullptr) {
        if( simplifyTileBord(right->bords[3].tile)
                        != simplifyTileBord(tuile->bords[1].tile)) {
            return false;
        }
    }
    if(bottom != nullptr) {

        if( simplifyTileBord(bottom->bords[0].tile)
                        != simplifyTileBord(tuile->bords[2].tile)) {
            return false;
        }
    }
    if(left != nullptr) {
        if( simplifyTileBord(left->bords[1].tile)
                        != simplifyTileBord(tuile->bords[3].tile)) {
            return false;
        }
    }
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

void Carcassonne::closeApp(RenderWindow *app) {
    app->close();
    openMenuPrincipal();
}















// tuile = tuile courante
// bord = quelle partie je regarde : ville, chemin...
// direction = là d'où je suis arrivé
// retourne couple (score, partisant trouvé);
tuple <int, CarColor> Carcassonne::calculScore_rec(TuileCarcassonne *tuile, int score, 
                    Tile_Bord bord, Direction direction) {
    if(tuile == nullptr || tuile->bords[direction].marque || bord != simplifyTileBord(tuile->bords[direction].tile))
        return make_tuple(score, NONE);

    tuple <int, CarColor> res;
    CarColor partisant = tuile->bords[direction].partisant;

    tuile->bords[direction].marque = true;
    Tile_Bord direction_bord = tuile->bords[direction].tile;
    Tile_Bord simpl_direction_bord = simplifyTileBord(direction_bord);

    score += simpl_direction_bord == CITY ? 2 : 1;
    if(direction_bord == SOLO_CITY || direction_bord == START_PATH || direction_bord == ABBEY){
        return make_tuple(score, tuile->bords[direction].partisant);
    }
    if(direction != TOP && simplifyTileBord(tuile->bords[TOP].tile) == bord) {
        tuple <int, CarColor> res_top = calculScore_rec(getTuile(tuile->y-1,tuile->x),score,bord,BOTTOM);
        if( get<1>(res_top) != NONE) 
            partisant = get<1>(res_top);
        tuile->bords[TOP].marque = true;
        score += get<0>(res_top) + bord == CITY ? 2 : 1;
    }
    if(direction != BOTTOM && simplifyTileBord(tuile->bords[BOTTOM].tile) == bord) {
        tuple <int, CarColor> res_bottom = calculScore_rec(getTuile(tuile->y+1,tuile->x),score,bord,TOP);
        if( get<1>(res_bottom) != NONE) 
            partisant = get<1>(res_bottom);
        tuile->bords[BOTTOM].marque = true;
        score += get<0>(res_bottom) + bord == CITY ? 2 : 1;
    }
    if(direction != RIGHT && simplifyTileBord(tuile->bords[RIGHT].tile) == bord) {
        tuple <int, CarColor> res_right = calculScore_rec(getTuile(tuile->y,tuile->x+1),score,bord,LEFT);
        if( get<1>(res_right) != NONE) 
            partisant = get<1>(res_right);
        tuile->bords[RIGHT].marque = true;
        score += get<0>(res_right) + bord == CITY ? 2 : 1 ;
    }
    if(direction != LEFT && simplifyTileBord(tuile->bords[LEFT].tile) == bord) {
        tuple <int, CarColor> res_left = calculScore_rec(getTuile(tuile->y,tuile->x+1),score,bord,RIGHT);
        if( get<1>(res_left) != NONE) 
            partisant = get<1>(res_left);
        tuile->bords[LEFT].marque = true;
        score += get<0>(res_left) + bord == CITY ? 2 : 1;
    }
    return make_tuple(score,partisant);
}

void Carcassonne::calculScore(int y, int x, TuileCarcassonne *tuile) {

    for(int i = 0; i<4; i++)
        tuile->bords[i].marque = true;

    tuple <int, CarColor> res_top = calculScore_rec(getTuile(y-1,x), 1, 
                                    simplifyTileBord(tuile->bords[TOP].tile), BOTTOM);
    if(get<1>(res_top)!=NONE) scores[get<1>(res_top)] += get<0>(res_top);
    tuple <int, CarColor> res_bottom = calculScore_rec(getTuile(y+1,x), 1, 
                                    simplifyTileBord(tuile->bords[BOTTOM].tile), TOP);
    if(get<1>(res_bottom)!=NONE) scores[get<1>(res_bottom)] += get<0>(res_bottom);
    tuple <int, CarColor> res_right = calculScore_rec(getTuile(y,x+1), 1, 
                                    simplifyTileBord(tuile->bords[RIGHT].tile), LEFT);
    if(get<1>(res_right) != NONE) scores[get<1>(res_right)] += get<0>(res_right);
    tuple <int, CarColor> res_left = calculScore_rec(getTuile(y,x-1), 1, 
                                    simplifyTileBord(tuile->bords[LEFT].tile), RIGHT);
    if(get<1>(res_left)!=NONE) scores[get<1>(res_left)] += get<0>(res_left);
}


// calcule la distance entre deux points 
int getDistance(Vector2i start, Vector2i end) {
    return sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2));
}


void Carcassonne::start(){

    loadTiles();
    for(int i =0; i < 4; i++ )
        scores.push_back(0);
    bool victory = false;

    int DRAW_WIDTH = 900;
    int DRAW_HEIGHT = 700;
    int controller_start_x = DRAW_WIDTH*0.75;
    int controller_width = DRAW_WIDTH*0.25;

    int blocks_on_screen = 5;
    int block_length = controller_start_x/blocks_on_screen;
    Font font;
    font.loadFromFile("./resources/arial.ttf");

    TuileCarcassonne *defaultTuile = new TuileCarcassonne(T_JUNCTION);
    defaultTuile->initBords(tile_bords_list[defaultTuile->tile]);
    defaultTuile->x = 0; defaultTuile->y = 0;
    tuiles.push_back(defaultTuile);
    TuileCarcassonne *pick = getRandomTuileCarcassonne();

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
    turn_sprite.setPosition(controller_start_x+(controller_width*0.25),200);
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
    tilemap.loadFromFile("resources/carcassonne/carcassonne_tilemap.png");
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

    Texture partisant_texture;
    partisant_texture.loadFromFile("resources/carcassonne/partisant_"+ carColorToString(player)+".png");
    Sprite partisant_sprite;
    partisant_sprite.setTexture(partisant_texture);
    partisant_sprite.scale(1,1);
    partisant_sprite.setPosition(controller_start_x + 80, 300);
    FloatRect partisant_bound = partisant_sprite.getGlobalBounds();

    bool partisant_placing = false;
    bool placed_tuile = false;
    bool calcul_done = false;

    int tiles_start_x = -2;
    int tiles_start_y = -2;

    RenderWindow app(VideoMode(DRAW_WIDTH, DRAW_HEIGHT, 32), "Carcassonne");
    while (app.isOpen()){
        Event event;
        while (app.pollEvent(event)){
            switch (event.type) {
                case Event::Closed:
                    closeApp(&app); break;
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
                    if (event.mouseButton.button == sf::Mouse::Right) {
                        // TODO enlever tous ce if
                        calcul_done = false;
                        victory = true;
                        
                    } else
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        Vector2f mouse = app.mapPixelToCoords(Mouse::getPosition(app));
                        if(retour_bounds.contains(mouse)){
                            closeApp(&app);
                        }
                        if(victory)
                            break;
                        
                        if(cross_bounds.contains(mouse)) {
                            placed_tuile = false;
                            switch(player) {
                                case RED: player = YELLOW; break;
                                case YELLOW: player = GREEN; break;
                                case GREEN: player = BLUE; break;
                                case BLUE: player = RED; break;
                                default: break;
                            }
                            player_text.setString("Joueur " + carColorToString(player));
                            pick = getRandomTuileCarcassonne();
                            if(pick == nullptr) {
                                victory = true;
                            } else {
                                pick_sprite.setTextureRect(tiles_rect[pick->tile]);
                                pick_sprite.setRotation(0); 

                                partisant_texture.loadFromFile("resources/carcassonne/partisant_"
                                        +carColorToString(player)+".png");
                                partisant_sprite.setTexture(partisant_texture);
                            }
                        } else if(!placed_tuile && turn_bounds.contains(mouse)){
                            pick->turn();
                            pick_sprite.setRotation(90*pick->rotation);       
                        } else if(placed_tuile && partisant_bound.contains(mouse)) {
                            partisant_placing = !partisant_placing;
                        }
                        if(0 < mouse.x && mouse.x < DRAW_WIDTH-200 && 0 < mouse.y && mouse.y < DRAW_HEIGHT) {

                            int x = mouse.x / block_length;
                            int y = mouse.y / block_length;
                            x+= tiles_start_x - (x<0 ? 1 : 0); 
                            y+= tiles_start_y - (y<0 ? 1 : 0);

                            if(!placed_tuile && !partisant_placing && placeTuile(y,x, pick)) {
                                placed_tuile = true;
                                available_tiles[pick->tile] = available_tiles[pick->tile]-1;
                            } else if(partisant_placing == true 
                                && pick->x==x && pick->y==y ) {

                                Vector2i mouse_point( ((int)mouse.x) % block_length,  ((int)mouse.y) % block_length);
                                int distance_top = getDistance(mouse_point, Vector2i(block_length/2, block_length/4));
                                int distance_bottom = getDistance(mouse_point, Vector2i(block_length/2, block_length-(block_length/4)));
                                int distance_right = getDistance(mouse_point, Vector2i( block_length/4, block_length/2 ) );
                                int distance_left = getDistance(mouse_point, Vector2i( block_length-(block_length/4), block_length/2 ) );

                                int distance = distance_top;
                                TuileCarcassonne *tuile_voisin = getTuile(y-1,x);
                                Direction side = TOP;
                                if(distance > distance_bottom) { 
                                    side = BOTTOM;
                                    tuile_voisin = getTuile(y+1,x);
                                    distance = distance_bottom;
                                }
                                if(distance > distance_left) {
                                    side = RIGHT;
                                    tuile_voisin = getTuile(y,x+1);
                                    distance = distance_left;
                                }
                                else if(distance > distance_right) {
                                    side = LEFT;
                                    tuile_voisin = getTuile(y,x-1);
                                }
                                if(pick->bords[side].partisant == NONE && pick->bords[side].tile != PROT_CITY) {
                                    // on reutilise cette méthode ici pour voir si il existe deja un partisant
                                    // dans la zone où on veut placer le partisant actuel
                                    pick->bords[side].marque = true;
                                    tuple <int, CarColor> res = calculScore_rec(tuile_voisin, 0, 
                                                                    simplifyTileBord(pick->bords[side].tile),
                                                                    static_cast<Direction>((side+1)%4));
                                    if(get<1>(res)==NONE) 
                                        pick->bords[side].partisant = player;
                                    pick->bords[side].marque = false;

                                    partisant_placing = false;
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

            // affichage des partisants
            for(size_t i = 0; i<tuile->bords.size(); i++ ) {
                CarColor partisant = tuile->bords[i].partisant;
                if(partisant==NONE)
                    continue;
                Texture texture;
                texture.loadFromFile("resources/carcassonne/partisant_"
                                +carColorToString(partisant)+".png");
                Sprite sprite;
                sprite.setTexture(texture);
                sprite.scale(tilemapscale/2,tilemapscale/2);
                int pos_x = block_length*x;
                int pos_y = block_length*y;
                if(i == 0) { // partisant en haut
                    pos_x += (block_length*0.8)/2;
                    pos_y += (block_length*0.5)/4;
                } else if(i == 1) { // partisant a droite
                    pos_x += block_length-(block_length/4);
                    pos_y += (block_length*0.8)/2;
                } else if(i == 2) { // en dessous
                    pos_x += (block_length*0.8)/2;
                    pos_y += block_length - (block_length/4);
                } else if(i == 3) { // a gauche
                    pos_x += (block_length*0.5)/4;
                    pos_y += (block_length*0.8)/2;
                }
                sprite.setPosition(pos_x, pos_y);
                app.draw(sprite);
            }
        }

        // affichage des controlles
        app.draw(player_text);
        app.draw(pick_sprite);
        

        if(victory) {
            // TODO victory
            if(!calcul_done) {
                for(size_t i = 0; i < tuiles.size(); i++)
                    for(int j = 0; j<4; j++) 
                        tuiles[i]->bords[j].marque = false;
                for(size_t i = 0; i < tuiles.size(); i++)
                    calculScore(tuiles[i]->y,tuiles[i]->x,tuiles[i]);
                calcul_done = true;
            }

            CarColor winner = RED;
            string winner_str = "rouge";
            if(scores[winner] < scores[GREEN] ) {
                winner = GREEN;
                winner_str = "vert";
            }
            if(scores[winner] < scores[YELLOW] ) {
                winner = YELLOW;
                winner_str = "jaune";
            }
            if(scores[winner] < scores[BLUE] ) {
                winner_str = "bleu";
            }

            RectangleShape rect(Vector2f(controller_start_x*0.50, DRAW_HEIGHT*0.25));
            rect.move(controller_start_x*0.25, DRAW_HEIGHT*0.40);
            app.draw(rect);

            Text text;
            text.setFont(font);
            text.setString("Joueur " + winner_str + " a gagne!");
            text.setCharacterSize(30);
            text.setFillColor(Color::Black);
            text.move(controller_start_x*0.3, DRAW_HEIGHT*0.44);
            app.draw(text);
            
        }

        if(partisant_placing) {
            Text partisant_text;
            partisant_text.setFont(font);
            partisant_text.setString("Placement du partisant");
            partisant_text.setFillColor(Color::Black);
            partisant_text.setCharacterSize(18);
            partisant_text.setPosition(controller_start_x+20, 380);
            app.draw(partisant_text);
        }
        
        app.draw(retour_sprite);
        app.draw(turn_sprite);
        app.draw(cross_sprite);
        app.draw(partisant_sprite);
        app.display();
    } 
}

