#pragma once

#include "Type.hpp"
#include <iostream> // Pour std::cout dans displayMoveInfo

/**
 * @class Move
 * @brief Représente une attaque/technique que peut utiliser un Pokémon
 *
 * Cette classe encapsule toutes les caractéristiques d'un mouvement Pokémon :
 * - Son nom et son type
 * - Ses caractéristiques de combat (puissance, précision)
 * - Sa catégorie (physique/spécial)
 */
class Move
{
private:
    std::string name; ///< Nom du mouvement (ex: "Flamethrower", "Hydro Pump")
    Type type;        ///< Type élémentaire du mouvement (ex: Fire, Water)
    int power;        ///< Puissance de base du mouvement (0 si mouvement de statut)
    int accuracy;     ///< Chance de toucher (0-100), 0 signifie "jamais rate"
    bool isPhysical;  ///< True = mouvement physique, False = mouvement spécial

public:
    /**
     * @brief Constructeur complet
     * @param p_name Nom du mouvement ("Unnamed Move" par défaut)
     * @param p_type Type élémentaire (Type::None par défaut)
     * @param p_power Puissance (0 par défaut)
     * @param p_accuracy Précision (0-100, 0 par défaut)
     * @param p_isPhysical Catégorie physique (false par défaut)
     *
     * Crée un mouvement avec toutes ses caractéristiques de combat.
     * Un mouvement avec puissance 0 est considéré comme un mouvement de statut.
     */
    Move(const std::string &p_name = "Unnamed Move", 
         Type p_type = Type::None, 
         int p_power = 0, 
         int p_accuracy = 0, 
         bool p_isPhysical = false)
        : name(p_name), type(p_type), power(p_power), 
          accuracy(p_accuracy), isPhysical(p_isPhysical) {}

    // ========================== GETTERS ========================== //

    /**
     * @brief Getter pour le nom
     * @return Nom du mouvement
     */
    std::string getName() const { return name; }

    /**
     * @brief Getter pour le type
     * @return Type élémentaire du mouvement
     */
    Type getType() const { return type; }

    /**
     * @brief Getter pour la puissance
     * @return Puissance de base du mouvement
     */
    int getPower() const { return power; }

    /**
     * @brief Getter pour la précision
     * @return Valeur de précision (0-100)
     */
    int getAccuracy() const { return accuracy; }

    /**
     * @brief Détermine si le mouvement est physique
     * @return true si mouvement physique, false si spécial
     */
    bool isPhysicalMove() const { return isPhysical; }

    // ========================== METHODES UTILITAIRES ========================== //

    /**
     * @brief Affiche les informations du mouvement dans la console
     *
     * Format d'affichage :
     * Move: [name]
     * Type: [type] 
     * Power: [power]
     * Accuracy: [accuracy]%
     * Physical: Yes/No
     */
    void displayMoveInfo() const
    {
        std::cout << "Move: " << name << "\n"
                  << "Type: " << typeToString(type) << "\n"
                  << "Power: " << power << "\n"
                  << "Accuracy: " << accuracy << "%\n"
                  << "Physical: " << (isPhysical ? "Yes" : "No") << "\n"
                  << std::endl;
    }
};