#include "main.hpp"

int main() {

    BordDomino *w = new BordDomino{"nord", 1, 2, 3};
    BordDomino *x = new BordDomino{"est", 2, 3, 4};
    BordDomino *y = new BordDomino{"sud", 3, 4, 1};
    BordDomino *z = new BordDomino{"ouest", 4, 1, 2};
    Tuile tuileA = Tuile{vector <Bord *>{w,x,y,z}};
    cout << "tuileA: " << tuileA << endl;

    w = new BordDomino{"nord", 1,4,1};
    x = new BordDomino{"est", 4,1,2};
    y = new BordDomino{"sud", 1,2,3};
    z = new BordDomino{"ouest", 2, 3, 4};
    Tuile tuileB = Tuile{vector <Bord *>{w,x,y,z}};
    cout << "tuileB: " << tuileA << endl;



    Terrain terrain{4,4};

    int b = terrain.placeTuile(0,0, &tuileA);
    cout << b << endl;

    b = terrain.placeTuile(0,1, &tuileB);
    cout << b << endl;

    Tuile *A = terrain.getTuile(0, 0);
    if(A==nullptr)
        cout << "tuile(0,0) = null" << endl;
    else
        cout << "tuile(0,0) = " << *A << endl;
    A = terrain.getTuile(0, 1);
    if(A==nullptr)
        cout << "tuile(0,1) = null" << endl;
    else
        cout << "tuile(0,1) = " << *A << endl;



//    placerDomino(1,1,tuileA,terrain);
//    cout << terrain[1][1] << endl;

    cout << "Fin Programme" << endl;
    return EXIT_SUCCESS;
}