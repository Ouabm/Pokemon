#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <unordered_map>
#include "Pokemon.hpp"

class Database {
public:
    static Database& getInstance();  // Singleton pour éviter plusieurs instances

    Pokemon getPokemon(const std::string& name) const;  // Obtenir un Pokémon par son nom
    void addPokemon(const Pokemon& pokemon);  // Ajouter un Pokémon à la base

private:
    std::unordered_map<std::string, Pokemon> pokemons;  // Stocke les Pokémon
    Database();  // Constructeur privé pour empêcher plusieurs instances
    void loadPokemons();  // Charge les Pokémon par défaut
};

#endif
