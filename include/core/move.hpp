#ifndef MOVE_HPP
#define MOVE_HPP

#include <iostream>
#include <string>
#include <vector>

#include "type.hpp"

class Move
{
private:
    std::string name;     // Nom du mouvement
    Type type;            // Type du mouvement (ex : Fire, Water, Normal, etc.)
    int power;            // Puissance du mouvement
    int accuracy;         // Précision du mouvement (valeur entre 0 et 100)

public:
    // Constructeur
    Move(const std::string &p_name = "Unnamed Move", Type p_type = Type::Normal, 
         int p_power = 0, int p_accuracy = 100)
        : name(p_name), type(p_type), power(p_power), accuracy(p_accuracy) {}

    // Getters
    std::string getName() const { return name; }
    Type getType() const { return type; }
    int getPower() const { return power; }
    int getAccuracy() const { return accuracy; }

    // Setters
    void setName(const std::string &p_name) { name = p_name; }
    void setType(Type p_type) { type = p_type; }
    void setPower(int p_power) { power = p_power; }
    void setAccuracy(int p_accuracy) { accuracy = p_accuracy; }

    // Méthode pour afficher les informations d'un mouvement
    void displayMoveInfo() const
    {
        std::cout << "Move: " << name << "\n";
        std::cout << "Type: " << typeToString(type) << "\n";  // Type converti en string pour affichage
        std::cout << "Power: " << power << "\n";
        std::cout << "Accuracy: " << accuracy << "%" << std::endl;
    }
};

#endif // MOVE_HPP
