#include "Tuile.hpp"
// #include "Bord.hpp"
#include "common/Bord.hpp"

Tuile::Tuile(const vector<Bord<vector<int>>> &bords) : bords{bords} {}

vector<Bord<vector<int>>> Tuile::getBords() const {
    return this->bords;
}

Bord<vector<int>> Tuile::getBord(const string& face) const {
    if(face=="nord")
        return bords[0];
    if(face=="est")
        return bords[1];
    if(face=="sud")
        return bords[2];
    if(face=="ouest")
        return bords[3];
    throw invalid_argument("invalid face");
}


vector<vector<int>> pioches_possible{
    {1,1,1},
    {1,1,2}, {2,1,1}, {1,2,1}, {2,2,1}, {1,2,2}, {2,1,2},
    {1,1,3}, {3,1,1}, {1,3,1}, {3,3,1}, {1,3,3}, {3,1,3}
};

Tuile* getRandomTuile() {
    vector<Bord<vector<int>>> bords{};
    for(int i = 0; i < 4; i++) {
        vector<int> list = pioches_possible[rand() % pioches_possible.size()];
        Bord<vector<int>> bord {list};
        bords.push_back(bord);
    }
    return new Tuile{bords};
}


Tuile* getRandomTuileTrax(){
    vector<Bord<vector<int>>> bords{};

    vector<int> blanc = {0,0,0}; 
    vector<int> rouge = {1,1,1}; 

    int random = rand() % 2;
    if(random == 0){ // blanc rouge blanc rouge   
       bords.push_back(blanc);
       bords.push_back(rouge);
       bords.push_back(blanc);
       bords.push_back(rouge);  
       cout << "lÃ " << endl;  
    } else if(random == 1){ // blanc blanc rouge rouge
       bords.push_back(blanc);
       bords.push_back(blanc);
       bords.push_back(rouge);
       bords.push_back(rouge);
       cout << "ici" << endl;    
    }
    return new Tuile{bords};
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

    // le grand carrÃ© du centre
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
            
            Bord<vector<int>> bord = bords[i];
            Font font;
            font.loadFromFile("./resources/arial.ttf");
            Text text;
            text.setFont(font);
            text.setString(to_string(bord.x[j]));
            text.setCharacterSize(domino_height*0.8);
            text.setFillColor(Color::Black);
            if(i==0 || i== 2)
                text.move(domino_start_x +(domino_width/5),domino_start_y);
            else
                text.move(domino_start_x +(domino_width/3),domino_start_y);
            app->draw(text);
        }
    }

}


void Tuile::drawTrax(RenderWindow *app, int start_x, int start_y, int ZONE_WIDTH, int ZONE_HEIGHT ,Sprite sprite){
    Texture texture; texture.loadFromFile("./resources/TraxBlancBlancRougeRouge.png");
    sprite.setTexture(texture);
    sprite.setScale(0.05,0.05);
    sprite.move(ZONE_WIDTH,ZONE_HEIGHT);
    app->draw(sprite);
    app->display();
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
    vector<int> tmp = bords[3].x;
    bords[3].x = bords[2].x;
    bords[2].x = invert_vector(bords[1].x);
    bords[1].x = bords[0].x;
    bords[0].x = invert_vector(tmp);
}