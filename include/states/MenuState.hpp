#pragma once

#include "GameState.hpp"
#include "ElementUI.hpp" // Inclut les éléments d'interface utilisateur

// =============================== CLASSE MENUSTATE =============================== //
// Représente le menu principal du jeu avec des boutons pour naviguer entre les états.
class MenuState : public GameState
{
public:
    // ========================== CONSTRUCTEUR ========================== //
    MenuState(GameStateManager *manager); // Nécessite un GameStateManager pour gérer les transitions

    // ========================== MÉTHODES PRINCIPALES ========================== //
    void handleInput(sf::RenderWindow &window) override; // Gestion des entrées utilisateur
    void update() override;                              // Mise à jour des éléments du menu
    void render(sf::RenderWindow &window) override;      // Affichage du menu à l'écran

private:
    // ========================== ÉLÉMENTS GRAPHIQUES ========================== //
    sf::Sprite backgroundSprite; // Fond d'écran du menu
    sf::Font font;               // Police d'écriture utilisée pour le menu

    // ========================== BOUTONS DU MENU ========================== //
    Button startButton; // Bouton pour commencer une partie
    Button helpButton;  // Bouton pour afficher l'aide
    Button quitButton;  // Bouton pour quitter le jeu

    // ========================== MÉTHODES INTERNES ========================== //
    void createMenuButtons();                                                       // Initialise les boutons du menu
    void handleButtonClick(const sf::Vector2f &mousePos, sf::RenderWindow &window); // Gère les clics sur les boutons
    void drawButton(const Button &button, sf::RenderWindow &window);                // Affiche un bouton à l'écran
    void showHelpWindow();
};
