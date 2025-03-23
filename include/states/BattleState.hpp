#pragma once

#include "GameState.hpp"
#include "ElementUI.hpp"
#include "Pokemon.hpp"

// Structure pour gérer une équipe de Pokémon (sprites, Pokémon actifs, barres de vie, etc.)
struct TeamStruct
{
    std::vector<sf::Sprite> pokemonSprites;     // Sprites des Pokémon
    std::vector<Pokemon *> pokemons;            // Objets Pokémon
    std::vector<sf::RectangleShape> healthBars; // Barres de vie
    sf::RectangleShape bgHealthBar;
    std::vector<Button> moveButtons; // Boutons des attaques
    Button switchButton;             // Bouton pour changer de Pokémon

    int activePokemon = 0; // Indice du Pokémon actif
    bool moveChosen = false;
    bool targetChosen = false;
    int pokemonTargeted = 0;
    const Move *currentMove = nullptr;
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

    bool isBlueTeamTurn = true; // L'équipe bleue commence

    // bool blueMoveChosen = false;
    // bool redMoveChosen = false;

    // bool blueTargetChosen = false;
    // bool redTargetChosen = false;

    bool handleSwitchButtonClick(sf::RenderWindow &window, TeamStruct &team);
    bool handleMoveButtonClick(sf::RenderWindow &window, TeamStruct &team);

    void resetMoveButtonsOutline(TeamStruct &team);

    // Etat ou on choisi

    // Target

    TeamStruct blueTeamStruct; // Équipe bleue
    TeamStruct redTeamStruct;  // Équipe rouge

    void loadPokemonTeamSprites(const std::vector<std::string> &teamNames, TeamStruct &teamStruct, const std::vector<sf::Vector2f> &initPos, bool reverseTexture);
    void drawPokemonTeam(sf::RenderWindow &window, TeamStruct &teamStruct);

    void createMoveButtons();                                               // Création des boutons d'attaques
    void drawMoveButtons(sf::RenderWindow &window, TeamStruct &teamStruct); // Affichage des boutons

    void createHealthBars(); // Initialisation des barres de vie
    void updateHealthBars(); // Mise à jour des barres de vie
    void drawHealthBars(sf::RenderWindow &window, TeamStruct &teamStruct);

    /* ======================== Logique du jeu ======================== */
    void loadPokemonTeamsInfos(const std::vector<std::string> &blueTeamNames, const std::vector<std::string> &redTeamNames);

    bool checkBattleOver();              // Vérifie si le combat est terminé
    bool checkFainted(Pokemon *pokemon); // Vérifie si un Pokémon est KO
};
