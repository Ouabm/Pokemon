#pragma once

#include "Move.hpp"
#include <vector> // Pour stocker les moves

class Pokemon
{
protected:
    std::string name;
    Type type1;
    Type type2;
    int level;
    int hp;
    int hpRestant;
    float attack, specialAttack;
    float defense, specialDefense;
    float speed;
    std::vector<const Move *> moves; // Liste des mouvements

public:
    // Constructeur par défaut
    Pokemon()
        : name("Unknown"), type1(Type::None), type2(Type::None), level(0), hp(0), hpRestant(0),
          attack(0), specialAttack(0), defense(0), specialDefense(0), speed(0)
    {
        moves = {nullptr, nullptr, nullptr, nullptr}; // Aucune attaque par défaut
    }

    // Constructeur avec arguments
    Pokemon(const std::string &p_name, Type p_type1, Type p_type2, int p_level, int p_hp, int p_hpRestant,
            float p_attack, float p_specialAttack, float p_defense, float p_specialDefense,
            float p_speed, const Move &m1, const Move &m2, const Move &m3, const Move &m4)
        : name(p_name), type1(p_type1), type2(p_type2), level(p_level), hp(p_hp), hpRestant(p_hpRestant),
          attack(p_attack), specialAttack(p_specialAttack), defense(p_defense), specialDefense(p_specialDefense),
          speed(p_speed)
    {
        moves = {&m1, &m2, &m3, &m4};
    }

    // Getters
    std::string getName() const { return name; }
    Type getType1() const { return type1; }
    Type getType2() const { return type2; }
    int getHp() const { return hp; }
    int getHpRestant() const { return hpRestant; }
    float getAttack() const { return attack; }
    float getSpecialAttack() const { return specialAttack; }
    float getDefense() const { return defense; }
    float getSpecialDefense() const { return specialDefense; }
    float getSpeed() const { return speed; }
    std::vector<const Move *> getMoves() const { return moves; }

    // Setters
    void setHp(int p_hp) { hp = p_hp; }
    void setHpRestant(int p_hpRestant) { hpRestant = p_hpRestant; }
    void setAttack(float p_attack) { attack = p_attack; }
    void setSpecialAttack(float p_specialAttack) { specialAttack = p_specialAttack; }
    void setDefense(float p_defense) { defense = p_defense; }
    void setSpecialDefense(float p_specialDefense) { specialDefense = p_specialDefense; }
    void setSpeed(float p_speed) { speed = p_speed; }

    // Tests
    bool isKO() const { return hpRestant <= 0; }

    // Clone function
    Pokemon *clone() const
    {
        return new Pokemon(name, type1, type2, level, hp, hpRestant, attack, specialAttack, defense, specialDefense, speed,
                           *moves[0], *moves[1], *moves[2], *moves[3]); // Crée une copie de l'objet
    }
};
