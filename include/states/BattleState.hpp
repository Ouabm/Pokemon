#pragma once

#include "GameState.hpp"
#include "ElementUI.hpp"
#include "Pokemon.hpp"
#include "ElementUI.hpp"

// ================================= STRUCTURE DE L'ÉQUIPE =============================== //

/**
 * @struct BattleTeamStruct
 * @brief Structure contenant tous les éléments visuels et logiques d'une équipe de Pokémon pendant un combat
 * 
 * Cette structure regroupe les sprites, les données des Pokémon, les éléments d'interface utilisateur
 * et les états relatifs à une équipe pendant un combat.
 */
struct BattleTeamStruct
{
    std::vector<sf::Sprite> pokemonSprites; ///< Sprites graphiques des Pokémon de l'équipe
    std::vector<Pokemon *> pokemons;        ///< Pointeurs vers les objets Pokémon de l'équipe

    std::vector<sf::RectangleShape> healthBars; ///< Barres de vie pour chaque Pokémon
    sf::RectangleShape bgHealthBar;             ///< Arrière-plan des barres de vie
    std::vector<sf::Text> barsText;             ///< Textes affichant les points de vie actuels

    std::vector<Button> moveButtons;  ///< Boutons pour sélectionner les attaques
    sf::RectangleShape bgMoveButtons; ///< Arrière-plan des boutons d'attaques

    sf::CircleShape targetIndicator; ///< Indicateur visuel de la cible sélectionnée

    int activePokemon = 0;             ///< Index du Pokémon actuellement actif dans l'équipe
    int pokemonTargeted = 0;           ///< Index du Pokémon ennemi ciblé
    const Move *currentMove = nullptr; ///< Pointeur vers l'attaque actuellement sélectionnée

    bool isMoveChosen = false;   ///< Flag indiquant si un mouvement a été choisi
    bool isTargetChosen = false; ///< Flag indiquant si une cible a été sélectionnée
    bool isReady = false;        ///< Flag indiquant si l'équipe est prête à attaquer
};

// ====================================== CLASSE BATTLESTATE ====================================== //

/**
 * @class BattleState
 * @brief Classe gérant l'état de combat du jeu, héritant de GameState
 * 
 * Cette classe gère toute la logique et l'affichage d'un combat Pokémon entre deux équipes.
 * Elle hérite de la classe de base GameState pour s'intégrer dans le système d'états du jeu.
 */
class BattleState : public GameState
{
public:
    /**
     * @brief Constructeur de la classe BattleState
     * @param manager Pointeur vers le gestionnaire d'états du jeu
     * @param blueTeamNames Vecteur des noms des Pokémon de l'équipe bleue
     * @param redTeamNames Vecteur des noms des Pokémon de l'équipe rouge
     */
    BattleState(GameStateManager *manager, const std::vector<std::string> &blueTeamNames, const std::vector<std::string> &redTeamNames);

    // ========================== MÉTHODES PRINCIPALES ========================== //
    
    /**
     * @brief Gère les entrées utilisateur pendant le combat
     * @param window Fenêtre SFML pour la capture des événements
     */
    void handleInput(sf::RenderWindow &window) override;
    
    /**
     * @brief Met à jour la logique du combat à chaque frame
     */
    void update() override;
    
    /**
     * @brief Dessine tous les éléments du combat dans la fenêtre
     * @param window Fenêtre SFML pour le rendu
     */
    void render(sf::RenderWindow &window) override;

    /**
     * @brief Destructeur libérant la mémoire des Pokémon alloués
     */
    ~BattleState()
    {
        // Libération des Pokémon de l'équipe bleue
        for (Pokemon *p : blueTeamStruct.pokemons)
            delete p;

        // Libération des Pokémon de l'équipe rouge
        for (Pokemon *p : redTeamStruct.pokemons)
            delete p;
    }

private:
    sf::Sprite backgroundSprite; ///< Sprite pour l'arrière-plan du combat
    Button switchButton;         ///< Bouton pour changer de Pokémon

    static bool enterPressed; ///< État de la touche Entrée (pour éviter les répétitions)
    static bool tabPressed;   ///< État de la touche Tab (pour éviter les répétitions)

    BattleTeamStruct blueTeamStruct; ///< Données de l'équipe bleue (joueur)
    BattleTeamStruct redTeamStruct;  ///< Données de l'équipe rouge (adversaire)

    // ======================= CHARGEMENT DES INFORMATIONS DES POKÉMONS ======================= //
    
    /**
     * @brief Charge les sprites d'une équipe de Pokémon
     * @param teamNames Noms des Pokémon à charger
     * @param teamStruct Structure d'équipe à remplir
     * @param initPos Positions initiales des sprites
     * @param reverseTexture Si vrai, inverse les textures (pour l'équipe adverse)
     */
    void loadPokemonTeamSprites(const std::vector<std::string> &teamNames, BattleTeamStruct &teamStruct, const std::vector<sf::Vector2f> &initPos, bool reverseTexture);
    
    /**
     * @brief Charge les informations des deux équipes de Pokémon
     * @param blueTeamNames Noms des Pokémon de l'équipe bleue
     * @param redTeamNames Noms des Pokémon de l'équipe rouge
     */
    void loadPokemonTeamsInfos(const std::vector<std::string> &blueTeamNames, const std::vector<std::string> &redTeamNames);

    // ============================== CRÉATION DES ÉLÉMENTS DU COMBAT ============================== //
    
    /**
     * @brief Crée les boutons pour sélectionner les attaques
     */
    void createMoveButtons();
    
    /**
     * @brief Crée les barres de vie pour les Pokémon
     */
    void createHealthBars();
    
    /**
     * @brief Crée les barres de vie pour une équipe spécifique
     * @param teamStruct Structure de l'équipe à initialiser
     * @param bgPos Position de l'arrière-plan des barres
     * @param barOffset Décalage entre les barres
     */
    void createTeamBars(BattleTeamStruct &teamStruct, sf::Vector2f bgPos, sf::Vector2f barOffset);
    
    /**
     * @brief Crée l'indicateur de cible pour les attaques
     */
    void createTargetIndicator();

    // ============================== GESTION DES ENTRÉES UTILISATEUR ============================== //
    
    /**
     * @brief Gère les événements clavier
     * @param event Événement SFML à traiter
     */
    void handleKeyPress(const sf::Event &event);
    
    /**
     * @brief Traite l'appui sur la touche Entrée
     * @param currentTeam Équipe actuellement contrôlée par le joueur
     */
    void processEnterKey(BattleTeamStruct &currentTeam);
    
    /**
     * @brief Compte le nombre de Pokémon encore en vie dans une équipe
     * @param team Équipe à analyser
     * @return Nombre de Pokémon vivants
     */
    int countAlivePokemons(const BattleTeamStruct &team);

    // ============================== LOGIQUE DU COMBAT ============================== //
    
    /**
     * @brief Met à jour les barres de vie d'une équipe
     * @param teamStruct Équipe à mettre à jour
     */
    void updateHealthBars(BattleTeamStruct &teamStruct);
    
    /**
     * @brief Gère le déroulement d'un tour de combat
     * @param blueTeamStruct Référence à l'équipe bleue
     * @param redTeamStruct Référence à l'équipe rouge
     */
    void turnHandeler(BattleTeamStruct &blueTeamStruct, BattleTeamStruct &redTeamStruct);
    
    /**
     * @brief Vérifie si le combat est terminé
     * @return Vrai si une équipe n'a plus de Pokémon vivants
     */
    bool checkBattleOver();

    // ============================== AFFICHAGE DES ÉLÉMENTS ============================== //
    
    /**
     * @brief Dessine les boutons d'attaques
     * @param window Fenêtre de rendu
     * @param teamStruct Équipe dont il faut dessiner les boutons
     */
    void drawMoveButtons(sf::RenderWindow &window, BattleTeamStruct &teamStruct);
    
    /**
     * @brief Dessine les barres de vie
     * @param window Fenêtre de rendu
     * @param teamStruct Équipe dont il faut dessiner les barres
     */
    void drawHealthBars(sf::RenderWindow &window, BattleTeamStruct &teamStruct);
    
    /**
     * @brief Dessine l'indicateur de cible
     * @param window Fenêtre de rendu
     * @param teamStruct Équipe dont il faut dessiner l'indicateur
     */
    void drawTargetIndicator(sf::RenderWindow &window, BattleTeamStruct &teamStruct);
    
    /**
     * @brief Dessine les Pokémon d'une équipe
     * @param window Fenêtre de rendu
     * @param teamStruct Équipe à dessiner
     */
    void drawPokemonTeam(sf::RenderWindow &window, BattleTeamStruct &teamStruct);

    /**
     * @brief Réinitialise les contours des boutons d'attaque
     * @param team Équipe dont les boutons doivent être réinitialisés
     */
    void resetMoveButtonsOutline(BattleTeamStruct &team);
};