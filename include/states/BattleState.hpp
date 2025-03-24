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
    std::vector<sf::Text> barsText;

    std::vector<Button> moveButtons; // Boutons des attaques
    sf::RectangleShape bgMoveButtons;

    sf::CircleShape targetIndicator;

    int activePokemon = 0; // Indice du Pokémon actif
    bool isMoveChosen = false;
    bool isTargetChosen = false;

    // Valeur a stocker pour le calcul
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

    // Destructeur pour libérer la mémoire des clones de Pokémon
    ~BattleState()
    {
        // Libération de la mémoire des clones de Pokémon pour les équipes
        for (Pokemon *p : blueTeamStruct.pokemons)
        {
            delete p; // Libère la mémoire de chaque Pokémon cloné
        }

        for (Pokemon *p : redTeamStruct.pokemons)
        {
            delete p; // Libère la mémoire de chaque Pokémon cloné
        }
    }

private:
    sf::Sprite backgroundSprite; // Fond d'écran du combat
    sf::Font font;               // Police d'affichage des textes

    Button switchButton;             // Bouton pour changer de Pokémon

    bool isBlueTeamTurn = true; // L'équipe bleue commence
    bool isTurnReady = false;

    bool endBattle = false;

    bool handleSwitchButtonClick(sf::RenderWindow &window, TeamStruct &team);
    bool handleMoveButtonClick(sf::RenderWindow &window, TeamStruct &team);

    static bool enterPressed;
    static bool tabPressed;

    void handleMouseClick(sf::RenderWindow &window);
    void handleKeyPress(const sf::Event &event, bool &enterPressed, bool &tabPressed);
    void handleKeyRelease(const sf::Event &event, bool &enterPressed, bool &tabPressed);
    void processEnterKey();
    void processTabKey();
    void displayMoveDetails();

    int countAlivePokemons(const TeamStruct &team);

    void resetMoveButtonsOutline(TeamStruct &team);

    TeamStruct blueTeamStruct; // Équipe bleue
    TeamStruct redTeamStruct;  // Équipe rouge

    void loadPokemonTeamSprites(const std::vector<std::string> &teamNames, TeamStruct &teamStruct, const std::vector<sf::Vector2f> &initPos, bool reverseTexture);
    void drawPokemonTeam(sf::RenderWindow &window, TeamStruct &teamStruct);

    void createMoveButtons();                                               // Création des boutons d'attaques
    void drawMoveButtons(sf::RenderWindow &window, TeamStruct &teamStruct); // Affichage des boutons

    void createHealthBars(); // Initialisation des barres de vie
    void createTeamBars(TeamStruct &teamStruct, sf::Vector2f bgPos, sf::Vector2f barOffset);
    void updateHealthBars(TeamStruct &teamStruct);
    void drawHealthBars(sf::RenderWindow &window, TeamStruct &teamStruct);
    void drawTargetIndicator(sf::RenderWindow &window, TeamStruct &teamStruct);

    void createTargetIndicator();

    /* ======================== Logique du jeu ======================== */
    void loadPokemonTeamsInfos(const std::vector<std::string> &blueTeamNames, const std::vector<std::string> &redTeamNames);

    bool checkBattleOver();                    // Vérifie si le combat est terminé
    bool checkFainted(TeamStruct &teamStruct); // Vérifie si un Pokémon est KO
};
