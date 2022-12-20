#include "DominoCarre.hpp"
#include "Main.hpp"
#include "unistd.h"

DominoCarre::DominoCarre(int h, int w) {
    
    if(h <= 1 && w <= 1 ) {
        height = 5;
        width = 5;
    } else {
        height = h;
        width = w;
    }
    bag = (height*width)*0.75;
    if(bag % 2 == 1)
        bag++;
}

void DominoCarre::start() {

    Terrain terrain{height, width};
    bool victory = false;

    int DRAW_WIDTH = 800;
    int DRAW_HEIGHT = 700;
    int controller_start_x = DRAW_WIDTH*0.75;
    int controller_width = DRAW_WIDTH*0.25;
                            int block_width = controller_start_x/terrain.getWidth();
                            int block_height = DRAW_HEIGHT/terrain.getHeight();
    Font font;
    font.loadFromFile("./resources/arial.ttf");

    Texture turn_texture;
    turn_texture.loadFromFile("./resources/turn.jpg");
    Sprite turn_sprite;
    turn_sprite.setTexture(turn_texture);
    turn_sprite.setScale(0.3, 0.3);
    turn_sprite.move(controller_start_x+(controller_width*0.25),300);
    FloatRect turn_bounds = turn_sprite.getGlobalBounds();

    Texture cross_texture;
    cross_texture.loadFromFile("./resources/cross.jpg");
    Sprite cross_sprite;
    cross_sprite.setTexture(cross_texture);
    cross_sprite.setScale(0.4, 0.4);
    cross_sprite.move(controller_start_x+(controller_width*0.25),430);
    FloatRect cross_bounds = cross_sprite.getGlobalBounds();

    Texture retour_texture;
    retour_texture.loadFromFile("./resources/Retour.jpg");
    Sprite retour_sprite;
    retour_sprite.setTexture(retour_texture);
    retour_sprite.setScale(1.5,1.5);
    retour_sprite.move(controller_start_x+(controller_width*0.25),620);
    FloatRect retour_bounds = retour_sprite.getGlobalBounds();


    Tuile *pick = getRandomTuile();
    bag--;
    vector<vector<int>> possible_placements = terrain.getPossiblePlacements(pick);


    Text player_text;
    player_text.setFont(font);
    player_text.setString("Joueur 1");
    player_text.setFillColor(Color::Black);
    player_text.setCharacterSize(30);
    player_text.move(controller_start_x+(controller_width*0.25), 6);

    Text score_text;
    score_text.setFont(font);
    score_text.setFillColor(Color::Black);
    score_text.setString("0 | 0");
    score_text.setCharacterSize(30);
    score_text.move(controller_start_x+(controller_width*0.35), 50);

    Text bag_text;
    bag_text.setFont(font);
    bag_text.setFillColor(Color::Black);
    bag_text.setString("bag size = " + to_string(bag));
    bag_text.setCharacterSize(20);
    bag_text.move(controller_start_x+(controller_width*0.15), 520);

    RenderWindow app(VideoMode(DRAW_WIDTH, DRAW_HEIGHT, 32), "DominoCarre");
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
                        }
                        if (turn_bounds.contains(mouse) || cross_bounds.contains(mouse)) {
                            pick->turn();
                            possible_placements = terrain.getPossiblePlacements(pick);
                        }
                        if (cross_bounds.contains(mouse)) {
                            player = (player+1) %2;
                            player_text.setString("Joueur " + to_string(player+1));
                            if(bag == 0 ) {
                                victory = true;
                            } else {
                                pick = getRandomTuile();
                                bag--;
                                bag_text.setString("bag size = " + to_string(bag));
                            }
                        }
                        if(0 < mouse.x && mouse.x < DRAW_WIDTH-200 && 0 < mouse.y && mouse.y < DRAW_HEIGHT) {

                            int x = mouse.x / block_width;
                            int y = mouse.y / block_height;
                            if(0 <= x && x < terrain.getWidth() && 0 <= y && y < terrain.getHeight()) {
                                if(possible_placements[y][x] == -1)
                                    break;
                                int points = terrain.placeTuile(y,x, pick);
                                if(player == 0)
                                    score1 += points;
                                else
                                    score2 += points;
                                score_text.setString(
                                    to_string(score1) +
                                    " | " +
                                    to_string(score2)
                                );
                                if(bag == 0) {
                                    victory = true;
                                } else {
                                    pick = getRandomTuile();
                                    bag--;
                                    possible_placements = terrain.getPossiblePlacements(pick);
                                    player = (player+1) %2;
                                    player_text.setString("Joueur " + to_string(player+1));
                                    bag_text.setString("bag size = " + to_string(bag));
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
        int pick_start_x = controller_start_x+(controller_width*0.1);
        int pick_end_x = controller_start_x+(controller_width*0.9);
        pick->draw(&app, 
            pick_start_x, 120, 
            pick_end_x-pick_start_x, 
            pick_end_x-pick_start_x
            );
        app.draw(turn_sprite);
        app.draw(cross_sprite);
        app.draw(score_text);
        app.draw(retour_sprite);
        app.draw(bag_text);

        // affichage de l'aide au placement
        for(int y = 0; y < terrain.getHeight() && !victory; y++) {
            for(int x = 0; x < terrain.getWidth(); x++) {
                if(possible_placements[y][x] == -1)
                    continue;
                RectangleShape rect(Vector2f(block_width, block_height));
                rect.move(block_width*x, block_height*y);
                rect.setFillColor(Color(0,0,0,128));
                rect.setOutlineThickness(2);
                rect.setOutlineColor(Color(0,0,0));

                Text text;
                text.setFont(font);
                text.setString(to_string(possible_placements[y][x]));
                text.setCharacterSize(block_height*0.3);
                text.setFillColor(Color::Black);
                text.move(block_width*x+block_width/3, block_height*y+block_height/3);
                app.draw(text);

                app.draw(rect);
            }   
        }

        if(victory) {
            string winner_string = "";
            if(score1 > score2)
                winner_string = "Joueur 1 a gagne!";
            else if(score1 < score2)
                winner_string = "Joueur 2 a gagne!";
            else 
                winner_string = "Egalite!";

            RectangleShape rect(Vector2f(controller_start_x*0.50, DRAW_HEIGHT*0.25));
            rect.move(controller_start_x*0.25, DRAW_HEIGHT*0.40);
            app.draw(rect);

            Text text;
            text.setFont(font);
            text.setString(winner_string);
            text.setCharacterSize(30);
            text.setFillColor(Color::Black);
            text.move(controller_start_x*0.3, DRAW_HEIGHT*0.44);
            app.draw(text);
            app.display();
            sleep(5);
            app.close();
            Main::openMenuPrincipal();
        }

        app.display();
         
    }
}