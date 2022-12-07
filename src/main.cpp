#include "main.hpp"

int main() {
    srand(time(NULL));

    while(true) {
        cout << "Selectionez le jeu:\n"
        << "\t1 : Domino Carrées\n"
        << "\tautre : quitter\n";

        int choice;
        cin >> choice;
        switch(choice) {
            case 0 : 
                return EXIT_SUCCESS;
            case 1: 
                DominoCarre c{1,1};
                c.start();
                break;
        }
        cout << "\n\n\n\n" << endl;
    }

    return EXIT_SUCCESS;
}