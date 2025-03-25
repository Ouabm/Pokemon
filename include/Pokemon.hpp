#pragma once

#include "Move.hpp"
#include <vector> // Pour std::vector

/**
 * @class Pokemon
 * @brief Représente un Pokémon avec toutes ses caractéristiques de combat
 *
 * Cette classe encapsule les données et comportements d'un Pokémon :
 * - Ses attributs de base (nom, types, niveau)
 * - Ses statistiques de combat (PV, attaque, défense...)
 * - Ses capacités (moves)
 * - Son état actuel (PV restants)
 */
class Pokemon
{
protected:
    std::string name;        ///< Nom du Pokémon
    Type type1;              ///< Type primaire (ex: Fire, Water)
    Type type2;              ///< Type secondaire (Type::None si absent)
    int level;               ///< Niveau (1-100)
    int hp;                  ///< Points de vie maximum
    int hpRestant;           ///< Points de vie actuels
    float attack;            ///< Attaque physique
    float specialAttack;     ///< Attaque spéciale
    float defense;           ///< Défense physique
    float specialDefense;    ///< Défense spéciale
    float speed;             ///< Vitesse (détermine l'ordre d'attaque)
    std::vector<const Move*> moves; ///< Liste des 4 capacités connues

public:
    // ========================== CONSTRUCTEURS ========================== //

    /**
     * @brief Constructeur par défaut
     * 
     * Crée un Pokémon "vide" avec :
     * - Nom "Unknown"
     * - Aucun type
     * - Niveau 0
     * - Toutes stats à 0
     * - Aucune capacité
     */
    Pokemon()
        : name("Unknown"), type1(Type::None), type2(Type::None), level(0), hp(0), hpRestant(0),
          attack(0), specialAttack(0), defense(0), specialDefense(0), speed(0)
    {
        moves = {nullptr, nullptr, nullptr, nullptr};
    }

    /**
     * @brief Constructeur complet
     * @param p_name Nom du Pokémon
     * @param p_type1 Type primaire
     * @param p_type2 Type secondaire (Type::None si absent)
     * @param p_level Niveau (1-100)
     * @param p_hp Points de vie maximum
     * @param p_hpRestant Points de vie actuels
     * @param p_attack Attaque physique
     * @param p_specialAttack Attaque spéciale
     * @param p_defense Défense physique
     * @param p_specialDefense Défense spéciale
     * @param p_speed Vitesse
     * @param m1 Première capacité
     * @param m2 Deuxième capacité
     * @param m3 Troisième capacité
     * @param m4 Quatrième capacité
     *
     * Crée un Pokémon avec toutes ses caractéristiques initialisées.
     * Les PV restants sont généralement égaux aux PV max au départ.
     */
    Pokemon(const std::string &p_name, Type p_type1, Type p_type2, int p_level, int p_hp, int p_hpRestant,
            float p_attack, float p_specialAttack, float p_defense, float p_specialDefense,
            float p_speed, const Move &m1, const Move &m2, const Move &m3, const Move &m4)
        : name(p_name), type1(p_type1), type2(p_type2), level(p_level), hp(p_hp), hpRestant(p_hpRestant),
          attack(p_attack), specialAttack(p_specialAttack), defense(p_defense), specialDefense(p_specialDefense),
          speed(p_speed)
    {
        moves = {&m1, &m2, &m3, &m4};
    }

    // ========================== GETTERS ========================== //

    std::string getName() const { return name; }          ///< @return Nom du Pokémon
    Type getType1() const { return type1; }              ///< @return Type primaire
    Type getType2() const { return type2; }              ///< @return Type secondaire
    int getHp() const { return hp; }                     ///< @return PV maximum
    int getHpRestant() const { return hpRestant; }       ///< @return PV actuels
    float getAttack() const { return attack; }           ///< @return Attaque physique
    float getSpecialAttack() const { return specialAttack; } ///< @return Attaque spéciale
    float getDefense() const { return defense; }         ///< @return Défense physique
    float getSpecialDefense() const { return specialDefense; } ///< @return Défense spéciale
    float getSpeed() const { return speed; }             ///< @return Vitesse
    std::vector<const Move*> getMoves() const { return moves; } ///< @return Liste des capacités

    // ========================== SETTERS ========================== //

    void setHp(int p_hp) { hp = p_hp; }                         ///< @param p_hp Nouveaux PV maximum
    void setHpRestant(int p_hpRestant) { hpRestant = p_hpRestant; } ///< @param p_hpRestant PV actuels
    void setAttack(float p_attack) { attack = p_attack; }       ///< @param p_attack Nouvelle attaque
    void setSpecialAttack(float p_specialAttack) { specialAttack = p_specialAttack; } ///< @param p_specialAttack Nouvelle attaque spéciale
    void setDefense(float p_defense) { defense = p_defense; }   ///< @param p_defense Nouvelle défense
    void setSpecialDefense(float p_specialDefense) { specialDefense = p_specialDefense; } ///< @param p_specialDefense Nouvelle défense spéciale
    void setSpeed(float p_speed) { speed = p_speed; }           ///< @param p_speed Nouvelle vitesse

    // ========================== METHODES ========================== //

    /**
     * @brief Vérifie si le Pokémon est K.O.
     * @return true si les PV sont <= 0, false sinon
     */
    bool isKO() const { return hpRestant <= 0; }

    /**
     * @brief Crée une copie profonde du Pokémon
     * @return Pointeur vers une nouvelle instance identique
     *
     * @note La responsabilité de la destruction revient à l'appelant
     */
    Pokemon* clone() const
    {
        return new Pokemon(name, type1, type2, level, hp, hpRestant, 
                         attack, specialAttack, defense, specialDefense, speed,
                         *moves[0], *moves[1], *moves[2], *moves[3]);
    }
};