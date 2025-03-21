#pragma once

#include "GameState.hpp"
#include "Pokemon.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string> // Pour utiliser std::string

class BattleState : public GameState
{
public:
    // Modification pour accepter les noms des Pokémon (std::string) au lieu de pointeurs
    BattleState(GameStateManager *manager, const std::vector<std::string>& redTeamNames, const std::vector<std::string>& blueTeamNames);

    void handleInput(sf::RenderWindow &window) override;
    void update() override;
    void render(sf::RenderWindow &window) override;

private:
    sf::Font font;
    sf::Text battleText;
    
    // std::vector<Pokemon*> redTeam;  // Équipe rouge
    // std::vector<Pokemon*> blueTeam; // Équipe bleue

    // Méthode pour charger les Pokémon à partir des noms
    //void loadPokemonTeams(const std::vector<std::string>& redTeamNames, const std::vector<std::string>& blueTeamNames);
};
