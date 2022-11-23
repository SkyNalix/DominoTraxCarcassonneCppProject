//tuile composé de vector<Bord>
#include "Tuile.hpp"
#include "BordDomino.hpp"

Tuile::Tuile(vector<Bord *> b) : bords{b} {}

vector<Bord *> Tuile::getBords() {
    return this->bords;
}


string Tuile::getId() {
    return this->id;
}

Bord *Tuile::getBord(const string& face) {
    if(face=="nord")
        return bords[0];
    if(face=="est")
        return bords[1];
    if(face=="sud")
        return bords[2];
    if(face=="ouest")
        return bords[3];
    return nullptr;
}

string afficherTuile(Tuile t) {
    string str = "Tuile :" + t.getId();
    vector<Bord *> bords = t.getBords();
    for (size_t i = 0; i < bords.size(); i++) {
        str += " bords : " + std::to_string(i);
    }
    return str;
}

ostream &operator<<(ostream &out, Tuile t) {
    out << "Tuile : " + t.getId();
    for (size_t i = 0; i < t.getBords().size(); i++) {
        BordDomino bord = *((BordDomino *) t.getBords()[i]);
        if(bord.face == "vide")
            out << "Bord(vide)";
        else
            out << "Bord(" << bord.face << ") : " << bord ;
        if(i < t.getBords().size()-1)
            out << "; ";
    }
    return out;
}

int piocherTuileDomino(vector <Tuile> pioche) {
    srand((unsigned) time(NULL));
    return rand() % (pioche.size());
}


void Tuile::draw(RenderWindow *app, int start_x, int start_y, int ZONE_WIDTH, int ZONE_HEIGHT ) {

    RectangleShape rectangle(Vector2f(ZONE_WIDTH, ZONE_HEIGHT));
    rectangle.move(start_x, start_y);
    rectangle.setOutlineThickness(-2);
    rectangle.setOutlineColor(Color::Black);
    // Color color(255,0,0);
    // rectangle.setFillColor(color);
    app->draw(rectangle);


    double square_width = ZONE_WIDTH/4;
    double square_height = ZONE_HEIGHT/4;
    for(int i = 0; i < 4; i++) {
        int x = start_x;
        int y = start_y;
        if(i==1 || i==3) x += ZONE_WIDTH - square_width;
        if(i==2 || i== 3) y += ZONE_HEIGHT - square_height;
        RectangleShape rectangle2(Vector2f(square_width, square_height));
        rectangle2.move(x, y);
        Color color2(68, 75, 78);
        rectangle2.setFillColor(color2);
        app->draw(rectangle2);
    }

    // le grand carré du centre
    RectangleShape square(Vector2f(square_width*2, square_height*2));
    square.move(start_x+square_width, start_y+square_height);
    square.setOutlineThickness(2);
    square.setOutlineColor(Color::Black);
    square.setFillColor(Color::Black);
    app->draw(square);
    
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 3; j++) {
            double domino_width = -1;
            double domino_height = -1;
            if(i==0 || i==2) {
                domino_width = (square_width*2)/3;
                domino_height = square_height;
            } else {
                domino_width = square_width;
                domino_height = (square_height*2)/3;
            }

            double domino_start_x = start_x;
            double domino_start_y = start_y;
            if(i==0) {
                domino_start_x += square_width + (j*domino_width);
            } else if(i==1) {
                domino_start_x += 3*square_width;
                domino_start_y += square_height + (j*domino_height);
            } else if(i==2) {
                domino_start_x += square_width + (j*domino_width); 
                domino_start_y += 3*square_height;
            } else {
                domino_start_y += square_height + (j*domino_height);
            }
            // domino_start_x += (domino_width/3);
            
            

            BordDomino bord = *((BordDomino *) bords[i]);
            Font font;
            font.loadFromFile("arial.ttf");
            Text text;
            text.setFont(font);
            text.setString(to_string(bord.getValeurs()[j]));
            text.setCharacterSize(domino_height*0.8);
            text.setFillColor(Color::Black);
            if(i==0 || i== 2)
                text.move(domino_start_x +(domino_width/5),domino_start_y);
            else
                text.move(domino_start_x +(domino_width/3),domino_start_y);


            if( j < 2 ) {
                RectangleShape line;
                if(i==0 || i==2) {
                    line = RectangleShape(Vector2f(1, domino_height));
                    line.move(domino_start_x+domino_width, domino_start_y);
                } else {
                    line = RectangleShape(Vector2f(domino_width, 1));
                    line.move(domino_start_x, domino_start_y+domino_height);
                }
                line.setFillColor(Color::Black);
                app->draw(line);
            }
        
            app->draw(text);
        }
    }





}
