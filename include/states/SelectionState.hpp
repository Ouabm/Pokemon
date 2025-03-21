#pragma once

#include "GameState.hpp"

#include "../../include/states/BattleState.hpp"

#include "../../include/GameStateManager.hpp"
#include "../../include/PokemonManager.hpp"

#include "../../include/ElementUI.hpp"

class SelectionState : public GameState
{
public:
    SelectionState(GameStateManager *manager);
    void handleInput(sf::RenderWindow &window) override;
    void update() override;
    void render(sf::RenderWindow &window) override;

private:
    sf::Sprite backgroundSprite;

    // Vecteur pour stocker les sprites des Pokémon
    std::vector<sf::Sprite> pokemonSprites;
};