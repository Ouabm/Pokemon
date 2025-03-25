#pragma once  // Version plus moderne des include guards

#include "GameState.hpp"
#include <stack>
#include <memory>  // Pour std::unique_ptr
#include <SFML/Graphics.hpp>

/**
 * @file GameStateManager.hpp
 * @brief Gère la pile des états du jeu et leur transition.
 */

/**
 * @class GameStateManager
 * @brief Classe permettant de gérer les différents états du jeu via une pile.
 */
class GameStateManager
{
public:
    /**
     * @brief Change l'état actuel du jeu.
     * 
     * Cette fonction remplace l'état actuel par un nouvel état en utilisant 
     * un `unique_ptr` pour garantir une gestion propre de la mémoire.
     * 
     * @param newState Pointeur unique vers le nouvel état du jeu.
     */
    void changeState(std::unique_ptr<GameState> newState);

    /**
     * @brief Gère les entrées de l'utilisateur.
     * 
     * Cette fonction détecte et traite les interactions du joueur.
     * 
     * @param window Référence vers la fenêtre SFML où les entrées sont captées.
     */
    void handleInput(sf::RenderWindow &window);

    /**
     * @brief Met à jour l'état actuel du jeu.
     * 
     * Cette fonction appelle la mise à jour de l'état en haut de la pile.
     */
    void update();

    /**
     * @brief Affiche l'état actuel du jeu.
     * 
     * Cette fonction dessine l'état en haut de la pile sur la fenêtre SFML.
     * 
     * @param window Référence vers la fenêtre SFML où l'affichage est effectué.
     */
    void render(sf::RenderWindow &window);

private:
    /**
     * @brief Pile des états du jeu.
     * 
     * Utilisation d'une pile (`std::stack`) pour stocker les différents états 
     * du jeu et permettre la navigation entre eux.
     */
    std::stack<std::unique_ptr<GameState>> states;
};
