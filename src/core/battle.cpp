#include "battle.hpp"
#include <iostream>

Battle::Battle(Trainer &player1, Trainer &player2)
    : player1(player1), player2(player2) {}

void Battle::start()
{
    // Logique de démarrage du combat
}

void Battle::performTurn()
{
    // Logique de déroulement du tour
    // Étape 3 : calculer l'ordre des actions, attaque, switch
}
