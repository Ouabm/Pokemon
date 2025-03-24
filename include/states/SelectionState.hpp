#pragma once

#include "GameState.hpp"
#include "ElementUI.hpp"

// ========================== STRUCTURE DE SÉLECTION D'ÉQUIPE ========================== //
// Gère la sélection des Pokémon pour chaque équipe
struct TeamSelectionStruct
{
    std::vector<sf::RectangleShape> selectedBoxes; // Boîtes de sélection des Pokémon
    sf::RectangleShape currentBox;                 // Boîte de sélection active
    std::vector<std::string> pokemonNames;         // Noms des Pokémon sélectionnés
    int selectionIndex = 0;                        // Indice du Pokémon actuellement sélectionné
    bool isReady = false;                          // Indique si l'équipe est prête
};

// ================================ CLASSE SELECTIONSTATE ================================ //
// État du jeu permettant aux joueurs de sélectionner leurs équipes
class SelectionState : public GameState
{
public:
    SelectionState(GameStateManager *manager); // Constructeur

    // ========================== MÉTHODES PRINCIPALES ========================== //
    void handleInput(sf::RenderWindow &window) override; // Gestion des entrées utilisateur
    void update() override;                              // Mise à jour de l'état de sélection
    void render(sf::RenderWindow &window) override;      // Affichage de l'écran de sélection

private:
    // ============================== ÉLÉMENTS GRAPHIQUES ============================== //
    sf::Sprite backgroundSprite;            // Fond d'écran de l'écran de sélection
    std::vector<sf::Sprite> pokemonSprites; // Sprites de tous les Pokémon disponibles

    // ============================== STRUCTURES DE SÉLECTION ============================== //
    TeamSelectionStruct redTeamSelection;  // Sélection de l'équipe rouge
    TeamSelectionStruct blueTeamSelection; // Sélection de l'équipe bleue

    // ============================== MÉTHODES UTILES ============================== //
    void loadAllPokemonSprites();                                    // Charge tous les sprites de Pokémon disponibles
    void handlePokemonSelection(TeamSelectionStruct &teamSelection); // Gère la sélection des Pokémon
};
