#include "GameStateManager.hpp"
#include <iostream>

// =============================================================================
// La méthode changeState
// =============================================================================
// Description:
// Cette méthode permet de remplacer l'état actuel du jeu par un nouvel état.
// Elle prend en paramètre un std::unique_ptr vers un nouvel état (GameState).

// Explication détaillée:
// 1. `if (!states.empty())` :
//    Vérifie si la pile des états n'est pas vide. Si c'est le cas, l'état actuel est retiré de la pile avec `states.pop()`.
//    Cela permet de supprimer l'état précédent avant de charger un nouvel état.
// 2. `states.push(std::move(newState))` :
//    On pousse le nouvel état dans la pile. Utilisation de `std::move` pour transférer la propriété du `unique_ptr`
//    sans faire de copie, ce qui rend l'opération plus efficace et garantit une gestion correcte de la mémoire.

void GameStateManager::changeState(std::unique_ptr<GameState> newState)
{
    if (!states.empty())
    {
        states.pop(); // Retirer l'état actuel
    }
    states.push(std::move(newState)); // Ajouter le nouvel état
}

// =============================================================================
// La méthode handleInput
// =============================================================================
// Description:
// Cette méthode permet de gérer les entrées de l'utilisateur (clavier, souris, etc.)
// pour l'état actuel du jeu.

// Explication détaillée:
// 1. `if (!states.empty())` :
//    Vérifie si la pile des états n'est pas vide. Si c'est le cas, on appelle la méthode `handleInput()` de l'état actuel
//    via `states.top()->handleInput(window)`. Cela permet de gérer les entrées de l'utilisateur pour l'état actif.
// 2. `else` :
//    Si la pile est vide (c'est-à-dire qu'il n'y a aucun état actif), un message d'erreur est affiché dans la console.
//    Cela permet de protéger le programme contre des appels invalides lorsque aucun état n'est disponible pour traiter les entrées.

void GameStateManager::handleInput(sf::RenderWindow &window)
{
    if (!states.empty())
    {
        states.top()->handleInput(window); // Gérer l'entrée de l'utilisateur
    }
    else
    {
        std::cerr << "Error: No states to handle input!" << std::endl; // Protection si la pile est vide
    }
}

// =============================================================================
// La méthode update
// =============================================================================
// Description:
// Pareil que pour handleInput

void GameStateManager::update()
{
    if (!states.empty())
    {
        states.top()->update(); // Mettre à jour l'état actuel
    }
    else
    {
        std::cerr << "Error: No states to update!" << std::endl; // Protection si la pile est vide
    }
}

// =============================================================================
// La méthode render
// =============================================================================
// Description:
// Pareil que pour handleInput

void GameStateManager::render(sf::RenderWindow &window)
{
    if (!states.empty())
    {
        states.top()->render(window); // Rendre l'état actuel
    }
    else
    {
        std::cerr << "Error: No states to render!" << std::endl; // Protection si la pile est vide
    }
}
