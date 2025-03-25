#pragma once

#include "GameState.hpp"
#include "ElementUI.hpp"

// ============================== CLASSE ENDSTATE ============================== //

/**
 * @class EndState
 * @brief État de fin de jeu, affichant l'écran de conclusion et les options disponibles
 * 
 * Cette classe gère l'écran de fin du jeu qui s'affiche lorsqu'une partie est terminée.
 * Elle permet au joueur de choisir entre rejouer ou quitter l'application.
 * Hérite de GameState pour s'intégrer dans le système d'états du jeu.
 */
class EndState : public GameState
{
public:
    /**
     * @brief Constructeur de la classe EndState
     * @param manager Pointeur vers le gestionnaire d'états du jeu
     * @param winner Chaîne de caractères indiquant le gagnant (pour l'affichage)
     */
    EndState(GameStateManager *manager, const std::string winner);

    // ========================== MÉTHODES PRINCIPALES ========================== //
    
    /**
     * @brief Gère les entrées utilisateur (souris/clavier)
     * @param window Fenêtre SFML pour la capture des événements
     */
    void handleInput(sf::RenderWindow &window) override;
    
    /**
     * @brief Met à jour la logique de l'état à chaque frame
     * 
     * Gère les animations, transitions et vérifie les interactions avec les boutons
     */
    void update() override;
    
    /**
     * @brief Dessine tous les éléments de l'écran de fin
     * @param window Fenêtre SFML pour le rendu graphique
     */
    void render(sf::RenderWindow &window) override;

private:
    // ============================== ÉLÉMENTS GRAPHIQUES ============================== //
    sf::Sprite backgroundSprite; ///< Sprite pour l'arrière-plan de l'écran de fin
    sf::Text endText;            ///< Texte affichant le message de fin (victoire/défaite)

    // ============================== BOUTONS ============================== //
    Button replayButton; ///< Bouton "Rejouer" pour relancer une nouvelle partie
    Button quitButton;   ///< Bouton "Quitter" pour fermer l'application

    // ============================== GESTION DU TEMPS ============================== //
    sf::Clock clock; ///< Chronomètre pour gérer les animations et effets temporels
};