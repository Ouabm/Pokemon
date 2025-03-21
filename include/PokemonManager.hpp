#pragma once

#include <map>
#include <vector>
#include "Pokemon.hpp"
#include "Move.hpp"
#include "MoveManager.hpp"

class PokemonManager
{
private:
    std::map<std::string, Pokemon> pokemonList; // Stocker les Pokémons avec leur nom comme clé

    // Fonction pour charger les Pokémon dans pokemonList
    void loadPokemonData();

    // Constructeur privé pour interdire la création d'instances multiples
    PokemonManager();

public:
    // Méthode pour obtenir l'instance unique de PokemonManager
    static PokemonManager &getInstance();

    // Récupérer un Pokémon par son nom (retourne un pointeur vers Pokémon)
    Pokemon* getPokemonByName(const std::string &name);

    // Obtenir la liste des noms de tous les Pokémons
    std::vector<std::string> getAllPokemonNames() const;

    // Désactiver la copie de l'instance
    PokemonManager(const PokemonManager&) = delete;
    PokemonManager& operator=(const PokemonManager&) = delete;
};
