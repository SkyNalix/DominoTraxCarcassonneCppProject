#include "main.hpp"

int main() {
    srand(time(NULL));

    while(true) {
    cout << "Selectionez le jeu:\n"
    << "\t0 : quitter\n"
    << "\t1 : Domino Carrées\n";;

    int choice;
        cin >> choice;
        switch(choice) {
            case 0 : 
                return EXIT_SUCCESS; break;
            case 1: {
                DominoCarre c{1,1};
                c.start();
            }
        }
        cout << "\n\n\n\n" << endl;
    }

    return EXIT_SUCCESS;
}