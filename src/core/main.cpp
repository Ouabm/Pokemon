#include <iostream>

#include "game.hpp"
#include "battle.hpp"
#include "pokemon_data.hpp"
#include "move_data.hpp"
#include "trainer.hpp"

int main()
{
    // Création des équipes des joueurs
    Trainer player1({pikachu, charizard, mehdy, tagrandMere});
    Trainer player2({charizard});

    std::cout << "Test: " << player1.getActivePokemon().getName() << std::endl;

    player1.switchPokemon(2);

    std::cout << "Test: " << typeToString(player1.getActivePokemon().getType2()) << std::endl;

    return 0;
}
