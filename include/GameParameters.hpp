#pragma once

#include <SFML/Graphics.hpp>

// ==================== PARAMÈTRES GÉNÉRAUX ==================== //
constexpr float WINDOW_WIDTH = 1024.0f; // Largeur de la fenêtre du jeu
constexpr float WINDOW_HEIGHT = 640.0f; // Hauteur de la fenêtre du jeu

constexpr float MASTER_VOLUME = 0.0f;

// ==================== PARAMÈTRES DU MENU ==================== //
namespace Menu
{
    // ==================== PARAMÈTRES DES BOUTONS ==================== //
    namespace Button
    {
        constexpr float WIDTH = 200.0f; // Largeur des boutons
        constexpr float HEIGHT = 50.0f; // Hauteur des boutons

        // Positions des boutons
        constexpr float START_BUTTON_POS_Y = WINDOW_HEIGHT * 7.0f / 12; // Position verticale du bouton "Start"
        constexpr float HELP_BUTTON_POS_Y = WINDOW_HEIGHT * 8.0f / 12;  // Position verticale du bouton "Help"
        constexpr float QUIT_BUTTON_POS_Y = WINDOW_HEIGHT * 11.0f / 12; // Position verticale du bouton "Quit"

        constexpr int FONT_SIZE = 24; // Taille de la police des boutons

        // Couleurs des boutons
        const sf::Color START_BUTTON_COLOR = sf::Color::Green;
        const sf::Color HELP_BUTTON_COLOR = sf::Color::Blue;
        const sf::Color QUIT_BUTTON_COLOR = sf::Color::Red;
        const sf::Color BUTTON_TEXT_COLOR = sf::Color::White;

        // Texte des boutons
        const std::string START_BUTTON_TEXT = "Start";
        const std::string HELP_BUTTON_TEXT = "Help";
        const std::string QUIT_BUTTON_TEXT = "Quit";
    }

    // ==================== PARAMÈTRES DE LA MUSIQUE ==================== //
    namespace Music
    {
        constexpr float VOLUME = 50.0f * MASTER_VOLUME;        // Volume de la musique
        const std::string BACKGROUND_MUSIC = "MenuStateMusic"; // Musique de fond
    }

    // ==================== PARAMÈTRES DE L'ARrière-PLAN ==================== //
    namespace Background
    {
        const std::string TEXTURE = "MenuStateBG"; // Texture de fond
    }

    // ==================== PARAMÈTRES DE LA POLICE ==================== //
    namespace Font
    {
        const std::string KEY = "MenuStateFont"; // Clé de la police pour le menu
    }
}

// ==================== PARAMÈTRES DE LA SÉLECTION ==================== //
namespace Selection
{
    // Dimensions de la sélection
    constexpr float POKEMON_SPRITE_WIDTH = 120.0f;          // Largeur du sprite Pokémon
    constexpr float POKEMON_SPRITE_HEIGHT = 120.0f;         // Hauteur du sprite Pokémon
    constexpr float SELECTION_BOX_WIDTH = 120.0f;           // Largeur de la boîte de sélection
    constexpr float SELECTION_BOX_HEIGHT = 120.0f;          // Hauteur de la boîte de sélection
    constexpr float SELECTION_BOX_OUTLINE_THICKNESS = 4.0f; // Epaisseur de l'encadré

    // Couleurs de la sélection
    const sf::Color SELECTION_BOX_COLOR = sf::Color::Blue; // Couleur de la boîte de sélection

    const std::string BACKGROUND_TEXTURE = "SelectionStateBG"; // Musique de fond

    namespace Music
    {
        constexpr float VOLUME = 50.0f * MASTER_VOLUME;             // Volume de la musique
        const std::string BACKGROUND_MUSIC = "SelectionStateMusic"; // Musique de fond
    }

}

// ==================== PARAMÈTRES DU COMBAT ==================== //
namespace Battle
{

    namespace Music
    {
        constexpr float VOLUME = 50.0f * MASTER_VOLUME;          // Volume de la musique
        const std::string BACKGROUND_MUSIC = "BattleStateMusic"; // Musique de fond
    }
}

// ==================== PARAMÈTRES DE LA FIN DU JEU ==================== //
namespace End
{

    namespace Music
    {
        constexpr float VOLUME = 50.0f * MASTER_VOLUME;       // Volume de la musique
        const std::string BACKGROUND_MUSIC = "EndStateMusic"; // Musique de fond
    }
}
