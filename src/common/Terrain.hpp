#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <iostream>
#include "Bord.hpp"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

template <typename T> class Terrain {
    private:
        int height;
        int width;
    public:
        vector<vector<T *>> terrain;
        Terrain(int height, int width);
        T * getTuile(int y, int x) const;
        int getHeight() const;
        int getWidth() const;
        bool isEmpty();
        void draw(RenderWindow *app, int WIDTH, int HEIGHT);

        bool propage(int x,int y); 
};

template <typename T> 
Terrain<T>::Terrain(int height, int width) : height{height}, width{width} {
    vector <vector<T *>> plateau;
    for (int i = 0; i < height; i++) {
        vector < T *> tmp{};
        for (int j = 0; j < width; j++) {
            tmp.push_back(nullptr);
        }
        plateau.push_back(tmp);
    }
    terrain = plateau;
}


template <typename T>
T * Terrain<T>::getTuile(int y, int x) const {
    if( 0<= y && y < height && 0 <= x && x < width) {
        return terrain[y][x];
    }
    return nullptr;
}

template <typename T>
int Terrain<T>::getHeight() const {
    return height;
}

template <typename T>
int Terrain<T>::getWidth() const {
    return width;
}


template <typename T>
bool Terrain<T>::isEmpty() {
    for(int y = 0 ; y < height; y++ ) {
        for(int x= 0; x < width; x++) {
            if(getTuile(y,x) != nullptr) {
                return false;
            }
        }
    }
    return true;
}


template <typename T>
void Terrain<T>::draw(RenderWindow *app, int ZONE_WIDTH, int ZONE_HEIGHT) {
    int block_width = ZONE_WIDTH/width;
    int block_height = ZONE_HEIGHT/height;
    for( int y = 0; y < height; y++) {
        for( int x = 0; x < width; x++) {
            RectangleShape rectangle(Vector2f(block_width, block_height));
            rectangle.move(block_width*x, block_height*y );
            T * tuile = getTuile(y,x);
            if( tuile != nullptr) {
                tuile->draw(app, block_width*x, block_height*y, block_width, block_height);
            } 
            // else
            //     app->draw(rectangle);
        }
    }
}



template <typename T>
bool Terrain<T>::propage(int x,int y){ 
    T *actuel = this->getTuile(y,x);
    bool check = false;

    for(int i = 0; i < this->getHeight();i++){
        if(this->getTuile(i,0) != nullptr){
            // check = allerDroite(this,i,0);
        }
    }
    return check;
}


#endif //TERRAIN_HPP

