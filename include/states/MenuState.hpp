#pragma once

#include "GameState.hpp"
#include "ElementUI.hpp"  // Inclut les éléments d'interface utilisateur

class MenuState : public GameState
{
public:
    // Constructeur : Nécessite un GameStateManager pour manipuler les transitions d'état.
    MenuState(GameStateManager *manager);  

    void handleInput(sf::RenderWindow &window) override; 
    void update() override; 
    void render(sf::RenderWindow &window) override;

private:
    // Membres pour l'arrière-plan et les boutons de l'interface utilisateur.
    sf::Sprite backgroundSprite;  
    sf::Font font;              

    // Trois boutons pour naviguer dans le menu.
    Button startButton;
    Button helpButton;
    Button quitButton;

    // Méthodes internes pour gérer les boutons.
    void createMenuButtons();
    void handleButtonClick(const sf::Vector2f &mousePos, sf::RenderWindow &window); // Détecte les clics sur les boutons.

    void drawButton(const Button &button, sf::RenderWindow &window); // Fonction à généraliser plus tard.
};
