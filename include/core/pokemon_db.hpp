#ifndef POKEMON_DB_HPP
#define POKEMON_DB_HPP

#include "pokemon.hpp"
#include "move_db.hpp"

class PokemonDB
{
private:
    std::map<std::string, Pokemon> pokemonList; // Stocker les Pokémon avec leur nom comme clé

public:
    // Constructeur qui charge les données
    PokemonDB()
    {
        pokemonList["Charizard"] = Pokemon("Charizard", Type::Fire, Type::Flying, 100, 100, 300, 250, 240, 200, 180, 300, flamethrower, fly, dragonClaw, slash, "images/charizard.png");
        pokemonList["Pikachu"] = Pokemon("Pikachu", Type::Electric, Type::None, 50, 50, 200, 150, 140, 100, 100, 200, flamethrower, fly, dragonClaw, slash, "images/pikachu.png");
        pokemonList["Bouboule"] = Pokemon("Bouboule", Type::Grass, Type::None, 50, 50, 200, 150, 140, 100, 100, 200, flamethrower, fly, dragonClaw, slash, "images/bouboule.png");
        pokemonList["Mehdy"] = Pokemon("Mehdy", Type::Steel, Type::Dragon, 50, 50, 200, 150, 140, 100, 100, 200, flamethrower, fly, dragonClaw, slash, "images/mehdy.png");
    }

    // Récupérer un Pokémon par son nom
    const Pokemon *getPokemonByName(const std::string &name) const
    {
        auto it = pokemonList.find(name);
        if (it != pokemonList.end())
        {
            return &it->second;
        }
        return nullptr; // Retourne nullptr si non trouvé
    }

    // Obtenir la liste des noms de tous les Pokémon
    std::vector<std::string> getAllPokemonNames() const
    {
        std::vector<std::string> names;
        for (const auto &pair : pokemonList)
        {
            names.push_back(pair.first);
        }
        return names;
    }
};

#endif // POKEMON_DB_HPP
