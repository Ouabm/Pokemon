#pragma once

#include "GameState.hpp"
#include "ElementUI.hpp"

struct TeamSelectionStruct
{
    std::vector<sf::RectangleShape> selectedBoxes; // Boîtes de sélection des Pokémon
    sf ::RectangleShape currentBox;
    std::vector<std::string> pokemonNames; // Noms des Pokémon dans l'équipe
    int selectionIndex = 0;                // Indice du Pokémon sélectionné
    bool isReady = false;
};

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

    TeamSelectionStruct redTeamSelection;  // Struct pour l'équipe rouge
    TeamSelectionStruct blueTeamSelection; // Struct pour l'équipe bleue

    void loadAllPokemonSprites();
    void handlePokemonSelection(TeamSelectionStruct &teamSelection);
};
