
#include "Main.hpp"




void openMenuPrincipal(){

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
                            DominoCarre c{5,5};
                            c.start();
                        }else if(trax_bounds.contains(mouse)){
                            app.close();
                            Trax c{1};
                            c.start();
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
    srand(time(NULL));
    
    openMenuPrincipal();
    return EXIT_SUCCESS;
}



