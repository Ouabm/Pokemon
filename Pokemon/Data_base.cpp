#include "Data_base.hpp"

Database::Database() {
    loadPokemons();
}

// Singleton : retourne une seule instance de Database
Database& Database::getInstance() {
    static Database instance;
    return instance;
}

// Charger les Pokémon par défaut
void Database::loadPokemons() {
    pokemons["Palkia"] = Pokemon("Palkia", "Eau", 100, 100, 100, 100, "images/palkia_back.png");
    pokemons["Dialga"] = Pokemon("Dialga", "Acier", 100, 100, 100, 100, "images/dialga.png");
    pokemons["Giratina"] = Pokemon("Giratina", "Spectre", 100, 100, 100, 100, "images/giratina_back.png");
    pokemons["Arceus"] = Pokemon("Arceus", "Normal", 100, 100, 100, 100, "images/arceus.png");
}

// Obtenir un Pokémon par son nom
Pokemon Database::getPokemon(const std::string& name) const {
    auto it = pokemons.find(name);
    if (it != pokemons.end()) {
        return it->second;
    } else {
        throw std::runtime_error("Erreur : Pokémon non trouvé dans la base de données.");
    }
}

// Ajouter un Pokémon à la base
void Database::addPokemon(const Pokemon& pokemon) {
    pokemons[pokemon.getName()] = pokemon;
}
