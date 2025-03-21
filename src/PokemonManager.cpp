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
    pokemonList["Arceus"] = Pokemon("Arceus", Type::Fire, Type::Flying, 100, 100, 300, 250, 240, 200, 180, 300, flamethrower, fly, dragonClaw, slash);
    pokemonList["Articuno"] = Pokemon("Articuno", Type::Fire, Type::Flying, 100, 100, 300, 250, 240, 200, 180, 300, flamethrower, fly, dragonClaw, slash);
    pokemonList["Charizard"] = Pokemon("Charizard", Type::Fire, Type::Flying, 100, 100, 300, 250, 240, 200, 180, 300, flamethrower, fly, dragonClaw, slash);
    pokemonList["Dialga"] = Pokemon("Dialga", Type::Fire, Type::Flying, 100, 100, 300, 250, 240, 200, 180, 300, flamethrower, fly, dragonClaw, slash);
    pokemonList["Entei"] = Pokemon("Entei", Type::Fire, Type::Flying, 100, 100, 300, 250, 240, 200, 180, 300, flamethrower, fly, dragonClaw, slash);
    pokemonList["Giratina"] = Pokemon("Giratina", Type::Fire, Type::Flying, 100, 100, 300, 250, 240, 200, 180, 300, flamethrower, fly, dragonClaw, slash);
    pokemonList["Groudon"] = Pokemon("Groudon", Type::Fire, Type::Flying, 100, 100, 300, 250, 240, 200, 180, 300, flamethrower, fly, dragonClaw, slash);
    pokemonList["Ho-Oh"] = Pokemon("Ho-Oh", Type::Fire, Type::Flying, 100, 100, 300, 250, 240, 200, 180, 300, flamethrower, fly, dragonClaw, slash);
    pokemonList["Kyogre"] = Pokemon("Kyogre", Type::Fire, Type::Flying, 100, 100, 300, 250, 240, 200, 180, 300, flamethrower, fly, dragonClaw, slash);
    pokemonList["Lugia"] = Pokemon("Lugia", Type::Fire, Type::Flying, 100, 100, 300, 250, 240, 200, 180, 300, flamethrower, fly, dragonClaw, slash);
    pokemonList["Mewtwo"] = Pokemon("Mewtwo", Type::Fire, Type::Flying, 100, 100, 300, 250, 240, 200, 180, 300, flamethrower, fly, dragonClaw, slash);
    pokemonList["Moltres"] = Pokemon("Moltres", Type::Fire, Type::Flying, 100, 100, 300, 250, 240, 200, 180, 300, flamethrower, fly, dragonClaw, slash);
    pokemonList["Palkia"] = Pokemon("Palkia", Type::Fire, Type::Flying, 100, 100, 300, 250, 240, 200, 180, 300, flamethrower, fly, dragonClaw, slash);
    pokemonList["Pikachu"] = Pokemon("Pikachu", Type::Fire, Type::Flying, 100, 100, 300, 250, 240, 200, 180, 300, flamethrower, fly, dragonClaw, slash);
    pokemonList["Raikou"] = Pokemon("Raikou", Type::Fire, Type::Flying, 100, 100, 300, 250, 240, 200, 180, 300, flamethrower, fly, dragonClaw, slash);
    pokemonList["Rayquaza"] = Pokemon("Rayquaza", Type::Fire, Type::Flying, 100, 100, 300, 250, 240, 200, 180, 300, flamethrower, fly, dragonClaw, slash);
    pokemonList["Reshiram"] = Pokemon("Reshiram", Type::Fire, Type::Flying, 100, 100, 300, 250, 240, 200, 180, 300, flamethrower, fly, dragonClaw, slash);
    pokemonList["Suicune"] = Pokemon("Suicune", Type::Fire, Type::Flying, 100, 100, 300, 250, 240, 200, 180, 300, flamethrower, fly, dragonClaw, slash);
    pokemonList["Zapdos"] = Pokemon("Zapdos", Type::Fire, Type::Flying, 100, 100, 300, 250, 240, 200, 180, 300, flamethrower, fly, dragonClaw, slash);
    pokemonList["Zekrom"] = Pokemon("Zekrom", Type::Fire, Type::Flying, 100, 100, 300, 250, 240, 200, 180, 300, flamethrower, fly, dragonClaw, slash);
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