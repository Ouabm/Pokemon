#pragma once

#include "GameState.hpp"
#include "ElementUI.hpp"

#include "Pokemon.hpp"

class BattleState : public GameState
{
public:
    // Modification pour accepter les noms des Pokémon (std::string) au lieu de pointeurs
    BattleState(GameStateManager *manager, const std::vector<std::string> &redTeamNames, const std::vector<std::string> &blueTeamNames);

    void handleInput(sf::RenderWindow &window) override;
    void update() override;
    void render(sf::RenderWindow &window) override;

private:
    sf::Sprite backgroundSprite;
    sf::Font font;

    std::vector<Button> moveButtons;


    // Méthode pour charger les Pokémon à partir des noms
    // void loadPokemonTeams(const std::vector<std::string>& redTeamNames, const std::vector<std::string>& blueTeamNames);
};
