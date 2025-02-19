#ifndef TRAINER_HPP
#define TRAINER_HPP

#include <vector>
#include "pokemon.hpp"

class Trainer
{
public:
    Trainer(std::vector<Pokemon> pokemonTeam);

    Pokemon &getActivePokemon();
    void switchPokemon(size_t index);

private:
    std::vector<Pokemon> pokemonTeam;
    int activePokemonIndex;
};

#endif // TRAINER_HPP
