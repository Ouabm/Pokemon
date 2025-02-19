#include "trainer.hpp"

Trainer::Trainer(std::vector<Pokemon> pokemonTeam) : pokemonTeam(pokemonTeam), activePokemonIndex(0) {}

Pokemon &Trainer::getActivePokemon()
{
    if (pokemonTeam.empty())
    {
        throw std::runtime_error("No Pokémon in the team!");
    }
    return pokemonTeam[activePokemonIndex];
}

void Trainer::switchPokemon(size_t index)
{
    if (index >= pokemonTeam.size())
    {
        std::cerr << "Invalid index: " << index << std::endl;
        return;
    }
    activePokemonIndex = index;
}
