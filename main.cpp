#include "main.hpp"

void openMenuPrincipal();

void openDomino(){
    
    
    Terrain terrain{8,8};

    int WIDTH = 800;
    int HEIGHT = 600;
    Font font;
    font.loadFromFile("./resources/arial.ttf");

    Texture turn_texture;
    turn_texture.loadFromFile("./resources/turn.jpg");
    Sprite turn_sprite;
    turn_sprite.setTexture(turn_texture);
    turn_sprite.move(WIDTH-150,230);
    turn_sprite.setScale(0.3, 0.3);
    FloatRect turn_bounds = turn_sprite.getGlobalBounds();

    Texture cross_texture;
    cross_texture.loadFromFile("./resources/cross.jpg");
    Sprite cross_sprite;
    cross_sprite.setTexture(cross_texture);
    cross_sprite.move(WIDTH-150,340);
    cross_sprite.setScale(0.4, 0.4);
    FloatRect cross_bounds = cross_sprite.getGlobalBounds();

    Texture retour_texture;
    retour_texture.loadFromFile("./resources/Retour.jpg");
    Sprite retour_sprite;
    retour_sprite.setTexture(retour_texture);
    retour_sprite.move(WIDTH-150,460);
    retour_sprite.setScale(1.5,1.5);
    FloatRect retour_bounds = retour_sprite.getGlobalBounds();


    Tuile *pioche = piocherTuileDomino();
    vector<vector<int>> possible_placements = terrain.getPossiblePlacements(pioche);


    Text player_text;
    player_text.setFont(font);
    player_text.setString("Joueur 1");
    player_text.setFillColor(Color::Black);
    player_text.move(WIDTH-150, 6);
    player_text.setCharacterSize(30);


    int joueur = 0; // ou 1

    RenderWindow app(VideoMode(WIDTH, HEIGHT, 32), "Test ");
    while (app.isOpen()){
        Event event;
        while (app.pollEvent(event)){
            switch (event.type) {
                case Event::Closed:
                    app.close(); break;
                case Event::MouseButtonPressed: {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        Vector2f mouse = app.mapPixelToCoords(Mouse::getPosition(app));
                        if(retour_bounds.contains(mouse)){
                            app.close();
                            openMenuPrincipal();
                        }
                        if (turn_bounds.contains(mouse) || cross_bounds.contains(mouse)) {
                            pioche = piocherTuileDomino();
                            possible_placements = terrain.getPossiblePlacements(pioche);
                        }
                        if (cross_bounds.contains(mouse)) {
                            joueur = (joueur+1) %2;
                            player_text.setString("Joueur " + to_string(joueur+1));
                        }
                        if(0 < mouse.x && mouse.x < WIDTH-200 && 0 < mouse.y && mouse.y < HEIGHT) {
                            int block_width = (WIDTH-200)/terrain.getWidth();
                            int block_height = HEIGHT/terrain.getHeight();
                            int x = mouse.x / block_width;
                            int y = mouse.y / block_height;
                            if(0 <= x && x < terrain.getWidth() && 0 <= y && y < terrain.getHeight()) {
                                if(possible_placements[y][x] == -1)
                                    break;
                                terrain.placeTuile(y,x, pioche);
                                pioche = piocherTuileDomino();
                                possible_placements = terrain.getPossiblePlacements(pioche);
                                joueur = (joueur+1) %2;
                                player_text.setString("Joueur " + to_string(joueur+1));
                            }
                        } 
                    }
                    break;
                }
                default: break;
            }
        }

        app.clear();
        app.draw(RectangleShape(Vector2f(WIDTH, HEIGHT)));

        // affichage du terrain de jeu
        terrain.draw(&app, WIDTH-200, HEIGHT);

        RectangleShape line(Vector2f(5, HEIGHT));
        line.move(WIDTH-200, 0);
        line.setFillColor(Color(0,0,0));
        app.draw(line);

        Vector2f mouse = app.mapPixelToCoords(Mouse::getPosition(app));
        if(0 < mouse.x && mouse.x < WIDTH-200 && 0 < mouse.y && mouse.y < HEIGHT) {
            int block_width = (WIDTH-200)/terrain.getWidth();
            int block_height = HEIGHT/terrain.getHeight();
            int x = mouse.x / block_width;
            int y = mouse.y / block_height;
            
            if(0 <= x && x < terrain.getWidth() && 0 <= y && y < terrain.getHeight() 
                    && terrain.getTuile(y,x) == nullptr) {
                RectangleShape rect(Vector2f(block_width, block_width));
                rect.move(block_width*x, block_height*y);
                if(possible_placements[y][x] == -1)
                    rect.setFillColor(Color(255,0,0,128));
                else {
                    rect.setFillColor(Color(0,0,0,128));
                    Text text;
                    text.setFont(font);
                    text.setString(to_string(possible_placements[y][x]));
                    text.setCharacterSize(block_height*0.3);
                    text.setFillColor(Color::Black);
                    text.move(block_width*x+block_width/3, block_height*y+block_height/3);
                    app.draw(text);
                }
                app.draw(rect);
            }
        }

        // affichage des controlles
        app.draw(player_text);
        pioche->draw(&app, WIDTH-180, 60, (WIDTH-20)-(WIDTH-180), (WIDTH-20)-(WIDTH-180));
        app.draw(turn_sprite);
        app.draw(cross_sprite);
        app.draw(retour_sprite);

        app.display(); 
    }

    cout << "Fin Programme" << endl;
}



void openMenuPrincipal(){
    int WIDTH = 800;
    int HEIGHT = 600;

    Font font;
    font.loadFromFile("./resources/arial.ttf");
    Text text;
    text.setFont(font);
    text.setString(" Menu ");
    text.setCharacterSize(50);
    text.setFillColor(Color::Red);


    Texture texture;
    texture.loadFromFile("./resources/Domino.jpg");
    Sprite menuDomino;
    menuDomino.setTexture(texture);
    menuDomino.setScale(Vector2f(2.5,2.5));
    menuDomino.move(Vector2f(25, 125));
    FloatRect domino_bounds = menuDomino.getGlobalBounds(); 

    Texture texture2;
    texture2.loadFromFile("./resources/Trax.jpg");
    Sprite menuTrax;
    menuTrax.setTexture(texture2);
    menuTrax.setScale(Vector2f(2.5,2.5));
    menuTrax.move(Vector2f(25, 325));
    FloatRect trax_bounds = menuTrax.getGlobalBounds(); 


    RenderWindow app(VideoMode(800, 600, 32), "Projet 2022 CPP ");
    while (app.isOpen()){
        Event event;
        while (app.pollEvent(event)){
            switch (event.type) {
                case Event::Closed:
                app.close(); break;
                default: break;
                case Event::MouseButtonPressed: {
                if (event.mouseButton.button == sf::Mouse::Left) {
                        Vector2f mouse = app.mapPixelToCoords(Mouse::getPosition(app));
                        if (domino_bounds.contains(mouse)) {
                            app.close();
                            openDomino();
                        }
                    }
                }
        }}
        app.clear(); 
        app.draw(text);
        app.draw(menuDomino);
        app.draw(menuTrax);
        app.display(); 
    } 
}


int main() {
    openMenuPrincipal();
    return EXIT_SUCCESS;
}