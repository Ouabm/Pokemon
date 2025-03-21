#pragma once

#include "GameState.hpp"
#include <SFML/Graphics.hpp>

class BattleState : public GameState
{
public:
    BattleState(GameStateManager *manager);
    void handleInput(sf::RenderWindow &window) override;
    void update() override;
    void render(sf::RenderWindow &window) override;

private:
    sf::Font font;
    sf::Text battleText;
};
