#ifndef TYPE_HPP
#define TYPE_HPP

#include <string>

enum class Type
{
    Normal,
    Grass,
    Fire,
    Water,
    Electric,
    Ice,
    Fight,
    Poison,
    Ground,
    Flying,
    Psychic,
    Bug,
    Rock,
    Ghost,
    Dragon,
    Dark,
    Steel,
    Fairy,
    None
};

// Fonctions utilitaires
std::string typeToString(Type t);
int typeToInt(Type t);

#endif // TYPE_HPP