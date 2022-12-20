#include "Terrain.hpp"






// bool allerDroite(Terrain *terrain,int x,int y){
//     Tuile *tuile = terrain->getTuile(y,x);
//     bool check = false;

//     if(y == terrain->getHeight()){return true;} // si on arrive au dernier alors tout se suit
//     if(tuile->getBord("est").x[0] == 0 && terrain->getTuile(y,x+1)->getBord("ouest").x[0] == 0 ){ // chemin vers la droite
//         check = allerDroite(terrain,x+1,y);
//         return check;  
//     } else if(tuile->getBord("nord").x[0] == 0 && terrain->getTuile(y,x+1)->getBord("sud").x[0] == 0 ){ // on va vers le haut
//         check = allerHaut(terrain,x,y-1);
//         return check;  
//     }  else if(tuile->getBord("sud").x[0] == 0 && terrain->getTuile(y,x+1)->getBord("nord").x[0] == 0 ){
//        check = allerBas(terrain,x,y+1);   
//        return check;
//     }

//     return false;
// }

// bool allerGauche(Terrain *terrain,int x,int y){
//     Tuile *tuile = terrain->getTuile(y,x);
//     bool check = false;

//     if(y == 0 ){return true;} // si on arrive au dernier alors tout se suit
//     if(tuile->getBord("ouest").x[0] == 0 && terrain->getTuile(y,x+1)->getBord("est").x[0] == 0 ){ // chemin vers la droite
//         check = allerGauche(terrain,x-1,y);
//         return check;  
//     } else if(tuile->getBord("nord").x[0] == 0 && terrain->getTuile(y,x+1)->getBord("sud").x[0] == 0 ){ // on va vers le haut
//         check = allerHaut(terrain,x,y-1);
//         return check;  
//     }  else if(tuile->getBord("sud").x[0] == 0 && terrain->getTuile(y,x+1)->getBord("nord").x[0] == 0 ){
//        check = allerBas(terrain,x,y+1);  
//        return check;
//     }
//     return false;
// }

// bool allerBas(Terrain *terrain,int x,int y){ // x = ligne y = colonne ? 
//     Tuile *tuile = terrain->getTuile(y,x);
//     bool check = false;

//     if(y == terrain->getWidth()){return true;} // si on arrive au dernier alors tout se suit
//     if(tuile->getBord("ouest").x[0] == 0 && terrain->getTuile(y,x+1)->getBord("est").x[0] == 0 ){ // chemin vers la droite
//         check = allerGauche(terrain,x-1,y);
//         return check;  
//     } else if(tuile->getBord("est").x[0] == 0 && terrain->getTuile(y,x+1)->getBord("ouest").x[0] == 0 ){ // on va vers le haut
//         check = allerDroite(terrain,x+1,y);
//         return check;  
//     } else if(tuile->getBord("sud").x[0] == 0 && terrain->getTuile(y,x+1)->getBord("nord").x[0] == 0 ){
//        check = allerBas(terrain,x,y+1);   
//         return check;
//     }
//     return false;
// }


// bool allerHaut(Terrain *terrain,int x,int y){
//     Tuile *tuile = terrain->getTuile(y,x);
//     bool check = false;

//     if(y == 0){return true;} // si on arrive au dernier alors tout se suit
//     if(tuile->getBord("ouest").x[0] == 0 && terrain->getTuile(y,x+1)->getBord("est").x[0] == 0 ){ // chemin vers la droite
//         check = allerGauche(terrain,x-1,y);
//         return check;  
//     } else if(tuile->getBord("est").x[0] == 0 && terrain->getTuile(y,x+1)->getBord("ouest").x[0] == 0 ){ // on va vers le haut
//         check = allerDroite(terrain,x+1,y);
//         return check;  
//     } else if(tuile->getBord("nord").x[0] == 0 && terrain->getTuile(y,x+1)->getBord("sud").x[0] == 0 ){
//        check = allerHaut(terrain,x,y-1);   
//         return check;
//     }
//     return false;
// }

