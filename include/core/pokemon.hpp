#ifndef POKEMON_HPP
#define POKEMON_HPP

#include <iostream>
#include <string>
#include <vector>
#include "type.hpp"
#include "move.hpp"

using namespace std;

class Pokemon
{
protected:
    string name;
    Type type1;
    Type type2;
    int level;
    int hp;
    float attack, specialAttack;
    float defense, specialDefense;
    float speed;
    vector<const Move *> moves;

public:
    // Constructeur
    Pokemon(const string &p_name, Type p_type1, Type p_type2, int p_level, int p_hp,
            float p_attack, float p_specialAttack, float p_defense, float p_specialDefense,
            float p_speed, const Move &m1, const Move &m2, const Move &m3, const Move &m4);

    // Getters
    string getName() const;
    Type getType1() const;
    Type getType2() const;
    int getHp() const;
    float getAttack() const;
    float getSpecialAttack() const;
    float getDefense() const;
    float getSpecialDefense() const;
    float getSpeed() const;
    vector<const Move *> getMoves() const;

    // Setters
    void setHp(int p_hp);
    void setAttack(float p_attack);
    void setSpecialAttack(float p_specialAttack);
    void setDefense(float p_defense);
    void setSpecialDefense(float p_specialDefense);
    void setSpeed(float p_speed);

    // Tests
    bool isKO() const;
};

#endif // POKEMON_HPP
