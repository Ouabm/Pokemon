#pragma once

#include "GameState.hpp"
#include "ElementUI.hpp" // Inclut les éléments d'interface utilisateur

// =============================== CLASSE MENUSTATE =============================== //

/**
 * @class MenuState
 * @brief État du menu principal du jeu, gérant la navigation entre les différents états
 *
 * Cette classe représente l'écran principal du jeu avec les options de démarrage,
 * d'aide et de sortie. Elle hérite de GameState pour s'intégrer dans le système
 * de gestion des états du jeu.
 */
class MenuState : public GameState
{
public:
    // ========================== CONSTRUCTEUR ========================== //
    
    /**
     * @brief Constructeur de MenuState
     * @param manager Pointeur vers le gestionnaire d'états du jeu
     * 
     * Initialise l'état du menu et crée tous les éléments d'interface nécessaires.
     */
    MenuState(GameStateManager *manager);

    // ========================== MÉTHODES PRINCIPALES ========================== //
    
    /**
     * @brief Gère les entrées utilisateur (clavier/souris)
     * @param window Fenêtre SFML pour la capture des événements
     */
    void handleInput(sf::RenderWindow &window) override;
    
    /**
     * @brief Met à jour la logique du menu à chaque frame
     * 
     * Gère les animations, effets visuels et vérifie l'état des boutons
     */
    void update() override;
    
    /**
     * @brief Dessine tous les éléments du menu
     * @param window Fenêtre SFML pour le rendu graphique
     */
    void render(sf::RenderWindow &window) override;

private:
    // ========================== ÉLÉMENTS GRAPHIQUES ========================== //
    sf::Sprite backgroundSprite; ///< Sprite pour l'arrière-plan du menu principal
    sf::Font font;               ///< Police utilisée pour le texte du menu

    // ========================== BOUTONS DU MENU ========================== //
    Button startButton; ///< Bouton "Commencer" pour démarrer une nouvelle partie
    Button helpButton;  ///< Bouton "Aide" pour afficher les instructions
    Button quitButton;  ///< Bouton "Quitter" pour fermer l'application

    // ========================== MÉTHODES INTERNES ========================== //
    
    /**
     * @brief Initialise et configure les boutons du menu
     * 
     * Positionne les boutons, définit leurs textes et leurs apparences
     */
    void createMenuButtons();
    
    /**
     * @brief Gère les clics de souris sur les boutons
     * @param mousePos Position actuelle de la souris
     * @param window Fenêtre SFML pour les éventuelles transitions
     */
    void handleButtonClick(const sf::Vector2f &mousePos, sf::RenderWindow &window);
    
    /**
     * @brief Dessine un bouton dans la fenêtre
     * @param button Bouton à afficher
     * @param window Fenêtre SFML pour le rendu
     */
    void drawButton(const Button &button, sf::RenderWindow &window);
    
    /**
     * @brief Affiche une fenêtre d'aide avec les instructions du jeu
     * 
     * Crée et montre une fenêtre modale contenant les informations d'aide
     */
    void showHelpWindow();
};