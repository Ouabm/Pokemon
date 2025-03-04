
#include "PokemonDB.hpp"
#include "type.hpp"

PokemonDB::PokemonDB() {
    // Ajouter des Pokémon à la base de données
    pokemonList["Palkia"] = Pokemon("Palkia", "Eau", 100, 120, 90, 100, "images/palkia_back.png");
    pokemonList["Dialga"] = Pokemon("Dialga", "Acier", 100, 130, 100, 120, "images/dialga.png");
    pokemonList["Giratina"] = Pokemon("Giratina", "Spectre", 150, 100, 120, 90, "images/giratina.png");
    pokemonList["Arceus"] = Pokemon("Arceus", "Normal", 120, 140, 120, 120, "images/arceus_back.png");
    pokemonList["Charizard"] = Pokemon("Charizard", "Feu", 150,10,100,100,"images/charizard.png");
    pokemonList["Mewtwo"] = Pokemon("Mewtwo", "Psy", 150, 120, 100, 120,"images/mewtwo_back.png");

    // Ajouter plus de Pokémon ici
}

Pokemon PokemonDB::getPokemonByName(const std::string& name) const {
    auto it = pokemonList.find(name);
    if (it != pokemonList.end()) {
        return it->second;
    }
    return Pokemon();  // Retourne un Pokémon vide si non trouvé
}

std::vector<std::string> PokemonDB::getAllPokemonNames() const {
    std::vector<std::string> names;
    for (const auto& pair : pokemonList) {
        names.push_back(pair.first);
    }
    return names;
}
