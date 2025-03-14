
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
    pokemonList["Ho-Oh"]=Pokemon("Ho-Oh","Feu",100,120,100,100,"images/Ho-Oh.png","images/Ho-Oh_back.png");
    pokemonList["Groudon"]=Pokemon("Groudon","Terre",100,120,100,100,"images/Groudon.png","images/Groudon_back.png");
    pokemonList["Kyogre"]=Pokemon("Kyogre","Eau",100,120,100,100,"images/Kyogre.png","images/Kyogre_back.png");
    pokemonList["Suicune"]=Pokemon("Suicune","Eau",100,120,100,100,"images/Suicune.png","images/Suicune_back.png");
    pokemonList["Entei"]=Pokemon("Entei","Feu",100,120,100,100,"images/Entei.png","images/Entei_back.png");
    pokemonList["Raikou"]=Pokemon("Raikou","elctrique",100,100,100,100,"images/Raikou.png","images/Raikou_back.png");
    pokemonList["Articuno"]=Pokemon("Articuno","Glace",100,120,100,100,"images/Articuno.png","images/Articuno_back.png");
    pokemonList["Zapdos"]=Pokemon("Zapdos","elctrique",100,100,100,100,"images/Zapdos.png","images/Zapdos_back.png");
    pokemonList["Moltres"]=Pokemon("Moltres","Feu",100,100,100,100,"images/Moltres.png","images/Moltres_back.png");



}
PokemonDB::~PokemonDB(){
    
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
