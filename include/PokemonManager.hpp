#pragma once

#include "Pokemon.hpp"
#include <map> // Pour stocker les pokemons

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

    // -------------------------------------------------------------------------------------
    // Pourquoi le Singleton est bien dans ce cas :

    // 1. Accès global unique :
    //    Le Singleton garantit qu'il n'y a qu'une seule instance de PokemonManager, 
    //    ce qui est idéal ici, car il n'y a besoin que d'une seule source de données 
    //    pour tous les Pokémons. Chaque partie de l'application peut y accéder facilement 
    //    via PokemonManager::getInstance() sans avoir à passer des instances en argument.

    // 2. Gestion centralisée des données :
    //    Cela permet de gérer de manière centralisée tous les Pokémons dans une seule instance.
    //    Toutes les données des Pokémons (nom, type, statistiques, etc.) seront accessibles 
    //    sans avoir à dupliquer les objets, ce qui est plus simple à maintenir.

    // 3. Réduction de la duplication des données :
    //    Éviter la création de multiples instances de PokemonManager permet de centraliser
    //    les données et d'éviter d'en stocker plusieurs copies dans différentes parties de 
    //    l'application. Cela améliore la gestion de la mémoire.

    // -------------------------------------------------------------------------------------
};
