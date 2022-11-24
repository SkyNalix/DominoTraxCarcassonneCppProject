#include "Tuile.hpp"
#include "BordDomino.hpp"

Tuile::Tuile(const vector<BordDomino *> &bords) : bords{bords} {}

vector<BordDomino *> Tuile::getBords() const {
    return this->bords;
}


string Tuile::getId() const {
    return this->id;
}

BordDomino *Tuile::getBord(const string& face) const {
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

string afficherTuile(const Tuile &t) {
    string str = "Tuile :" + t.getId();
    vector<BordDomino *> bords = t.getBords();
    for (size_t i = 0; i < bords.size(); i++) {
        str += " bords : " + std::to_string(i);
    }
    return str;
}

ostream &operator<<(ostream &out, const Tuile &t) {
    out << "Tuile : " + t.getId();
    for (size_t i = 0; i < t.getBords().size(); i++) {
        BordDomino bord = *((BordDomino *) t.getBords()[i]);
        if(bord.face == "vide")
            out << "BordDomino(vide)";
        else
            out << "BordDomino(" << bord.face << ") : " << bord ;
        if(i < t.getBords().size()-1)
            out << "; ";
    }
    return out;
}

vector<vector<int>> pioches_possible{
    {1,1,1}, {1,1,1},
    {1,1,2}, {2,1,1},
    // {1,2,1},
    // {1,1,3}, {3,1,1},
    // {1,3,1},
    // {2,1,3}, {3,1,2},
    // {1,2,3}, {3,2,1},  
    // {0,2,3}, {3,2,0}, 
    // {1,1,2}, {2,1,1},   
    // {3,0,0}, {0,0,3},
    
};

Tuile* piocherTuileDomino() {
    srand((unsigned) time(NULL));
    BordDomino *n = new BordDomino {"nord", pioches_possible[rand() % (pioches_possible.size())]};
    BordDomino *e = new BordDomino {"est", pioches_possible[rand() % (pioches_possible.size())]};
    BordDomino *s = new BordDomino {"sud", pioches_possible[rand() % (pioches_possible.size())]};
    BordDomino *o = new BordDomino {"ouest", pioches_possible[rand() % (pioches_possible.size())]};
    return new Tuile{vector<BordDomino *> {n,e,s,o} };
}


void Tuile::draw(RenderWindow *app, int start_x, int start_y, int ZONE_WIDTH, int ZONE_HEIGHT ) {

    RectangleShape rectangle(Vector2f(ZONE_WIDTH, ZONE_HEIGHT));
    rectangle.move(start_x, start_y);
    rectangle.setOutlineThickness(-2);
    rectangle.setOutlineColor(Color::Black);
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
            

            BordDomino bord = *((BordDomino *) bords[i]);
            Font font;
            font.loadFromFile("./resources/arial.ttf");
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

vector<int> invert_vector(vector<int> v) {
    vector<int> res{};
    for(size_t i = v.size()-1;;i--) {
        res.push_back(v[i]);
        if(i==0)
        break;
    }
    return res;
} 

void Tuile::turn() {
    vector<int> tmp = bords[3]->getValeurs();
    bords[3]->setValeurs(bords[2]->getValeurs());
    bords[2]->setValeurs(invert_vector(bords[1]->getValeurs()));
    bords[1]->setValeurs(bords[0]->getValeurs());
    bords[0]->setValeurs(invert_vector(tmp));;
}