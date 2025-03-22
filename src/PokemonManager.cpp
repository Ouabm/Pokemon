#include "PokemonManager.hpp"
#include "MoveManager.hpp"

// Constructeur qui initialise la base de données de Pokémon
PokemonManager::PokemonManager()
{
    loadPokemonData();
}

// Retourne l'instance unique de PokemonManager
PokemonManager &PokemonManager::getInstance()
{
    static PokemonManager instance;
    return instance;
}

// Fonction pour charger les données des Pokémon
void PokemonManager::loadPokemonData()
{
    // Exemple d'ajout de Pokémon à la liste
    pokemonList["Arceus"] = Pokemon("Arceus", Type::Normal, Type::None, 50, 195, 195, 140, 140, 140, 140, 140, judgment, earthPower, gunkShot, sacredSword);
    pokemonList["Articuno"] = Pokemon("Articuno", Type::Ice, Type::Flying, 50, 165, 165, 105, 120, 115, 145, 105, iceBeam, fly, scald, hurricane);
    pokemonList["Charizard"] = Pokemon("Charizard", Type::Fire, Type::Flying, 50, 153, 153, 104, 98, 129, 105, 120, flameThrower, fly, dragonClaw, hurricane);
    pokemonList["Dialga"] = Pokemon("Dialga", Type::Steel, Type::Dragon, 50, 175, 175, 140, 140, 170, 120, 110, dracoMeteor, dragonPulse, flashCannon, flameThrower);
    pokemonList["Entei"] = Pokemon("Entei", Type::Fire, Type::None, 50, 190, 190, 135, 105, 110, 95, 120, fireBlast, firePunch, wildCharge, slash);
    pokemonList["Giratina"] = Pokemon("Giratina", Type::Dragon, Type::Ghost, 50, 225, 225, 120, 140, 120, 140, 110, fireBlast, poltergeist, dracoMeteor, dragonClaw);
    pokemonList["Groudon"] = Pokemon("Groudon", Type::Ground, Type::None, 50, 175, 175, 170, 160, 120, 110, 110, firePunch, precipiceBlades, landsWrath, stoneEdge);
    pokemonList["Ho-Oh"] = Pokemon("Ho-Oh", Type::Fire, Type::Flying, 50, 181, 181, 150, 110, 130, 174, 110, sacredFire, fly, foulPlay, playRough);
    pokemonList["Kyogre"] = Pokemon("Kyogre", Type::Water, Type::None, 50, 175, 175, 120, 110, 170, 160, 110, originPulse, iceBeam, thunder, scald);
    pokemonList["Lugia"] = Pokemon("Lugia", Type::Psychic, Type::Flying, 50, 181, 181, 110, 150, 110, 174, 130, aeroBlast, psychic, fieryWrath, fly);
    pokemonList["Mewtwo"] = Pokemon("Mewtwo", Type::Psychic, Type::None, 50, 181, 181, 130, 110, 174, 110, 150, psychic, shadowBall, moonBlast, auraSphere);
    pokemonList["Moltres"] = Pokemon("Moltres", Type::Fire, Type::Flying, 50, 165, 165, 120, 110, 145, 105, 110, flameThrower, fieryWrath, hurricane, sludgeBomb);
    pokemonList["Palkia"] = Pokemon("Palkia", Type::Water, Type::Dragon, 50, 165, 165, 140, 120, 170, 140, 120, scald, dracoMeteor, dragonPulse, iceBeam);
    pokemonList["Pikachu"] = Pokemon("Pikachu", Type::Electric, Type::None, 50, 110, 110, 75, 60, 70, 70, 110, thunderBolt, thunder, energyBall, moonBlast);
    pokemonList["Raikou"] = Pokemon("Raikou", Type::Electric, Type::None, 50, 165, 165, 105, 95, 135, 120, 135, thunder, thunderBolt, shadowBall, focusBlast);
    pokemonList["Rayquaza"] = Pokemon("Rayquaza", Type::Dragon, Type::Flying, 50, 180, 180, 170, 110, 170, 110, 115, flameThrower, aeroBlast, dragonClaw, dracoMeteor);
    pokemonList["Reshiram"] = Pokemon("Reshiram", Type::Fire, Type::Dragon, 50, 175, 175, 140, 120, 170, 140, 110, fusionFlare, dracoMeteor, dragonPulse, sludgeBomb);
    pokemonList["Suicune"] = Pokemon("Suicune", Type::Water, Type::None, 50, 175, 175, 95, 135, 110, 135, 105, scald, iceBeam, thunder, focusBlast);
    pokemonList["Zapdos"] = Pokemon("Zapdos", Type::Electric, Type::Flying, 50, 165, 165, 110, 105, 145, 110, 120, thunderBolt, hurricane, thunder, powerGem);
    pokemonList["Zekrom"] = Pokemon("Zekrom", Type::Electric, Type::Dragon, 50, 175, 175, 170, 140, 140, 120, 110, fusionBolt, dragonClaw, poisonJab, ironHead);
}

// Récupère un Pokémon par son nom (retourne un pointeur vers un Pokémon)
Pokemon *PokemonManager::getPokemonByName(const std::string &name)
{
    auto it = pokemonList.find(name);
    if (it != pokemonList.end())
    {
        return &(it->second); // Retourne un pointeur vers le Pokémon trouvé
    }
    return nullptr; // Retourne nullptr si le Pokémon n'est pas trouvé
}

// Obtient la liste de tous les noms de Pokémon
std::vector<std::string> PokemonManager::getAllPokemonNames() const
{
    std::vector<std::string> names;
    for (const auto &pair : pokemonList)
    {
        names.push_back(pair.first); // Ajoute chaque nom de Pokémon à la liste
    }
    return names;
}