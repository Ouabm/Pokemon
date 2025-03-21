#pragma once

#include "GameState.hpp"
#include "../../include/states/BattleState.hpp"
#include "../../include/GameStateManager.hpp"
#include "../../include/PokemonManager.hpp"
#include "../../include/ElementUI.hpp"
#include <memory>  // pour std::shared_ptr

class SelectionState : public GameState
{
public:
    SelectionState(GameStateManager *manager);
    void handleInput(sf::RenderWindow &window) override;
    void update() override;
    void render(sf::RenderWindow &window) override;

private:
    sf::Sprite backgroundSprite;
    std::vector<sf::Sprite> pokemonSprites;

    sf::RectangleShape selectionBox;
    int selectedIndex;
    
    bool playerTurn;

    std::vector<std::string> redTeam;
    std::vector<std::string>  blueTeam; 
};
