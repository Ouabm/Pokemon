#pragma once

#include "GameState.hpp"
#include "ElementUI.hpp"

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

    std::vector<std::string> blueTeam;
    std::vector<std::string> redTeam;

    void loadPokemonSprites();
    void configureSelectionBox();

    void handlePokemonSelection();
};
