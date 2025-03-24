#pragma once

#include "GameState.hpp"
#include "ElementUI.hpp"

// ============================== CLASSE ENDSTATE ============================== //
// Gère l'écran de fin du jeu, permettant au joueur de rejouer ou de quitter
class EndState : public GameState
{
public:
    EndState(GameStateManager *manager); // Constructeur

    // ========================== MÉTHODES PRINCIPALES ========================== //
    void handleInput(sf::RenderWindow &window) override; // Gestion des entrées utilisateur
    void update() override;                              // Mise à jour de l'état de fin
    void render(sf::RenderWindow &window) override;      // Affichage de l'écran de fin

private:
    // ============================== ÉLÉMENTS GRAPHIQUES ============================== //
    sf::Sprite backgroundSprite; // Fond d'écran de l'écran de fin
    sf::Text endText;            // Texte affichant "Fin du jeu"

    // ============================== BOUTONS ============================== //
    Button replayButton; // Bouton permettant de rejouer
    Button quitButton;   // Bouton permettant de quitter le jeu

    // ============================== GESTION DU TEMPS ============================== //
    sf::Clock clock; // Chronomètre pour gérer les transitions ou effets de fin
};
