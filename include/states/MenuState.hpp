#pragma once

#include "GameState.hpp"
#include "ElementUI.hpp"

class MenuState : public GameState
{
public:
    MenuState(GameStateManager *manager);
    void handleInput(sf::RenderWindow &window) override;
    void update() override;
    void render(sf::RenderWindow &window) override;

private:
    sf::Sprite backgroundSprite;
    sf::Font font;
    
    Button startButton;
    Button helpButton;
    Button quitButton;

    void createMenuButtons(float mainMenuwindowWidth, float mainMenuwindowHeight, const sf::Vector2f &buttonSize);
    void handleButtonClicks(const sf::Vector2f &mousePos, sf::RenderWindow &window);

    void drawButton(const Button &button, sf::RenderWindow &window); // A generaliser plus tard 
};
