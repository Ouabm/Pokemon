#ifndef GAME_MASTER_HPP
#define GAME_MASTER_HPP

#include "pokemon.hpp"
#include <iostream>
#include <vector>

class GameMaster {
private:
    Pokemon* activePokemon1_1;
    Pokemon* activePokemon1_2;
    Pokemon* activePokemon2_1;
    Pokemon* activePokemon2_2;
    std::vector<Pokemon*> team1;
    std::vector<Pokemon*> team2;

public:
    GameMaster(std::vector<Pokemon*> p_team1, std::vector<Pokemon*> p_team2);
    void attack(Pokemon* attacker, Pokemon* defender, const move& move);
    void switchPokemon(int player, int slot, int newPokemonIndex);
    bool isBattleOver() const;
};

#endif // GAME_MASTER_HPP