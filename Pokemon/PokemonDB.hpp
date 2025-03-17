#ifndef POKEMONDB_HPP
#define POKEMONDB_HPP

#include <vector>
#include <map>
#include "Pokemon.hpp"

class PokemonDB {
private:
    std::map<std::string, Pokemon*> pokemonList;  // Stocker les Pokémon avec leur nom comme clé

public:
    PokemonDB();  // Constructeur qui charge les données
    virtual ~PokemonDB();

    Pokemon* getPokemonByName(const std::string& name) const;
    std::vector<std::string> getAllPokemonNames() const;
};

#endif