
#include "Misc.hpp"

map<String, Texture>textures;
   
void loadAllTextures() {
    vector<String> paths {
        "resources/trax/BBRR.png",
        "resources/trax/BRBR.png",
        "resources/trax/BRRB.png",
        "resources/trax/RBBR.png",
        "resources/trax/RBRB.png",
        "resources/trax/RRBB.png",
        "resources/Domino.jpg",
        "resources/Retour.jpg",
        "resources/Trax.jpg",
        "resources/cross.jpg",
        "resources/turn.jpg"
    };
    for(size_t i = 0; i < paths.size(); i++ ) {
        Texture text;
        text.loadFromFile(paths[i]);
        textures [paths[i]] = text;
    }
}

Texture getTexture(String s) {
    return textures[s];
}
