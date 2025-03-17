
#include "PokemonDB.hpp"


PokemonDB::PokemonDB() {
    // Ajouter des Pokémon à la base de données
    pokemonList["Palkia"] = new WaterDragonPokemon("Palkia", 100, 120, 90, 100, "images/Palkia.png", "images/palkia_back.png");
    pokemonList["Dialga"] = new SteelPokemon("Dialga", 100, 130, 100, 120, "images/Dialga.png","images/Dialga_back.png");
    pokemonList["Giratina"] = new SpectrePokemon("Giratina", 150, 100, 120, 90, "images/Giratina.png","images/giratina_back.png");
    pokemonList["Arceus"] = new Arceus("Arceus", 120, 140, 120, 120, "images/Arceus.png","images/arceus_back.png");
    pokemonList["Charizard"] = new FirePokemon("Charizard", 150,10,100,100,"images/Charizard.png","images/charizard_back.png");
    pokemonList["Mewtwo"] = new PsyPokemon("Mewtwo", 150, 120, 100, 120,"images/Mewtwo.png","images/mewtwo_back.png");
    pokemonList["Pikachu"] = new electriquePokemon("Pikachu", 100,120,100,100,"images/Pikachu.png","images/Pikachu_back.png");
    pokemonList["Reshiram"] = new FireDragonPokemon("Reshiram",100,120,120,100,"images/Reshiram.png","images/Reshiram_back.png");    // Ajouter plus de Pokémon ici
    pokemonList["Zekrom"]=new electriqueDragonPokemon("Zekrom",100,120,100,100,"images/Zekrom.png","images/Zekrom_back.png");
    pokemonList["Blastoise"]=new WaterPokemon("Blastoise",150,120,100,100,"images/Blastoise.png","images/Blastoise_back.png");
    pokemonList["Rayquaza"]=new DragonPokemon("Rayquaza",100,120,100,100,"images/Rayquaza.png","images/Rayquaza_back.png");
    pokemonList["Lugia"]=new DragonPokemon("Lugia",100,120,100,100,"images/Lugia.png","images/Lugia_back.png");
    pokemonList["Ho-Oh"]=new FirePokemon("Ho-Oh",100,120,100,100,"images/Ho-Oh.png","images/Ho-Oh_back.png");
    pokemonList["Groudon"]=new EarthPokemon("Groudon",100,120,100,100,"images/Groudon.png","images/Groudon_back.png");
    pokemonList["Kyogre"]=new WaterPokemon("Kyogre",100,120,100,100,"images/Kyogre.png","images/Kyogre_back.png");
    pokemonList["Suicune"]=new WaterPokemon("Suicune",100,120,100,100,"images/Suicune.png","images/Suicune_back.png");
    pokemonList["Entei"]=new FirePokemon("Entei",100,120,100,100,"images/Entei.png","images/Entei_back.png");
    pokemonList["Raikou"]=new electriquePokemon("Raikou",100,100,100,100,"images/Raikou.png","images/Raikou_back.png");
    pokemonList["Articuno"]=new WaterPokemon("Articuno",100,120,100,100,"images/Articuno.png","images/Articuno_back.png");
    pokemonList["Zapdos"]=new electriquePokemon("Zapdos",100,100,100,100,"images/Zapdos.png","images/Zapdos_back.png");
    pokemonList["Moltres"]=new FirePokemon("Moltres",100,100,100,100,"images/Moltres.png","images/Moltres_back.png");



}
PokemonDB::~PokemonDB(){
    
}
Pokemon* PokemonDB::getPokemonByName(const std::string& name) const {
    auto it = pokemonList.find(name);
    if (it != pokemonList.end()) {
        return it->second;
    }
    return nullptr;  // Retourne un pointeur null si le Pokémon n'est pas trouvé
}

std::vector<std::string> PokemonDB::getAllPokemonNames() const {
    std::vector<std::string> names;
    for (const auto& pair : pokemonList) {
        names.push_back(pair.first);
    }
    return names;
}
