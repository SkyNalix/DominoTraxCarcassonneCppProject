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

// return -1 si le placement a echoué, les points gagnes sinon
int Trax::tryPlaceTuile(int y, int x, TuileTrax *tuile) {
    int points = 0;
    if( x < 0 || width <= x || y < 0 || height <= y || terrain.getTuile(y, x) != nullptr ) 
        return -1;

    // TODO

    return points;
}

 vector<vector<int>> Trax::getPossiblePlacements(TuileTrax *tuile) {
    vector<vector<int>> res{};
    for(int i = 0 ; i < terrain.getHeight(); i++) {
        vector<int> list{};
        for(int j = 0; j < terrain.getWidth(); j++) {
            list.push_back(tryPlaceTuile(i, j, tuile));
        }
        res.push_back(list);
    }
    return res;
}

int Trax::placeTuile(int y, int x, TuileTrax* tuile) {
    int n = tryPlaceTuile(y, x, tuile);
    if(n == -1)
        return -1;
    terrain.terrain[y][x] = tuile;
    return n;
}

void Trax::start(){
    bool victory = false;

    int DRAW_WIDTH = 800;
    int DRAW_HEIGHT = 700;
    int controller_start_x = DRAW_WIDTH*0.75;
    int controller_width = DRAW_WIDTH*0.25;
                            int block_width = controller_start_x/terrain.getWidth();
                            int block_height = DRAW_HEIGHT/terrain.getHeight();
    Font font;
    font.loadFromFile("./resources/arial.ttf");

    string texture_tuile_nom = "";
    TuileTrax *pick = getRandomTuileTrax();
    vector<vector<int>> possible_placements = getPossiblePlacements(pick);
    

    if(pick->bords[0].x == 0 && pick->bords[1].x == 0 ){
        texture_tuile_nom = "./resources/TraxBlancBlancRougeRouge.png";
    }else {
        texture_tuile_nom = "./resources/TraxBlancRougeBlancRouge.png";
    }

    Texture tuile_texture;
    tuile_texture.loadFromFile(texture_tuile_nom);
    Sprite tuile_sprite;
    tuile_sprite.setTexture(tuile_texture);
    tuile_sprite.setScale(0.05,0.05);
    tuile_sprite.move(controller_start_x+(controller_width*0.25),150);
    FloatRect tuile_bounds = tuile_sprite.getGlobalBounds();


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


    Text player_text;
    player_text.setFont(font);
    player_text.setString("Joueur 1");
    player_text.setFillColor(Color::Black);
    player_text.setCharacterSize(30);
    player_text.move(controller_start_x+(controller_width*0.25), 6);


    RenderWindow app(VideoMode(DRAW_WIDTH, DRAW_HEIGHT, 32), "Trax");
    while (app.isOpen()){
        Event event;
        while (app.pollEvent(event)){
            switch (event.type) {
                case Event::Closed:
                    app.close(); break;
                case Event::MouseButtonPressed: {
                    if (!victory && event.mouseButton.button == sf::Mouse::Left) {
                        Vector2f mouse = app.mapPixelToCoords(Mouse::getPosition(app));
                        if(retour_bounds.contains(mouse)){
                            app.close();
                            Main::openMenuPrincipal();
                        }else if(turn_bounds.contains(mouse)){
                            //rotateTuile(pick);
                            pick->turn();
                            texture_tuile_nom = updateTuile(texture_tuile_nom);
                            tuile_texture.loadFromFile(texture_tuile_nom);
                            Sprite tuile_sprite;
                            tuile_sprite.setTexture(tuile_texture);
                            tuile_sprite.setScale(0.05,0.05);
                            tuile_sprite.move(controller_start_x+(controller_width*0.25),150);
                            FloatRect tuile_bounds = tuile_sprite.getGlobalBounds();
                                                    
                        }
                        if(0 < mouse.x && mouse.x < DRAW_WIDTH-200 && 0 < mouse.y && mouse.y < DRAW_HEIGHT) {

                            int x = mouse.x / block_width;
                            int y = mouse.y / block_height;
                            if(0 <= x && x < terrain.getWidth() && 0 <= y && y < terrain.getHeight()) {
                                if(possible_placements[y][x] == -1)
                                    break;
                                int points = placeTuile(y,x, pick);
                                pick = getRandomTuileTrax();
                                possible_placements = getPossiblePlacements(pick);
                                player = (player+1) %2;
                                player_text.setString("Joueur " + to_string(player+1));

                                //texture_tuile_nom = updateTuile(texture_tuile_nom);
                                tuile_texture.loadFromFile(texture_tuile_nom);
                                Sprite tuile_sprite;
                                tuile_sprite.setTexture(tuile_texture);
                                tuile_sprite.setScale(0.05,0.05);
                                tuile_sprite.move(mouse.x,mouse.y);
                                FloatRect tuile_bounds = tuile_sprite.getGlobalBounds();
                                app.draw(tuile_sprite); 
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
        app.draw(tuile_sprite);
        int pick_start_x = controller_start_x+(controller_width*0.1);
        int pick_end_x = controller_start_x+(controller_width*0.9);
        app.draw(retour_sprite);
        app.draw(turn_sprite);

        app.display();
    } 
}

