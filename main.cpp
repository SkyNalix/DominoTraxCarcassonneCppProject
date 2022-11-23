#include "main.hpp"

int main() {
    Tuile tuileA{ vector <Bord *>{
        new BordDomino{"nord", 1, 2, 3},
        new BordDomino{"est", 2, 3, 4},
        new BordDomino{"sud", 3, 4, 1},
        new BordDomino{"ouest", 4, 1, 2}
    }};
    Tuile tuileB{vector <Bord *>{
        new BordDomino{"nord", 1,4,1},
        new BordDomino{"est", 4,1,2},
        new BordDomino{"sud", 1,2,3},
        new BordDomino{"ouest", 2, 3, 4}
    }};

    Terrain terrain{4,4};
    terrain.placeTuile(0,0, &tuileA);
    terrain.placeTuile(0,1, &tuileB);




    int WIDTH = 800;
    int HEIGHT = 600;

    RectangleShape rectangle(Vector2f(120, 50));
    rectangle.move(100,100);
    rectangle.setFillColor(Color(0,0,0));

    RenderWindow app(VideoMode(WIDTH, HEIGHT, 32), "Test ");
    while (app.isOpen()){
        Event event;
        while (app.pollEvent(event)){
            switch (event.type) {
                case Event::Closed:
                    app.close(); break;
                default: break;
            }}
        app.clear(); // Remplissage en noir
        app.draw(RectangleShape(Vector2f(WIDTH, HEIGHT)));

        terrain.draw(&app, WIDTH-200, HEIGHT);

        RectangleShape line(Vector2f(5, HEIGHT));
        line.move(WIDTH-200, 0);
        line.setFillColor(Color(0,0,0));
        app.draw(line);

        app.display(); // Affichage effectif
    } // fermeture de la fenêtre

    cout << "Fin Programme" << endl;
    return EXIT_SUCCESS;
}