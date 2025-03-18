
#include "PokemonDB.hpp"

PokemonDB::PokemonDB()
{
    // Ajouter des Pokémon à la base de données
    pokemonList["Palkia"] = new WaterDragonPokemon("Palkia", 100, 120, 90, 100, "assets/images/Palkia.png", "assets/images/palkia_back.png");
    pokemonList["Dialga"] = new SteelPokemon("Dialga", 100, 130, 100, 120, "assets/images/Dialga.png", "assets/images/Dialga_back.png");
    pokemonList["Giratina"] = new SpectrePokemon("Giratina", 150, 100, 120, 90, "assets/images/Giratina.png", "assets/images/giratina_back.png");
    pokemonList["Arceus"] = new Arceus("Arceus", 120, 140, 120, 120, "assets/images/Arceus.png", "assets/images/arceus_back.png");
    pokemonList["Charizard"] = new FirePokemon("Charizard", 150, 10, 100, 100, "assets/images/Charizard.png", "assets/images/charizard_back.png");
    pokemonList["Mewtwo"] = new PsyPokemon("Mewtwo", 150, 120, 100, 120, "assets/images/Mewtwo.png", "assets/images/mewtwo_back.png");
    pokemonList["Pikachu"] = new electriquePokemon("Pikachu", 100, 120, 100, 100, "assets/images/Pikachu.png", "assets/images/Pikachu_back.png");
    pokemonList["Reshiram"] = new FireDragonPokemon("Reshiram", 100, 120, 120, 100, "assets/images/Reshiram.png", "assets/images/Reshiram_back.png"); // Ajouter plus de Pokémon ici
    pokemonList["Zekrom"] = new electriqueDragonPokemon("Zekrom", 100, 120, 100, 100, "assets/images/Zekrom.png", "assets/images/Zekrom_back.png");
    pokemonList["Blastoise"] = new WaterPokemon("Blastoise", 150, 120, 100, 100, "assets/images/Blastoise.png", "assets/images/Blastoise_back.png");
    pokemonList["Rayquaza"] = new DragonPokemon("Rayquaza", 100, 120, 100, 100, "assets/images/Rayquaza.png", "assets/images/Rayquaza_back.png");
    pokemonList["Lugia"] = new DragonPokemon("Lugia", 100, 120, 100, 100, "assets/images/Lugia.png", "assets/images/Lugia_back.png");
    pokemonList["Ho-Oh"] = new FirePokemon("Ho-Oh", 100, 120, 100, 100, "assets/images/Ho-Oh.png", "assets/images/Ho-Oh_back.png");
    pokemonList["Groudon"] = new EarthPokemon("Groudon", 100, 120, 100, 100, "assets/images/Groudon.png", "assets/images/Groudon_back.png");
    pokemonList["Kyogre"] = new WaterPokemon("Kyogre", 100, 120, 100, 100, "assets/images/Kyogre.png", "assets/images/Kyogre_back.png");
    pokemonList["Suicune"] = new WaterPokemon("Suicune", 100, 120, 100, 100, "assets/images/Suicune.png", "assets/images/Suicune_back.png");
    pokemonList["Entei"] = new FirePokemon("Entei", 100, 120, 100, 100, "assets/images/Entei.png", "assets/images/Entei_back.png");
    pokemonList["Raikou"] = new electriquePokemon("Raikou", 100, 100, 100, 100, "assets/images/Raikou.png", "assets/images/Raikou_back.png");
    pokemonList["Articuno"] = new WaterPokemon("Articuno", 100, 120, 100, 100, "assets/images/Articuno.png", "assets/images/Articuno_back.png");
    pokemonList["Zapdos"] = new electriquePokemon("Zapdos", 100, 100, 100, 100, "assets/images/Zapdos.png", "assets/images/Zapdos_back.png");
    pokemonList["Moltres"] = new FirePokemon("Moltres", 100, 100, 100, 100, "assets/images/Moltres.png", "assets/images/Moltres_back.png");
}
PokemonDB::~PokemonDB()
{
}
Pokemon *PokemonDB::getPokemonByName(const std::string &name) const
{
    auto it = pokemonList.find(name);
    if (it != pokemonList.end())
    {
        return it->second;
    }
    return nullptr; // Retourne un pointeur null si le Pokémon n'est pas trouvé
}

std::vector<std::string> PokemonDB::getAllPokemonNames() const
{
    std::vector<std::string> names;
    for (const auto &pair : pokemonList)
    {
        names.push_back(pair.first);
    }
    return names;
}
