#include "PokemonManager.hpp"

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
    pokemonList["Arceus"] = Pokemon("Arceus", Type::Normal, Type::None, 50, 195, 195, 140, 140, 140, 140, 140, Judgment, Earth_Power, Gunk_Shot, Sacred_Sword);
    pokemonList["Articuno"] = Pokemon("Articuno", Type::Ice, Type::Flying, 50, 165, 165, 105, 120, 115, 145, 105, Ice_Beam, Fly, Scald, Hurricane);
    pokemonList["Charizard"] = Pokemon("Charizard", Type::Fire, Type::Flying, 50, 153, 153, 104, 98, 129, 105, 120, Flamethrower, Fly, DragonClaw, Hurricane);
    pokemonList["Dialga"] = Pokemon("Dialga", Type::Steel, Type::Dragon, 50, 175, 175, 140, 140, 170, 120, 110, Draco_Meteor, Dragon_Pulse, Flash_Cannon, Flamethrower);
    pokemonList["Entei"] = Pokemon("Entei", Type::Fire, Type::None, 50, 190, 190, 135, 105, 110, 95, 120, Fire_Blast, Fire_Punch, Wild_Charge, Slash);
    pokemonList["Giratina"] = Pokemon("Giratina", Type::Dragon, Type::Ghost, 50, 225, 225, 120, 140, 120, 140, 110, Fire_Blast, Poltergeist, Draco_Meteor, DragonClaw);
    pokemonList["Groudon"] = Pokemon("Groudon", Type::Ground, Type::None, 50, 175, 175, 170, 160, 120, 110, 110, Fire_Punch, Precipice_Blades, Lands_Wrath, Stone_Edge);
    pokemonList["Ho-Oh"] = Pokemon("Ho-Oh", Type::Fire, Type::Flying, 50, 181, 181, 150, 110, 130, 174, 110, Sacred_Fire, Fly, Foul_Play, Play_Rough);
    pokemonList["Kyogre"] = Pokemon("Kyogre", Type::Water, Type::None, 50, 175, 175, 120, 110, 170, 160, 110, Origin_Pulse, Ice_Beam, Thunder, Scald);
    pokemonList["Lugia"] = Pokemon("Lugia", Type::Psychic, Type::Flying, 50, 181, 181, 110, 150, 110, 174, 130, Aeroblast, Psychics, Fiery_Wrath, Fly);
    pokemonList["Mewtwo"] = Pokemon("Mewtwo", Type::Psychic, Type::None, 50, 181, 181, 130, 110, 174, 110, 150, Psychics, Shadow_Ball, Moonblast, Aura_Sphere);
    pokemonList["Moltres"] = Pokemon("Moltres", Type::Fire, Type::Flying, 50, 165, 165, 120, 110, 145, 105, 110, Flamethrower, Fiery_Wrath, Hurricane, Sludge_Bomb);
    pokemonList["Palkia"] = Pokemon("Palkia", Type::Water, Type::Dragon, 50, 165, 165, 140, 120, 170, 140, 120, Scald, Draco_Meteor, Dragon_Pulse, Ice_Beam);
    pokemonList["Pikachu"] = Pokemon("Pikachu", Type::Electric, Type::None, 50, 110, 110, 75, 60, 70, 70, 110, Thunderbolt, Thunder, Energy_Ball, Moonblast);
    pokemonList["Raikou"] = Pokemon("Raikou", Type::Electric, Type::None, 50, 165, 165, 105, 95, 135, 120, 135, Thunder, Thunderbolt, Shadow_Ball, Focus_Blast);
    pokemonList["Rayquaza"] = Pokemon("Rayquaza", Type::Dragon, Type::Flying, 50, 180, 180, 170, 110, 170, 110, 115, Flamethrower, Aeroblast, DragonClaw, Draco_Meteor);
    pokemonList["Reshiram"] = Pokemon("Reshiram", Type::Fire, Type::Dragon, 50, 175, 175, 140, 120, 170, 140, 110, Fusion_Flare, Draco_Meteor, Dragon_Pulse, Sludge_Bomb);
    pokemonList["Suicune"] = Pokemon("Suicune", Type::Water, Type::None, 50, 175, 175, 95, 135, 110, 135, 105, Scald, Ice_Beam, Thunder, Focus_Blast);
    pokemonList["Zapdos"] = Pokemon("Zapdos", Type::Electric, Type::Flying, 50, 165, 165, 110, 105, 145, 110, 120, Thunderbolt, Hurricane, Thunder, Power_Gem);
    pokemonList["Zekrom"] = Pokemon("Zekrom", Type::Electric, Type::Dragon, 50, 175, 175, 170, 140, 140, 120, 110, Fusion_Bolt, DragonClaw, Poison_Jab, Iron_Head);
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