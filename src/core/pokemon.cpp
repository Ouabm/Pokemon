#include "pokemon.hpp"

// Constructeur
Pokemon::Pokemon(const std::string &p_name, Type p_type1, Type p_type2, int p_level, int p_hp,
                 float p_attack, float p_specialAttack, float p_defense, float p_specialDefense,
                 float p_speed, const Move &m1, const Move &m2, const Move &m3, const Move &m4)
    : name(p_name), type1(p_type1), type2(p_type2), level(p_level), hp(p_hp), attack(p_attack), specialAttack(p_specialAttack),
      defense(p_defense), specialDefense(p_specialDefense), speed(p_speed), moves{&m1, &m2, &m3, &m4} {}

// Getters
string Pokemon::getName() const { return name; }
Type Pokemon::getType1() const { return type1; }
Type Pokemon::getType2() const { return type2; }
int Pokemon::getHp() const { return hp; }
float Pokemon::getAttack() const { return attack; }
float Pokemon::getSpecialAttack() const { return specialAttack; }
float Pokemon::getDefense() const { return defense; }
float Pokemon::getSpecialDefense() const { return specialDefense; }
float Pokemon::getSpeed() const { return speed; }
vector<const Move *> Pokemon::getMoves() const { return moves; }

// Setters
void Pokemon::setHp(int p_hp) { hp = p_hp; }
void Pokemon::setAttack(float p_attack) { attack = p_attack; }
void Pokemon::setSpecialAttack(float p_specialAttack) { specialAttack = p_specialAttack; }
void Pokemon::setDefense(float p_defense) { defense = p_defense; }
void Pokemon::setSpecialDefense(float p_specialDefense) { specialDefense = p_specialDefense; }
void Pokemon::setSpeed(float p_speed) { speed = p_speed; }

// Tests
bool Pokemon::isKO() const { return hp <= 0; }
