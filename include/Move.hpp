#pragma once

#include "Type.hpp"
#include <iostream> // Pour la foncion displayInfo

class Move
{
private:
    std::string name; // Nom du mouvement
    Type type;        // Type du mouvement (ex : Fire, Water, Normal, etc.)
    int power;        // Puissance du mouvement
    int accuracy;     // Précision du mouvement (valeur entre 0 et 100)
    bool isPhysical;  // Indique si le mouvement est physique ou spécial

public:
    // Constructeur
    Move(const std::string &p_name = "Unnamed Move", Type p_type = Type::None, int p_power = 0, int p_accuracy = 0, bool p_isPhysical = false)
        : name(p_name), type(p_type), power(p_power), accuracy(p_accuracy), isPhysical(p_isPhysical) {}

    // Getters
    std::string getName() const { return name; }
    Type getType() const { return type; }
    int getPower() const { return power; }
    int getAccuracy() const { return accuracy; }
    bool isPhysicalMove() const { return isPhysical; }

    // Pas besoin de Setters car constant

    // Méthode pour afficher les informations d'un mouvement
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
