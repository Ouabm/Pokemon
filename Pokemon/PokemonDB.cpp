
#include "PokemonDB.hpp"


PokemonDB::PokemonDB() {
    // Ajouter des Pokémon à la base de données
    pokemonList["Palkia"] = Pokemon("Palkia", "Eau", 100, 120, 90, 100, "images/Palkia.png","images/palkia_back.png");
    pokemonList["Dialga"] = Pokemon("Dialga", "Acier", 100, 130, 100, 120, "images/Dialga.png","images/Dialga_back.png");
    pokemonList["Giratina"] = Pokemon("Giratina", "Spectre", 150, 100, 120, 90, "images/Giratina.png","images/giratina_back.png");
    pokemonList["Arceus"] = Pokemon("Arceus", "Normal", 120, 140, 120, 120, "images/Arceus.png","images/arceus_back.png");
    pokemonList["Charizard"] = Pokemon("Charizard", "Feu", 150,10,100,100,"images/Charizard.png","images/charizard_back.png");
    pokemonList["Mewtwo"] = Pokemon("Mewtwo", "Psy", 150, 120, 100, 120,"images/Mewtwo.png","images/mewtwo_back.png");
    pokemonList["Pikachu"] = Pokemon("Pikachu", "elctrique", 100,120,100,100,"images/Pikachu.png","images/Pikachu_back.png");
    pokemonList["Reshiram"] = Pokemon("Reshiram", "Dragon",100,120,120,100,"images/Reshiram.png","images/Reshiram_back.png");    // Ajouter plus de Pokémon ici

    pokemonList["Zekrom"]=Pokemon("Zekrom","Dragon",100,120,100,100,"images/Zekrom.png","images/Zekrom_back.png");
    pokemonList["Blastoise"]=Pokemon("Blastoise","Eau",150,120,100,100,"images/Blastoise.png","images/Blastoise_back.png");
    pokemonList["Rayquaza"]=Pokemon("Rayquaza","Dragon",100,120,100,100,"images/Rayquaza.png","images/Rayquaza_back.png");
    pokemonList["Lugia"]=Pokemon("Lugia","Dragon",100,120,100,100,"images/Lugia.png","images/Lugia_back.png");



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
