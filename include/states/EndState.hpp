#pragma once

#include "GameState.hpp"
#include "ElementUI.hpp"

class EndState : public GameState
{
public:
    EndState(GameStateManager *manager);

    void handleInput(sf::RenderWindow &window) override;
    void update() override;
    void render(sf::RenderWindow &window) override;

private:
    sf::Sprite backgroundSprite;
    sf::Font font;

    sf::Text endText;
    sf::Text yo;

    sf::Clock clock;

    Button replayButton;
    Button quitButton;

};