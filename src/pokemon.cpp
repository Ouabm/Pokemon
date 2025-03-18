#include "Pokemon.hpp"

Pokemon::~Pokemon(){
    for(move* m :spes){
        delete m;

    }
    spes.clear();
}
void Pokemon::resetMoves()
{
    for (auto m : spes)
    {
        delete m; // Supprime chaque attaque allouée dynamiquement
    }
    spes.clear(); // Vide la liste des attaques
}
