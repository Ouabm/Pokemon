#ifndef MOVE_HPP
#define MOVE_HPP

#include <iostream>
#include <string>
#include <vector>

#include "type.hpp"

using namespace std;

class Move
{
private:
    string name;  // Nom du mouvement
    Type type;    // Type du mouvement (ex : Fire, Water, Normal, etc.)
    int power;    // Puissance du mouvement
    int accuracy; // Précision du mouvement (valeur entre 0 et 100)
    bool isPhysical;

public:
    // Constructeur
    Move(const string &p_name = "Unnamed Move", Type p_type = Type::Normal,
         int p_power = 0, int p_accuracy = 100, string)
        : name(p_name), type(p_type), power(p_power), accuracy(p_accuracy) {}

    // Getters
    string getName() const { return name; }
    Type getType() const { return type; }
    int getPower() const { return power; }
    int getAccuracy() const { return accuracy; }
    int isPhysical() const { return 0; } // A completer

    // Méthode pour afficher les informations d'un mouvement
    void displayMoveInfo() const
    {
        cout << "Move: " << name << "\n";
        cout << "Type: " << typeToString(type) << "\n"; // Type converti en string pour affichage
        cout << "Power: " << power << "\n";
        cout << "Accuracy: " << accuracy << "%" << endl;
    }
};

#endif // MOVE_HPP
