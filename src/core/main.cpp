#include <iostream>

#include "game.hpp"
#include "battle.hpp"
#include "pokemon_data.hpp"
#include "move_data.hpp"
#include "trainer.hpp"

// int main()
// {
//     // Création des équipes des joueurs
//     Trainer player1({pikachu, charizard, mehdy});
//     Trainer player2({charizard});

//     std::cout << "Test: " << player1.getActivePokemon().getName() << std::endl;

//     player1.switchPokemon(2);

//     std::cout << "Test: " << typeToString(player1.getActivePokemon().getType2()) << std::endl;

//     //

//     return 0;
// }

#include <stdio.h>

void iaSelectAction()
{
    printf("1. L'IA sélectionne ses attaques ou switch.\n");
}

void playerSelectAction(int player)
{
    printf("2. Joueur %d sélectionne son choix : switch ou attaque.\n", player);
}

void determineTurnOrder()
{
    printf("3. Établissement de l'ordre du tour :\n");
    printf("3.1 On switch les Pokémon par ordre de vitesse.\n");
    printf("3.2 Classement des attaques par ordre de priorité.\n");
    printf("3.3 En cas d'égalité, on se base sur la vitesse.\n");
}

void executeAttacks()
{
    printf("4. Combat :\n");
    printf("4.1 Attaque 1 + effet.\n");
    printf("4.2 Si pas K.O, Attaque 2 + effet.\n");
    printf("4.3 Si pas K.O, Attaque 3 + effet.\n");
    printf("4.4 Si pas K.O, Attaque 4 + effet.\n");
}

void endOfTurnEffects()
{
    printf("5. Application des effets passifs de fin de tour.\n");
}

void handleKoPokemon()
{
    printf("6. Remplacement des Pokémon K.O si nécessaire.\n");
}

int checkEndOfBattle()
{
    printf("7. Vérification si une équipe n'a plus de Pokémon.\n");
    return 0; // 0 pour continuer, 1 si une équipe a perdu
}

int main()
{
    printf("Début du combat Pokémon simplifié.\n");

    // Init menu pokemon choix

    int battleFinished = 0;

    while (!battleFinished)
    {
        iaSelectAction();
        playerSelectAction(1);
        playerSelectAction(2);

        determineTurnOrder();

        executeAttacks();

        endOfTurnEffects();

        handleKoPokemon();

        battleFinished = checkEndOfBattle();

        if (!battleFinished)
        {
            printf("Fin du tour, le combat continue.\n");
            battleFinished++;
        }
    }

    printf("Fin du combat.\n");

    //restart

    return 0;
}