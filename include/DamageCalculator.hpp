#pragma once 
#include <array>
#include "Pokemon.hpp"

constexpr std::array<std::array<float, 18>, 18> tableType = {{
    {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 0.0, 1.0, 1.0, 0.5, 1.0},
    {1.0, 0.5, 0.5, 2.0, 1.0, 1.0, 1.0, 0.5, 2.0, 0.5, 1.0, 0.5, 2.0, 1.0, 0.5, 1.0, 0.5, 1.0},
    {1.0, 2.0, 0.5, 0.5, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 0.5, 1.0, 2.0, 1.0},
    {1.0, 0.5, 2.0, 0.5, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 1.0, 1.0},
    {1.0, 0.5, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 0.0, 2.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0},
    {1.0, 2.0, 0.5, 0.5, 1.0, 0.5, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0},
    {2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 0.5, 0.5, 0.5, 2.0, 0.0, 1.0, 2.0, 2.0, 0.5},
    {1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 0.5, 1.0, 1.0, 1.0, 0.5, 0.5, 1.0, 1.0, 0.0, 2.0},
    {1.0, 0.5, 2.0, 1.0, 2.0, 1.0, 1.0, 2.0, 1.0, 0.0, 1.0, 0.5, 2.0, 1.0, 1.0, 1.0, 2.0, 1.0},
    {1.0, 2.0, 1.0, 1.0, 0.5, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 0.5, 1.0},
    {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 0.0, 0.5, 1.0},
    {1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 0.5, 0.5, 1.0, 0.5, 2.0, 1.0, 1.0, 0.5, 1.0, 2.0, 0.5, 0.5},
    {1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 0.5, 2.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0},
    {0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 0.0},
    {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 0.5},
    {1.0, 1.0, 0.5, 0.5, 0.5, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 0.5, 2.0},
    {1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 0.5, 1.0}
}};

constexpr float typeDamage(int attack, int def_1, int def_2) {
    return (def_2 != 18) ? tableType[attack][def_1] * tableType[attack][def_2] : tableType[attack][def_1];
}

int calculDamage(Pokemon pokemon_atk, Pokemon pokemon_def, Move move){
    int min1 = 0 ,  max1 = 15;
    int min2 = 1 ,  max2 = 100;

    int randomInRange = min1 + std::rand() % (max1 - min1 + 1);
    int accuracy = min2 + std::rand() % (max2 - min2 + 1);
    if (accuracy>move.getAccuracy()){
        return 0;
    }
    int role = 85 + std::rand() % (max1 - min1 + 1);
    float crit = randomInRange == 15 ? 1.5 : 1;
    float STAB = ((move.getType() == pokemon_atk.getType1()) || (move.getType() == pokemon_atk.getType2())) ? 1.5 : 1;
    if (move.isPhysicalMove()){
        return ((((50*0.4+2)*pokemon_atk.getAttack()*move.getPower())/(pokemon_def.getDefense()*50))*STAB*typeDamage(typeToInt(move.getType()),typeToInt(pokemon_def.getType1()),typeToInt(pokemon_def.getType2()))*crit*(role/100.0));
    }
    else {
        return ((((50*0.4+2)*pokemon_atk.getSpecialAttack()*move.getPower())/(pokemon_def.getSpecialDefense()*50))*STAB*typeDamage(typeToInt(move.getType()),typeToInt(pokemon_def.getType1()),typeToInt(pokemon_def.getType2()))*crit*(role/100.0));
    }
}
