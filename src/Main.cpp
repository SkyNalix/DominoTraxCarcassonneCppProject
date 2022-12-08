
#include "Main.hpp"

int main() {
    srand(time(NULL));

    while(true) {
        cout << "Selectionez le jeu:\n"
        << "\t  1   : Domino Carrées\n"
        << "\tautre : quitter\n";

        int choice;
        cin >> choice;
        switch(choice) {
            case 1: {
                DominoCarre c{1,1};
                c.start();
                break;
            }
            default: 
                return EXIT_FAILURE;
        }
        cout << "\n\n\n\n" << endl;
    }

    return EXIT_SUCCESS;
}