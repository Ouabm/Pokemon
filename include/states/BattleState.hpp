#pragma once

#include "GameState.hpp"
#include "ElementUI.hpp"
#include "Pokemon.hpp"

// Structure pour gérer une équipe de Pokémon (sprites, Pokémon actifs, barres de vie, etc.)
struct PokemonTeam
{
    std::vector<sf::Sprite> pokemonSprites;     // Sprites des Pokémon
    std::vector<Pokemon *> pokemons;            // Objets Pokémon
    std::vector<sf::RectangleShape> healthBars; // Barres de vie
    std::vector<Button> moveButtons;            // Boutons des attaques
    Button switchButton;                        // Bouton pour changer de Pokémon
    int activePokemon = 0;                      // Indice du Pokémon actif
};

class BattleState : public GameState
{
public:
    BattleState(GameStateManager *manager, const std::vector<std::string> &blueTeamNames, const std::vector<std::string> &redTeamNames);

    void handleInput(sf::RenderWindow &window) override;
    void update() override;
    void render(sf::RenderWindow &window) override;

private:
    /* ======================== Graphismes & UI ======================== */
    sf::Sprite backgroundSprite; // Fond d'écran du combat
    sf::Font font;               // Police d'affichage des textes

    PokemonTeam blueTeamStruct; // Équipe bleue
    PokemonTeam redTeamStruct;  // Équipe rouge

    void loadPokemonTeamSprites(const std::vector<std::string> &teamNames, PokemonTeam &teamStruct, const std::vector<sf::Vector2f> &initPos, bool reverseTexture);
    void drawPokemonTeam(sf::RenderWindow &window, PokemonTeam &teamStruct);

    void createMoveButtons();                                                // Création des boutons d'attaques
    void drawMoveButtons(sf::RenderWindow &window, PokemonTeam &teamStruct); // Affichage des boutons

    void createHealthBars();   // Initialisation des barres de vie
    void updateHealthBars(); // Mise à jour des barres de vie
    void drawHealthBars(sf::RenderWindow &window, PokemonTeam &teamStruct);

    /* ======================== Logique du jeu ======================== */
    void loadPokemonTeamsInfos(const std::vector<std::string> &blueTeamNames, const std::vector<std::string> &redTeamNames);

    bool checkBattleOver();              // Vérifie si le combat est terminé
    bool checkFainted(Pokemon *pokemon); // Vérifie si un Pokémon est KO
};
