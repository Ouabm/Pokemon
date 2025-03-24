#pragma once

#include <SFML/Graphics.hpp>

// ==================== PARAMÈTRES GÉNÉRAUX ==================== //
constexpr float WINDOW_WIDTH = 1024.0f;
constexpr float WINDOW_HEIGHT = 700.0f;
constexpr float MASTER_VOLUME = 10.0f;

// ==================== PARAMÈTRES DU MENU ==================== //
namespace Menu
{
    namespace Button
    {
        constexpr float BUTTON_WIDTH = 200.0f;
        constexpr float BUTTON_HEIGHT = 50.0f;
        const sf::Vector2f BUTTON_SIZE = {BUTTON_WIDTH, BUTTON_HEIGHT};

        // Positions verticales
        constexpr float START_BUTTON_POS_Y = WINDOW_HEIGHT * 6.0f / 12;
        constexpr float HELP_BUTTON_POS_Y = WINDOW_HEIGHT * 7.5f / 12;
        constexpr float QUIT_BUTTON_POS_Y = WINDOW_HEIGHT * 9.0f / 12;

        // Position horizontale unique (identique pour tous les boutons)
        constexpr float BUTTON_POS_X = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;

        // Positions complètes des boutons
        const sf::Vector2f START_BUTTON_POS = sf::Vector2f(BUTTON_POS_X, START_BUTTON_POS_Y);
        const sf::Vector2f HELP_BUTTON_POS = sf::Vector2f(BUTTON_POS_X, HELP_BUTTON_POS_Y);
        const sf::Vector2f QUIT_BUTTON_POS = sf::Vector2f(BUTTON_POS_X, QUIT_BUTTON_POS_Y);

        constexpr int FONT_SIZE = 24;

        // Couleurs des boutons
        const sf::Color START_BUTTON_COLOR = sf::Color::Green;
        const sf::Color HELP_BUTTON_COLOR = sf::Color::Blue;
        const sf::Color QUIT_BUTTON_COLOR = sf::Color::Red;
        const sf::Color BUTTON_TEXT_COLOR = sf::Color::White;

        // Contour des boutons
        const sf::Color BUTTON_OUTLINE_COLOR = sf::Color::Transparent;
        constexpr float BUTTON_OUTLINE_THICKNESS = 0.0f;

        // Texte des boutons
        constexpr const char *START_BUTTON_TEXT = "Start";
        constexpr const char *HELP_BUTTON_TEXT = "Help";
        constexpr const char *QUIT_BUTTON_TEXT = "Quit";
    }

    namespace Music
    {
        constexpr float VOLUME = 50.0f * MASTER_VOLUME / 100.0f;
        constexpr const char *BACKGROUND_MUSIC = "MenuStateMusic";
    }

    namespace Background
    {
        constexpr const char *TEXTURE = "MenuStateBG";
    }

    namespace Font
    {
        constexpr const char *KEY = "MenuStateFont";
    }
}

// ==================== PARAMÈTRES DE LA SÉLECTION ==================== //
namespace Selection
{
    namespace Box
    {
        // Boîte de sélection pour l'équipe bleue
        constexpr float BLUE_BOX_WIDTH = 120.0f;
        constexpr float BLUE_BOX_HEIGHT = 120.0f;
        const sf::Vector2f BLUE_BOX_SIZE = {BLUE_BOX_WIDTH, BLUE_BOX_HEIGHT};

        constexpr float BLUE_BOX_POS_X = 60.0f;
        constexpr float BLUE_BOX_POS_Y = 30.0f;
        const sf::Vector2f BLUE_BOX_POS = {BLUE_BOX_POS_X, BLUE_BOX_POS_Y};

        const sf::Color BLUE_BOX_COLOR = sf::Color::Transparent;
        const sf::Color BLUE_BOX_OUTLINE_COLOR = sf::Color::Blue;
        constexpr float BLUE_BOX_OUTLINE_THICKNESS = 3.0f;

        // Boîte de sélection pour l'équipe rouge
        constexpr float RED_BOX_WIDTH = 126.0f;
        constexpr float RED_BOX_HEIGHT = 126.0f;
        const sf::Vector2f RED_BOX_SIZE = {RED_BOX_WIDTH, RED_BOX_HEIGHT};

        constexpr float RED_BOX_POS_X = 60.0f;
        constexpr float RED_BOX_POS_Y = 30.0f;
        const sf::Vector2f RED_BOX_POS = {RED_BOX_POS_X, RED_BOX_POS_Y};

        const sf::Color RED_BOX_COLOR = sf::Color::Transparent;
        const sf::Color RED_BOX_OUTLINE_COLOR = sf::Color::Red;
        constexpr float RED_BOX_OUTLINE_THICKNESS = 3.0f;
    }

    namespace Music
    {
        constexpr float VOLUME = 50.0f * MASTER_VOLUME / 100.0f;
        constexpr const char *BACKGROUND_MUSIC = "SelectionStateMusic";
    }

    namespace Background
    {
        constexpr const char *TEXTURE = "SelectionStateBG";
    }

    namespace Font
    {
        constexpr const char *KEY = "SelectionStateFont";
    }

    namespace Pokemon
    {
        constexpr int MAX_SELECTION = 2; // Nombre maximal de Pokémon à sélectionner

        // Dimensions de la grille des Pokémon
        constexpr int POKEMON_COLUMNS = 5;
        constexpr int POKEMON_ROWS = 3;
        constexpr float POKEMON_SCALE = 0.7f;
        constexpr float POKEMON_X_OFFSET = 60.0f;
        constexpr float POKEMON_Y_OFFSET = 30.0f;
        constexpr float POKEMON_SPACING_X = 180.0f;
        constexpr float POKEMON_SPACING_Y = 150.0f;
    }
}

// ==================== PARAMÈTRES DU COMBAT ==================== //
namespace Battle
{
    namespace Music
    {
        constexpr float VOLUME = 50.0f * MASTER_VOLUME / 100.0f; // Volume de la musique
        const std::string BACKGROUND_MUSIC = "BattleStateMusic"; // Musique de fond
    }
}

// ==================== PARAMÈTRES DE LA FIN DU JEU ==================== //
namespace End
{
    namespace Music
    {
        constexpr float VOLUME = 50.0f * MASTER_VOLUME / 100.0f; // Volume de la musique
        const std::string BACKGROUND_MUSIC = "EndStateMusic";    // Musique de fond
    }
}
