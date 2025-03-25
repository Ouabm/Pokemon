#pragma once

#include "GameState.hpp"
#include "ElementUI.hpp"
#include "Pokemon.hpp"
#include "ElementUI.hpp"

// ================================= STRUCTURE DE L'ÉQUIPE =============================== //
// Structure pour gérer une équipe de Pokémon (sprites, Pokémon actifs, barres de vie, etc.)
struct BattleTeamStruct
{
    std::vector<sf::Sprite> pokemonSprites; // Sprites des Pokémon de l'équipe
    std::vector<Pokemon *> pokemons;        // Objets représentant les Pokémon

    std::vector<sf::RectangleShape> healthBars; // Barres de vie des Pokémon
    sf::RectangleShape bgHealthBar;             // Fond des barres de vie
    std::vector<sf::Text> barsText;             // Textes affichant les HP

    std::vector<Button> moveButtons;  // Boutons pour sélectionner les attaques
    sf::RectangleShape bgMoveButtons; // Fond des boutons d'attaques

    sf::CircleShape targetIndicator; // Indicateur de la cible sélectionnée

    int activePokemon = 0;             // Indice du Pokémon actif
    int pokemonTargeted = 0;           // Indice du Pokémon ennemi ciblé
    const Move *currentMove = nullptr; // Mouvement sélectionné

    bool isMoveChosen = false;   // Si un mouvement a été choisi
    bool isTargetChosen = false; // Si une cible a été choisie
    bool isReady = false;        // Si le joueur est prêt à attaquer
};

// ====================================== CLASSE BATTLESTATE ====================================== //
class BattleState : public GameState
{
public:
    BattleState(GameStateManager *manager, const std::vector<std::string> &blueTeamNames, const std::vector<std::string> &redTeamNames);

    // ========================== MÉTHODES PRINCIPALES ========================== //
    void handleInput(sf::RenderWindow &window) override; // Gestion des entrées utilisateur
    void update() override;                              // Mise à jour des données du combat
    void render(sf::RenderWindow &window) override;      // Affichage de l'interface du combat

    // Destructeur pour libérer la mémoire des Pokémon clonés
    ~BattleState()
    {
        // Suppression des Pokémon clonés pour éviter les fuites de mémoire
        for (Pokemon *p : blueTeamStruct.pokemons)
            delete p;

        for (Pokemon *p : redTeamStruct.pokemons)
            delete p;
    }

private:
    sf::Sprite backgroundSprite; // Fond d'écran du combat
    Button switchButton;         // Bouton permettant de changer de Pokémon

    static bool enterPressed; // État de la touche "Entrée"
    static bool tabPressed;   // État de la touche "Tab"

    BattleTeamStruct blueTeamStruct; // Équipe bleue
    BattleTeamStruct redTeamStruct;  // Équipe rouge

    // ======================= CHARGEMENT DES INFORMATIONS DES POKÉMONS ======================= //
    void loadPokemonTeamSprites(const std::vector<std::string> &teamNames, BattleTeamStruct &teamStruct, const std::vector<sf::Vector2f> &initPos, bool reverseTexture);
    void loadPokemonTeamsInfos(const std::vector<std::string> &blueTeamNames, const std::vector<std::string> &redTeamNames);

    // ============================== CRÉATION DES ÉLÉMENTS DU COMBAT ============================== //
    void createMoveButtons();                                                                      // Création des boutons d'attaques
    void createHealthBars();                                                                       // Création des barres de vie
    void createTeamBars(BattleTeamStruct &teamStruct, sf::Vector2f bgPos, sf::Vector2f barOffset); // Création des barres de vie des équipes
    void createTargetIndicator();                                                                  // Création de l'indicateur de cible

    // ============================== GESTION DES ENTRÉES UTILISATEUR ============================== //
    void handleKeyPress(const sf::Event &event);          // Gestion des touches pressées
    void processEnterKey(BattleTeamStruct &currentTeam);  // Action lors de l'appui sur "Entrée"
    int countAlivePokemons(const BattleTeamStruct &team); // Compte le nombre de Pokémon encore en vie

    // ============================== LOGIQUE DU COMBAT ============================== //
    void updateHealthBars(BattleTeamStruct &teamStruct); // Mise à jour des barres de vie
    void turnHandeler(BattleTeamStruct &blueTeamStruct,BattleTeamStruct &redTeamStruct);
    bool checkBattleOver();                              // Vérifie si le combat est terminé

    // ============================== AFFICHAGE DES ÉLÉMENTS ============================== //
    void drawMoveButtons(sf::RenderWindow &window, BattleTeamStruct &teamStruct);     // Affichage des boutons d'attaques
    void drawHealthBars(sf::RenderWindow &window, BattleTeamStruct &teamStruct);      // Affichage des barres de vie
    void drawTargetIndicator(sf::RenderWindow &window, BattleTeamStruct &teamStruct); // Affichage de l'indicateur de cible
    void drawPokemonTeam(sf::RenderWindow &window, BattleTeamStruct &teamStruct);     // Affichage des Pokémon de l'équipe

    void resetMoveButtonsOutline(BattleTeamStruct &team); // Réinitialisation des contours des boutons
};
