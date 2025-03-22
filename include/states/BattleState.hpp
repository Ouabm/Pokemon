#pragma once

#include "GameState.hpp"
#include "ElementUI.hpp"

#include "Pokemon.hpp"

class BattleState : public GameState
{
public:
    // Modification pour accepter les noms des Pokémon (std::string) au lieu de pointeurs
    BattleState(GameStateManager *manager, const std::vector<std::string> &blueTeamNames, const std::vector<std::string> &redTeamNames);

    void handleInput(sf::RenderWindow &window) override;
    void update() override;
    void render(sf::RenderWindow &window) override;

private:
    sf::Sprite backgroundSprite;
    sf::Font font;

    std::vector<Button> moveButtons;
    void createMoveButtons();
    void drawMoveButtons(sf::RenderWindow &window);

    std::vector<sf::Sprite> blueTeamPokemonSprites;
    std::vector<sf::Sprite> redTeamPokemonSprites;
    void loadTeamSprites(const std::vector<std::string> &teamNames, std::vector<sf::Sprite> &teamSprites);
    void drawTeamSprites(sf::RenderWindow &window);

    std::vector<Pokemon *> blueTeamPokemons;
    std::vector<Pokemon *> redTeamPokemons;
    void loadTeamPokemons(const std::vector<std::string> &blueTeamNames, const std::vector<std::string> &redTeamNames);

    int blueActivePokemon = 0; // L'indice du Pokémon actif dans l'équipe bleue
    int redActivePokemon = 0;  // L'indice du Pokémon actif dans l'équipe rouge

    bool checkBattleOver();
    bool checkFainted(Pokemon *pokemon);
};
