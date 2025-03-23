#pragma once // Version plus moderne des guardians #indef et #endif

#include "GameState.hpp"
#include <stack> 

class GameStateManager
{
public:
    // Fonction permettant de changer l'état actuel du jeu. Elle prend un unique_ptr vers le nouvel état.
    // Cela permet de gérer dynamiquement les états en les manipulant par pointeur sans risque de fuites de mémoire.
    void changeState(std::unique_ptr<GameState> newState);

    void handleInput(sf::RenderWindow &window);
    void update();
    void render(sf::RenderWindow &window);

private:
    // Utilisation d'une pile pour stocker les états du jeu, permettant de naviguer entre eux.
    std::stack<std::unique_ptr<GameState>> states;
};
