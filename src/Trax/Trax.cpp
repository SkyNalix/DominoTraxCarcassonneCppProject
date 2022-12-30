#include "Trax.hpp"

Trax::Trax(int p): player{p} {}


string updateTuile(string tuile){
        cout << "Tuile :" << tuile << endl;
    if(tuile.compare("./resources/TraxBlancBlancRougeRouge.png") == 0){
        cout << "blanc blanc rouge rouge -> rouge blanc blanc rouge" << endl;
        return "./resources/TraxRougeBlancBlancRouge.png";
    }else if(tuile.compare("./resources/TraxRougeBlancBlancRouge.png") == 0){
        cout << "rouge blanc blanc rouge -> rouge rouge blanc blanc" << endl;
        return "./resources/TraxRougeRougeBlancBlanc.png";
    }else if(tuile.compare("./resources/TraxRougeRougeBlancBlanc.png") == 0){
        cout << "rouge rouge blanc blanc -> blanc rouge rouge blanc" << endl;
        return "./resources/TraxBlancRougeRougeBlanc.png";
    }else if(tuile.compare("./resources/TraxBlancRougeRougeBlanc.png") == 0){
        cout << "rouge rouge blanc blanc -> blanc blanc rouge rouge" << endl;
        return "./resources/TraxBlancBlancRougeRouge.png";
    }else if(tuile.compare("./resources/TraxBlancRougeBlancRouge.png") == 0){
        return "./resources/TraxRougeBlancRougeBlanc.png";
    }else if (tuile.compare("./resources/TraxRougeBlancRougeBlanc.png") == 0){
        cout << "Rouge Blanc Rouge Blanc -> Blanc Rouge Blanc Rouge" << endl;
        return "./resources/TraxBlancRougeBlancRouge.png";
    }
    return tuile;
}

// return false si le placement a echoué, true sinon
bool Trax::tryPlaceTuile(int y, int x, TuileTrax *tuile) {
    if( x < 0 || width <= x || y < 0 || height <= y || terrain.getTuile(y, x) != nullptr ) 
        return false;
    
    if(terrain.getTuile(y, x+1) == nullptr 
        && terrain.getTuile(y, x-1) == nullptr 
        && terrain.getTuile(y+1, x) == nullptr 
        && terrain.getTuile(y-1, x) == nullptr 
        && terrain.isEmpty() ) {
        return true;
    }

    if( terrain.getTuile(y, x+1) != nullptr) {
        if (tuile->bords[1] == terrain.getTuile(y,x+1)->bords[3])
            return true;
    }
    if( terrain.getTuile(y, x-1) != nullptr) {
        if (tuile->bords[3] == terrain.getTuile(y,x-1)->bords[1])
            return true;
    }
    if( terrain.getTuile(y-1, x) != nullptr) {
        if (tuile->bords[0] == terrain.getTuile(y-1,x)->bords[2])
            return true;
    }
    if( terrain.getTuile(y+1, x) != nullptr) {
        if (tuile->bords[2] == terrain.getTuile(y+1, x)->bords[0])
            return true;
    }
    return false;
}

bool Trax::placeTuile(int y, int x, TuileTrax* tuile) {
    bool n = tryPlaceTuile(y, x, tuile);
    if(n == false)
        return false;
    terrain.terrain[y][x] = tuile;
    return true;
}


void Trax::angleForcedPlays(int y, int x) {
    TuileTrax * top = terrain.getTuile(y-1,x);
    TuileTrax * right = terrain.getTuile(y,x+1);
    TuileTrax * bottom = terrain.getTuile(y+1,x);
    TuileTrax * left = terrain.getTuile(y,x-1);
    if(
        top != nullptr && left != nullptr
        && top->bords[2] == left->bords[1]
    ) {
        BordColor c1 = top->bords[2];
        BordColor c2 = c1 == white ? red : white;
        placeTuile(y,x, new TuileTrax(vector<BordColor>{c1,c2,c2,c1}));
        return;
    }
    if(
        top != nullptr && right != nullptr
        && top->bords[2] == right->bords[3]
    ) {
        BordColor c1 = top->bords[2];
        BordColor c2 = c1 == white ? red : white;
        placeTuile(y,x, new TuileTrax(vector<BordColor>{c1,c1,c2,c2}));
        return;
    }

    if(
        bottom != nullptr && left != nullptr
        && bottom->bords[0] == left->bords[1]
    ) {
        BordColor c1 = bottom->bords[0];
        BordColor c2 = c1 == white ? red : white;
        placeTuile(y,x, new TuileTrax(vector<BordColor>{c2,c2,c1,c1}));
        return;
    }
    if(
        bottom != nullptr && right != nullptr
        && bottom->bords[0] == right->bords[3]
    ) {
        BordColor c1 = bottom->bords[0];
        BordColor c2 = c1 == white ? red : white;
        placeTuile(y,x, new TuileTrax(vector<BordColor>{c2,c1,c1,c2}));
        return;
    }
}

void Trax::lineForcedPlays(int y, int x) {
    TuileTrax * top = terrain.getTuile(y-1,x);
    TuileTrax * bottom = terrain.getTuile(y+1,x);
    if(
        top != nullptr && bottom != nullptr
        && top->bords[2] == bottom->bords[0]
    ) {
        BordColor c1 = top->bords[2];
        BordColor c2 = c1 == white ? red : white;
        placeTuile(y,x, new TuileTrax(vector<BordColor>{c1,c2,c1,c2}));
        return;
    }
    TuileTrax * left = terrain.getTuile(y,x-1);
    TuileTrax * right = terrain.getTuile(y,x+1);
    if(
        left != nullptr && right != nullptr
        && left->bords[1] == right->bords[3]
    ) {
        BordColor c1 = left->bords[1];
        BordColor c2 = c1 == white ? red : white;
        placeTuile(y,x, new TuileTrax(vector<BordColor>{c2,c1,c2,c1}));
    } 
    return;
}


void Trax::doAllForcedPlays(vector<tuple<int,int>> liste) {
    for(int y = 0 ; y < terrain.height; y++) {
        for(int x = 0; x < terrain.width; x++) {
            if(terrain.getTuile(y,x) == nullptr){
                tuple<int,int> a = {y,x};  
                liste.push_back(a);
                angleForcedPlays(y,x);
            }
            if(terrain.getTuile(y,x) == nullptr){
                tuple<int,int> a = {y,x};
                liste.push_back(a);
                lineForcedPlays(y,x);
            }
        }
    }
}



vector<tuple<int, TuileTrax *>> unionLists(vector<tuple<int, TuileTrax *>> a, vector<tuple<int, TuileTrax *>> b) {
    for(size_t i = 0; i < b.size(); i++ ) {
        a.push_back(b[i]);
    }
    return a;
}

// cherche et renvoi un joueur gagnant
int Trax::checkVictory(vector<tuple<int,int>> listeA,BordColor couleur) {
    
    int resultat = -1;
    for(int i =0; i < terrain.height;i++){
        for(int j =0; j < terrain.width;j++){
            if(terrain.getTuile(i,j) != nullptr){
                tuple<int,int> premier = {i,j};
                //liste.push_back(premier); 

                vector<tuple<int,int>> nouveauL;
                nouveauL.push_back(premier);
                resultat = allerDirection(nouveauL,i,j,couleur);
                return resultat;
            }
        }
    }


    return resultat;
}



int Trax::allerDirection(vector<tuple<int,int>> positionDejaParcourue,int i,int j,BordColor couleur){
    int resultat = -1;
    TuileTrax* tuile = terrain.getTuile(i,j);
    tuple<int,int> position = {i,j};
    positionDejaParcourue.push_back(position);   
    resultat = deplacementBas(terrain,tuile,positionDejaParcourue,i,j,couleur);
     
    cout << "Resultat: " << resultat << endl; 
    //if(resultat == -1){resultat = victoireParLigne(positionDejaParcourue);}
    return resultat;
}

int Trax::verifierListe(vector<tuple<int,int>> liste, tuple<int,int> nouveau){
    for(size_t i=0; i < liste.size();i++){
        int listeA = std::get<0>(liste[i]);
        int listeB = std::get<1>(liste[i]); 
        int nouveauA = std::get<0>(nouveau);
        int nouveauB = std::get<1>(nouveau);
        //cout << listeA << "|" << listeB << "==" << nouveauA << "|" << nouveauB << endl;
        if(listeA == nouveauA && listeB == nouveauB){
            cout << "je boucle" << endl;
            //cout << "A: " << listeA << " " << listeB <<  " B: " << nouveauA << " " << nouveauB << endl;
            return 0;
        }
    }
    return -1;
    //return victoireParLigne(liste);
}

int Trax::victoireParLigne(vector<tuple<int,int>> liste){
    bool depart = false;
    bool arrive = false;

    bool departX = false;
    bool arriveX = false;

    bool departY = false;
    bool arriveY = false;

    for(size_t i = 0; i < liste.size();i++){
        tuple<int,int> x = liste[i];
        int a  = std::get<0>(x);
        int b = std::get<1>(x);

        if(a == 0){/*cout << "departX == true" << endl; */departX = true;}
        if(a == 7){/*cout << "arriveX == true" << endl;*/ arriveX = true;}
        if(b == 0){/*cout << "departY == true" << endl;*/ departY = true;}
        if(b == 7){/*cout << "arriveY == true" << endl;*/ arriveY = true;}

    }

    if(departX == true && arriveX == true){return 0;}
    if(departY == true && arriveY == true){return 0;}


    /*if(depart == true){ cout << "depart == true" << endl;}
    if(arrive == true){ cout << "arrive == true" << endl;}
    
    if(depart == false || arrive == false){return -1;}
    cout << "VICTOIRE PAR LIGNE " << endl; return 0; */

    return -1;
}

void Trax::printListe(vector<tuple<int,int>> liste){
    string str = "";
    for(size_t i = 0; i < liste.size();i++){
        tuple<int,int> x = liste[i];
        str += std::get<0>(x) + "|" + std::get<1>(x) ;
        str += " ";
    }
    cout << str << endl;
}


int Trax::deplacement(Terrain<TuileTrax> terrain,TuileTrax *actuel,vector<tuple<int,int>> liste,int i,int j,BordColor couleur){
    cout << "DeplacementHaut depuis " << i << "|" << j << endl;
    int resultat = -1;
    if(i > 0 && terrain.getTuile((i-1),j) != nullptr && resultat == -1){
        //deplacement en haut
        
        TuileTrax *prochain = terrain.getTuile((i-1),j);
       

        if(prochain->bords[2] == actuel->bords[0] && couleur == actuel->bords[0]){
            i--;
            tuple<int,int> x = {i,j};
            cout << "vers " << i << "|" << j << endl;
            if(verifierListe(liste,x) ==0 ){return 0;}
            liste.push_back(x);

            cout <<"victoireParligne" << endl;
            if(victoireParLigne(liste) == 0){return 0;}

            resultat = deplacement(terrain,prochain,liste,i,j,couleur); 
        }
    }

    if(j > 0 && terrain.getTuile(i,(j-1)) != nullptr && resultat == -1){
        //deplacement à gauche
        TuileTrax *prochain = terrain.getTuile(i,j-1);

        if(prochain->bords[1] == actuel->bords[3] && couleur == actuel->bords[3]){    
            j--;
            tuple<int,int> x = {i,j};
            cout << "vers " << i << "|" << j << endl;
            if(verifierListe(liste,x) ==0 ){return 0;}
            liste.push_back(x);

            cout <<"victoireParligne" << endl;
            if(victoireParLigne(liste) == 0){return 0;}
            resultat = deplacementGauche(terrain,prochain,liste,i,j,couleur);
        }
    }

    if(j < 8 && terrain.getTuile(i,(j+1)) != nullptr && resultat == -1){
        //deplacement à droite
        TuileTrax *prochain = terrain.getTuile(i,j+1);

        if(prochain->bords[3] == actuel->bords[1] && couleur == actuel->bords[1]){
            j++;
            tuple<int,int> x = {i,j};
            cout << "vers " << i << "|" << j << endl;
            if(verifierListe(liste,x) ==0 ){return 0;}
            liste.push_back(x);

            cout <<"victoireParligne" << endl;
            if(victoireParLigne(liste) == 0){return 0;}
            resultat = deplacementDroite(terrain,prochain,liste,i,j,couleur);
        }
    }

    return resultat;
}

int Trax::deplacementBas(Terrain<TuileTrax> terrain,TuileTrax *actuel,vector<tuple<int,int>> liste,int i,int j,BordColor couleur){
    int resultat = -1;
    cout << "DeplacementBas depuis " << i << "|" << j << endl;
    
    if(i < 8 && terrain.getTuile((i+1),j) != nullptr && resultat == -1 ){
        //deplacement en bas
        TuileTrax *prochain = terrain.getTuile((i+1),j);

        if(prochain->bords[0] == actuel->bords[2] && couleur == actuel->bords[2]){
            i++;
            tuple<int,int> x = {i,j};
            if(verifierListe(liste,x) ==0 ){return 0;}
            liste.push_back(x);

            cout <<"victoireParligne" << endl;
            if(victoireParLigne(liste) == 0){return 0;}
            cout << "vers " << i << "|" << j << endl;
            resultat = deplacementBas(terrain,prochain,liste,i,j,couleur);
        }
    } 

    if(j > 0 && terrain.getTuile(i,(j-1)) != nullptr && resultat == -1){
        //deplacement à gauche
        TuileTrax *prochain = terrain.getTuile(i,(j-1));

        if(prochain->bords[1] == actuel->bords[3] && couleur == prochain->bords[1]){    
            j--;
            tuple<int,int> x = {i,j};
            if(verifierListe(liste,x) ==0 ){return 0;}
            liste.push_back(x);

            cout <<"victoireParligne" << endl;
            if(victoireParLigne(liste) == 0){return 0;}
            cout << "vers " << i << "|" << j << endl;
            resultat = deplacementGauche(terrain,prochain,liste,i,j,couleur);
        }
    }

    if(j < 8 && terrain.getTuile(i,(j+1)) != nullptr && resultat == -1){
        //deplacement à droite
        TuileTrax *prochain = terrain.getTuile(i,(j+1));
        //cout << (actuel->bords[0] == white) << "|" <<( actuel->bords[2] == white )<< endl;
        
        if(prochain->bords[3] == actuel->bords[1]  && couleur == prochain->bords[3] ){
            j++;
            tuple<int,int> x = {i,j};
            if(verifierListe(liste,x) ==0 ){return 0;}
            liste.push_back(x);

            cout <<"victoireParligne" << endl;
            if(victoireParLigne(liste) == 0){return 0;}
            cout << "vers " << i << "|" << j << endl;
            resultat = deplacementDroite(terrain,prochain,liste,i,j,couleur);
        }
    }

    return resultat;
}

int Trax::deplacementDroite(Terrain<TuileTrax> terrain,TuileTrax *actuel,vector<tuple<int,int>> liste,int i,int j,BordColor couleur){
    int resultat = -1;
    cout << "DeplacementDroite depuis " << i << "|" << j << endl;
    if(i > 0 && terrain.getTuile((i-1),j) != nullptr && resultat == -1){
        //deplacement en haut
        //on vérifie que le prochain n'est pas dans la liste (si le cas on boucle)
        TuileTrax *prochain = terrain.getTuile((i-1),j);
        //cout <<( prochain->bords[2] == actuel->bords[0] )<< endl;
        

        if(prochain->bords[2] == actuel->bords[0]  && couleur == actuel->bords[0]){
            i--;
            tuple<int,int> x = {i,j};
            if(verifierListe(liste,x) ==0 ){return 0;}
            liste.push_back(x);

            cout <<"victoireParligne" << endl;
            if(victoireParLigne(liste) == 0){return 0;}
            cout << "vers " << i << "|" << j << endl;
            resultat = deplacement(terrain,prochain,liste,i,j,couleur); 
        }
    }

    if(i < 8 && terrain.getTuile((i+1),j) != nullptr && resultat == -1 ){
        //deplacement en bas
        TuileTrax *prochain = terrain.getTuile((i+1),j);

        if(prochain->bords[0] == actuel->bords[2] && couleur == actuel->bords[2]){
            i++;
            tuple<int,int> x = {i,j};
            if(verifierListe(liste,x) ==0 ){return 0;}
            liste.push_back(x);

            cout <<"victoireParligne" << endl;
            if(victoireParLigne(liste) == 0){return 0;}
            cout << "vers " << i << "|" << j << endl;
            resultat = deplacementBas(terrain,prochain,liste,i,j,couleur);
        }
    } 

    if(j < 8 && terrain.getTuile(i,(j+1)) != nullptr && resultat == -1){
         //deplacement à droite
        TuileTrax *prochain = terrain.getTuile(i,(j+1));

        if(prochain->bords[3] == actuel->bords[1]  && couleur == actuel->bords[1]){
            j++;
            tuple<int,int> x = {i,j};
            if(verifierListe(liste,x) ==0 ){return 0;}
            liste.push_back(x);

            cout <<"victoireParligne" << endl;
            if(victoireParLigne(liste) == 0){return 0;}
            cout << "vers " << i << "|" << j << endl;
            resultat = deplacementDroite(terrain,prochain,liste,i,j,couleur);
        }
    }

    return resultat;
}

int Trax::deplacementGauche(Terrain<TuileTrax> terrain,TuileTrax *actuel,vector<tuple<int,int>> liste,int i,int j,BordColor couleur){
    int resultat = -1;
    cout << "DeplacementDroite depuis " << i << "|" << j << endl;
    if(i > 0 && terrain.getTuile((i-1),j) != nullptr && resultat == -1){
        //deplacement en haut
        //on vérifie que le prochain n'est pas dans la liste (si le cas on boucle)
        TuileTrax *prochain = terrain.getTuile((i-1),j);
        cout <<( prochain->bords[2] == actuel->bords[0] )<< endl;
        

        if(prochain->bords[2] == actuel->bords[0] && couleur == actuel->bords[0]){
            i--;
            tuple<int,int> x = {i,j};
            if(verifierListe(liste,x) ==0 ){return 0;}
            liste.push_back(x);
            if(victoireParLigne(liste) == 0){return 0;}
            cout << "vers " << i << "|" << j << endl;
            resultat = deplacement(terrain,prochain,liste,i,j,couleur); 
        }
    }

    if(i < 8 && terrain.getTuile((i+1),j) != nullptr && resultat == -1 ){
        //deplacement en bas
        TuileTrax *prochain = terrain.getTuile((i+1),j);

        if(prochain->bords[0] == actuel->bords[2] && couleur == actuel->bords[2]){
            i++;
            tuple<int,int> x = {i,j};
            if(verifierListe(liste,x) ==0 ){return 0;}
            liste.push_back(x);
            if(victoireParLigne(liste) == 0){return 0;}
            cout << "vers " << i << "|" << j << endl;
            resultat = deplacementBas(terrain,prochain,liste,i,j,couleur);
        }
    } 

    if(j > 0 && terrain.getTuile(i,(j-1)) != nullptr && resultat == -1){
        //deplacement à gauche
        TuileTrax *prochain = terrain.getTuile(i,(j-1));

        if(prochain->bords[1] == actuel->bords[3] && couleur == actuel->bords[3]){    
            j--;
            tuple<int,int> x = {i,j};
            if(verifierListe(liste,x) ==0 ){return 0;}
            liste.push_back(x);
            if(victoireParLigne(liste) == 0){return 0;}
            cout << "vers " << i << "|" << j << endl;
            resultat = deplacementGauche(terrain,prochain,liste,i,j,couleur);
        }
    }

    return resultat;
}


void Trax::start(){
    int victory = -1;

    int DRAW_WIDTH = 800;
    int DRAW_HEIGHT = 700;
    int controller_start_x = DRAW_WIDTH*0.75;
    int controller_width = DRAW_WIDTH*0.25;
    int block_width = controller_start_x/terrain.width;
    int block_height = DRAW_HEIGHT/terrain.height;
    Font font;
    font.loadFromFile("./resources/arial.ttf");

    TuileTrax defaultTuile = TuileTrax(vector<BordColor>{white,red,white,red});
    TuileTrax *pick = new TuileTrax(defaultTuile);
    

    Texture retour_texture;
    retour_texture.loadFromFile("./resources/Retour.jpg");
    Sprite retour_sprite;
    retour_sprite.setTexture(retour_texture);
    retour_sprite.setScale(1.5,1.5);
    retour_sprite.move(controller_start_x+(controller_width*0.25),620);
    FloatRect retour_bounds = retour_sprite.getGlobalBounds();

    Texture turn_texture;
    turn_texture.loadFromFile("./resources/turn.jpg");
    Sprite turn_sprite;
    turn_sprite.setTexture(turn_texture);
    turn_sprite.setScale(0.3, 0.3);
    turn_sprite.move(controller_start_x+(controller_width*0.25),300);
    FloatRect turn_bounds = turn_sprite.getGlobalBounds();

    Texture flip_texture;
    flip_texture.loadFromFile("./resources/flip.png");
    Sprite flip_sprite;
    flip_sprite.setTexture(flip_texture);
    flip_sprite.setScale(0.4, 0.4);
    flip_sprite.move(controller_start_x+(controller_width*0.30),430);
    FloatRect flip_bounds = flip_sprite.getGlobalBounds();


    Text player_text;
    player_text.setFont(font);
    player_text.setString("Joueur Blanc");
    player_text.setFillColor(Color::Black);
    player_text.setCharacterSize(20);
    player_text.move(controller_start_x+(controller_width*0.25), 6);


    RenderWindow app(VideoMode(DRAW_WIDTH, DRAW_HEIGHT, 32), "Trax");
    while (app.isOpen()){
        Event event;
        while (app.pollEvent(event)){
            switch (event.type) {
                case Event::Closed:
                    app.close(); break;
                case Event::MouseButtonPressed: {
                    if (victory==-1 && event.mouseButton.button == sf::Mouse::Left) {
                        Vector2f mouse = app.mapPixelToCoords(Mouse::getPosition(app));
                        if(retour_bounds.contains(mouse)){
                            app.close();
                            openMenuPrincipal();
                        } else if(turn_bounds.contains(mouse)){
                            pick->turn();
                        } else if(flip_bounds.contains(mouse)) {
                            if(pick->bords[0] == pick->bords[1] || pick->bords[1] == pick->bords[2]) {
                                // pick = tuile AABB avec n'importe quel rotation
                                pick = new TuileTrax(vector<BordColor>{white,red,white,red});
                            } else {
                                // pick = tuile ABAB
                                pick = new TuileTrax(vector<BordColor>{white,white,red,red});
                            }
                        }
                        if(0 < mouse.x && mouse.x < DRAW_WIDTH-200 && 0 < mouse.y && mouse.y < DRAW_HEIGHT) {

                            int x = mouse.x / block_width;
                            int y = mouse.y / block_height;
                            if(0 <= x && x < terrain.width && 0 <= y && y < terrain.height) {
                            
                                if(placeTuile(y,x, pick)) {
                                    BordColor couleur;
                                    vector<tuple<int,int>> liste;
                                    doAllForcedPlays(liste);
                                    pick = new TuileTrax(defaultTuile);
                                    player = (player+1) %2;

                                    string player_str = player==0 ? "blanc" : "rouge";
                                    player_text.setString("Joueur " + player_str);

                                    player == 0 ? couleur = white : couleur =  red;
                                    victory = checkVictory(liste,couleur); // on regarde si le joueur qui pose gagne et après si l'autre gagne
                                   if(victory == 0 && couleur == white){victory = 1;}     // 1 victoire blanche       
                                    if(victory == 0 && couleur == red){victory = 2;}

                                  /*if(victory == 0 && couleur == white){ // le joueur qui a jouer à t'il gagner ?
                                        victory = 1;
                                    }else if(victory == 0 && couleur == red){
                                        victory = 2;
                                    }else if(victory == -1){
                                        if(couleur == white){
                                            couleur = red;
                                        }else{
                                            couleur = white;
                                        }
                                        victory = checkVictory(liste,couleur); // le joueur qui n'a pas jouer à t'il gagner ?
                                        if(victory == 0){
                                            if(couleur == red){
                                                victory  = 2;
                                            }else if(couleur == white){
                                                victory = 1;
                                            }
                                        }
                                    } */


                                    //faire animation Victoire et faire autre joueur
                                    cout << "__________________" << endl;
                                }
                           }
                        }
                    } 
                    break;
                }
                default: break;
            }
        }
        app.clear();
        app.draw(RectangleShape(Vector2f(DRAW_WIDTH, DRAW_HEIGHT))); // fond blanc

        // affichage de la ligne separation entre le jeu et les controlles
        RectangleShape line(Vector2f(5, DRAW_HEIGHT));
        line.move(controller_start_x, 0);
        line.setFillColor(Color(0,0,0));
        app.draw(line);

        // affichage du terrain de jeu
        terrain.draw(&app, controller_start_x, DRAW_HEIGHT);

        // affichage des controlles
        app.draw(player_text);
        int pick_start_x = controller_start_x+(controller_width*0.3);
        int pick_end_x = controller_start_x+(controller_width*0.9);
        pick->draw(&app, 
            pick_start_x, 120, 
            pick_end_x-pick_start_x, 
            pick_end_x-pick_start_x
            );
        

        if(victory > -1) {
            // TODO victory
            string winner_string ;
            victory == 1 ? winner_string = "Joueur Blanc est gagnant" : winner_string = "Joueur Rouge est gagnant" ;
            RectangleShape rect(Vector2f(controller_start_x*0.50, DRAW_HEIGHT*0.25));
            rect.move(controller_start_x*0.25, DRAW_HEIGHT*0.40);
            app.draw(rect);

            Text text;
            text.setFont(font);
            text.setString(winner_string);
            text.setCharacterSize(30);
            text.setFillColor(Color::Black);
            text.move(controller_start_x*0.3, DRAW_HEIGHT*0.44);
            app.draw(text);
        }
        
        app.draw(retour_sprite);
        app.draw(turn_sprite);
        app.draw(flip_sprite);
        app.display();
    } 
}

