#include "Pokemon.hpp"
void Pokemon::resetMoves()
{
    for (auto m : spes)
    {
        delete m; // Supprime chaque attaque allouée dynamiquement
    }
    spes.clear(); // Vide la liste des attaques
}
