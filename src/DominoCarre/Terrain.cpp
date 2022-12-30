#include "Terrain.hpp"

Terrain::Terrain(int height, int width) : height{height}, width{width} {
    vector <vector<Tuile *>> plateau;
    for (int i = 0; i < height; i++) {
        vector < Tuile *> tmp{};
        for (int j = 0; j < width; j++) {
            tmp.push_back(nullptr);
        }
        plateau.push_back(tmp);
    }
    terrain = plateau;
}

Tuile * Terrain::getTuile(int y, int x) const {
    if( 0<= y && y < height && 0 <= x && x < width) {
        return getTerrain()[y][x];
    }
    return nullptr;
}

vector<vector<Tuile *>> Terrain::getTerrain() const {
    return terrain;
}

int Terrain::getHeight() const {
    return height;
}

int Terrain::getWidth() const {
    return width;
}




bool checkBordsValues(Bord<vector<int>> bord1, Bord<vector<int>> bord2) {
    vector<int> bord1_val = bord1.x;
    vector<int> bord2_val = bord2.x;
    if(bord1_val.size() != bord2_val.size())
        return false;
    for(size_t i = 0; i < bord2_val.size(); i++){
        if (bord1_val[i] != bord2_val[i]) {
            return false;
        }
    }
    return true;
}

int calculPoints(Bord<vector<int>> bord1, Bord<vector<int>> bord2) {
    vector<int> bord1_val = bord1.x;
    vector<int> bord2_val = bord2.x;
    int points = 0;
    for(size_t i = 0; i < bord2_val.size(); i++){
        points += bord1_val[i];
    }
    return points;
}

bool Terrain::isEmpty() {
    for(int y = 0 ; y < height; y++ ) {
        for(int x= 0; x < width; x++) {
            if(getTuile(y,x) != nullptr) {
                return false;
            }
        }
    }
    return true;
}

// return -1 si le placement a echouÃ©, les points gagnÃ©s sinon
int Terrain::tryPlaceTuile(int y, int x, Tuile *tuile) {
    int points = 0;
    if( x < 0 || width <= x || y < 0 || height <= y || getTuile(y, x) != nullptr ) 
        return -1;

    if(getTuile(y, x+1) == nullptr 
    && getTuile(y, x-1) == nullptr 
    && getTuile(y+1, x) == nullptr 
    && getTuile(y-1, x) == nullptr 
    && !isEmpty() ) {
        return -1;
    }

    if( getTuile(y, x+1) != nullptr) {
        Bord<vector<int>> bord1 = tuile->getBord("est");
        Bord<vector<int>> bord2 = getTuile(y,x+1)->getBord("ouest");
        if (!checkBordsValues(bord1,bord2))
            return -1;
        points += calculPoints(bord1, bord2);
    }
    if( getTuile(y, x-1) != nullptr) {
        Bord<vector<int>> bord1 = tuile->getBord("ouest");
        Bord<vector<int>> bord2 = getTuile(y,x-1)->getBord("est");
        if (!checkBordsValues(bord1,bord2))
            return -1;
        points += calculPoints(bord1, bord2);
    }
    if( getTuile(y-1, x) != nullptr) {
        Bord<vector<int>> bord1 = tuile->getBord("nord");
        Bord<vector<int>> bord2 = getTuile(y-1,x)->getBord("sud");
        if (!checkBordsValues(bord1,bord2))
            return -1;
        points += calculPoints(bord1, bord2);
    }
    if( getTuile(y+1, x) != nullptr) {
        Bord<vector<int>> bord1 = tuile->getBord("sud");
        Bord<vector<int>> bord2 = getTuile(y+1,x)->getBord("nord");
        if (!checkBordsValues(bord1,bord2))
            return -1;
        points += calculPoints(bord1, bord2);
    }
    return points;
}

int Terrain::placeTuile(int y, int x, Tuile* tuile) {
    int n = tryPlaceTuile(y, x, tuile);
    if(n == -1)
        return -1;
    terrain[y][x] = tuile;
    return n;
}

void Terrain::draw(RenderWindow *app, int ZONE_WIDTH, int ZONE_HEIGHT) {
    int block_width = ZONE_WIDTH/width;
    int block_height = ZONE_HEIGHT/height;
    for( int y = 0; y < height; y++) {
        for( int x = 0; x < width; x++) {
            RectangleShape rectangle(Vector2f(block_width, block_height));
            rectangle.move(block_width*x, block_height*y );
            Tuile * tuile = getTuile(y,x);
            if( tuile != nullptr) {
                tuile->draw(app, block_width*x, block_height*y, block_width, block_height);
            } else
            app->draw(rectangle);
        }
    }
}


bool Terrain::propage(int x,int y){ 
    Tuile *actuel = this->getTuile(y,x);
    bool check = false;

    for(int i = 0; i < this->getHeight();i++){
        if(this->getTuile(i,0) != nullptr){
            check = allerDroite(this,i,0);
        }
    }
    return check;
}


bool allerDroite(Terrain *terrain,int x,int y){
    Tuile *tuile = terrain->getTuile(y,x);
    bool check = false;

    if(y == terrain->getHeight()){return true;} // si on arrive au dernier alors tout se suit
    if(tuile->getBord("est").x[0] == 0 && terrain->getTuile(y,x+1)->getBord("ouest").x[0] == 0 ){ // chemin vers la droite
        check = allerDroite(terrain,x+1,y);
        return check;  
    } else if(tuile->getBord("nord").x[0] == 0 && terrain->getTuile(y,x+1)->getBord("sud").x[0] == 0 ){ // on va vers le haut
        check = allerHaut(terrain,x,y-1);
        return check;  
    }  else if(tuile->getBord("sud").x[0] == 0 && terrain->getTuile(y,x+1)->getBord("nord").x[0] == 0 ){
       check = allerBas(terrain,x,y+1);   
       return check;
    }

    return false;
}

bool allerGauche(Terrain *terrain,int x,int y){
    Tuile *tuile = terrain->getTuile(y,x);
    bool check = false;

    if(y == 0 ){return true;} // si on arrive au dernier alors tout se suit
    if(tuile->getBord("ouest").x[0] == 0 && terrain->getTuile(y,x+1)->getBord("est").x[0] == 0 ){ // chemin vers la droite
        check = allerGauche(terrain,x-1,y);
        return check;  
    } else if(tuile->getBord("nord").x[0] == 0 && terrain->getTuile(y,x+1)->getBord("sud").x[0] == 0 ){ // on va vers le haut
        check = allerHaut(terrain,x,y-1);
        return check;  
    }  else if(tuile->getBord("sud").x[0] == 0 && terrain->getTuile(y,x+1)->getBord("nord").x[0] == 0 ){
       check = allerBas(terrain,x,y+1);  
       return check;
    }
    return false;
}

bool allerBas(Terrain *terrain,int x,int y){ // x = ligne y = colonne ? 
    Tuile *tuile = terrain->getTuile(y,x);
    bool check = false;

    if(y == terrain->getWidth()){return true;} // si on arrive au dernier alors tout se suit
    if(tuile->getBord("ouest").x[0] == 0 && terrain->getTuile(y,x+1)->getBord("est").x[0] == 0 ){ // chemin vers la droite
        check = allerGauche(terrain,x-1,y);
        return check;  
    } else if(tuile->getBord("est").x[0] == 0 && terrain->getTuile(y,x+1)->getBord("ouest").x[0] == 0 ){ // on va vers le haut
        check = allerDroite(terrain,x+1,y);
        return check;  
    } else if(tuile->getBord("sud").x[0] == 0 && terrain->getTuile(y,x+1)->getBord("nord").x[0] == 0 ){
       check = allerBas(terrain,x,y+1);   
        return check;
    }
    return false;
}


bool allerHaut(Terrain *terrain,int x,int y){
    Tuile *tuile = terrain->getTuile(y,x);
    bool check = false;

    if(y == 0){return true;} // si on arrive au dernier alors tout se suit
    if(tuile->getBord("ouest").x[0] == 0 && terrain->getTuile(y,x+1)->getBord("est").x[0] == 0 ){ // chemin vers la droite
        check = allerGauche(terrain,x-1,y);
        return check;  
    } else if(tuile->getBord("est").x[0] == 0 && terrain->getTuile(y,x+1)->getBord("ouest").x[0] == 0 ){ // on va vers le haut
        check = allerDroite(terrain,x+1,y);
        return check;  
    } else if(tuile->getBord("nord").x[0] == 0 && terrain->getTuile(y,x+1)->getBord("sud").x[0] == 0 ){
       check = allerHaut(terrain,x,y-1);   
        return check;
    }
    return false;
}



void Terrain::drawTrax(RenderWindow *app, int ZONE_WIDTH, int ZONE_HEIGHT,Sprite sprite){
    int block_width = ZONE_WIDTH/width;
    int block_height = ZONE_HEIGHT/height;
    for( int y = 0; y < height; y++) {
        for( int x = 0; x < width; x++) {
            Tuile * tuile = getTuile(y,x);

            
            if( tuile != nullptr) {
                    tuile->drawTrax(app, block_width*x, block_height*y, block_width, block_height,sprite);
            } else { tuile->drawTrax(app, block_width*x, block_height*y, block_width, block_height,sprite); }
        }
    }
} 


 vector<vector<int>> Terrain::getPossiblePlacements(Tuile *tuile) {
    vector<vector<int>> res{};
    for(int i = 0 ; i < getHeight(); i++) {
        vector<int> list{};
        for(int j = 0; j < getWidth(); j++) {
            list.push_back(tryPlaceTuile(i, j, tuile));
        }
        res.push_back(list);
    }
    return res;
 }