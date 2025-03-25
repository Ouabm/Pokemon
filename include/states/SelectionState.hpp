#pragma once

#include "GameState.hpp"
#include "ElementUI.hpp"

// ========================== STRUCTURE DE SÉLECTION D'ÉQUIPE ========================== //

/**
 * @struct TeamSelectionStruct
 * @brief Structure gérant l'état de sélection d'une équipe de Pokémon
 *
 * Contient tous les éléments nécessaires pour la sélection interactive
 * des Pokémon par un joueur.
 */
struct TeamSelectionStruct
{
    std::vector<sf::RectangleShape> selectedBoxes; ///< Conteneurs visuels pour les Pokémon sélectionnés
    sf::RectangleShape currentBox;                 ///< Cadre de sélection actif (mise en évidence)
    std::vector<std::string> pokemonNames;         ///< Noms des Pokémon actuellement sélectionnés
    int selectionIndex = 0;                        ///< Index de la sélection courante (0-based)
    bool isReady = false;                          ///< Flag indiquant si la sélection est complétée
};

// ================================ CLASSE SELECTIONSTATE ================================ //

/**
 * @class SelectionState
 * @brief État de sélection des équipes Pokémon avant le combat
 *
 * Cet état permet aux joueurs de choisir leurs Pokémon pour former
 * leurs équipes avant de lancer un combat. Gère l'interface de
 * sélection pour deux équipes (rouge et bleue).
 */
class SelectionState : public GameState
{
public:
    /**
     * @brief Constructeur de SelectionState
     * @param manager Pointeur vers le gestionnaire d'états du jeu
     *
     * Initialise l'état de sélection et charge les ressources nécessaires.
     */
    SelectionState(GameStateManager *manager);

    // ========================== MÉTHODES PRINCIPALES ========================== //
    
    /**
     * @brief Gère les entrées utilisateur (sélection, navigation, validation)
     * @param window Fenêtre SFML pour la capture des événements
     */
    void handleInput(sf::RenderWindow &window) override;
    
    /**
     * @brief Met à jour la logique de sélection à chaque frame
     *
     * Gère les animations et les transitions entre états de sélection.
     */
    void update() override;
    
    /**
     * @brief Affiche l'interface de sélection des Pokémon
     * @param window Fenêtre SFML pour le rendu graphique
     */
    void render(sf::RenderWindow &window) override;

private:
    // ============================== ÉLÉMENTS GRAPHIQUES ============================== //
    sf::Sprite backgroundSprite;            ///< Arrière-plan de l'écran de sélection
    std::vector<sf::Sprite> pokemonSprites; ///< Collection de tous les sprites Pokémon disponibles

    // ============================== STRUCTURES DE SÉLECTION ============================== //
    TeamSelectionStruct redTeamSelection;  ///< État de sélection pour l'équipe rouge
    TeamSelectionStruct blueTeamSelection; ///< État de sélection pour l'équipe bleue

    // ============================== MÉTHODES UTILES ============================== //
    
    /**
     * @brief Charge tous les sprites Pokémon disponibles pour la sélection
     *
     * Initialise le vecteur pokemonSprites avec les textures chargées.
     */
    void loadAllPokemonSprites();
    
    /**
     * @brief Gère la logique de sélection d'un Pokémon
     * @param teamSelection Référence à la structure de sélection à modifier
     *
     * Ajoute le Pokémon sélectionné à l'équipe et met à jour l'interface.
     */
    void handlePokemonSelection(TeamSelectionStruct &teamSelection);
};