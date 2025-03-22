#include "Type.hpp"

std::string typeToString(Type t)
{
    switch (t)
    {
    case Type::Normal: return "Normal";
    case Type::Grass: return "Grass";
    case Type::Fire: return "Fire";
    case Type::Water: return "Water";
    case Type::Electric: return "Electric";
    case Type::Ice: return "Ice";
    case Type::Fighting: return "Fighting";
    case Type::Poison: return "Poison";
    case Type::Ground: return "Ground";
    case Type::Flying: return "Flying";
    case Type::Psychic: return "Psychic";
    case Type::Bug: return "Bug";
    case Type::Rock: return "Rock";
    case Type::Ghost: return "Ghost";
    case Type::Dragon: return "Dragon";
    case Type::Dark: return "Dark";
    case Type::Steel: return "Steel";
    case Type::Fairy: return "Fairy";
    case Type::None: return "None";
    default: return "Unknown";
    }
}

int typeToInt(Type t)
{
    switch (t)
    {
    case Type::Normal: return 0;
    case Type::Grass: return 1;
    case Type::Fire: return 2;
    case Type::Water: return 3;
    case Type::Electric: return 4;
    case Type::Ice: return 5;
    case Type::Fighting: return 6;
    case Type::Poison: return 7;
    case Type::Ground: return 8;
    case Type::Flying: return 9;
    case Type::Psychic: return 10;
    case Type::Bug: return 11;
    case Type::Rock: return 12;
    case Type::Ghost: return 13;
    case Type::Dragon: return 14;
    case Type::Dark: return 15;
    case Type::Steel: return 16;
    case Type::Fairy: return 17;
    case Type::None: return -1;
    default: return -1;
    }
}