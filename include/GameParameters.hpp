#pragma once

#include <SFML/Graphics.hpp>

// ==================== PARAMÈTRES GÉNÉRAUX ==================== //
constexpr float WINDOW_WIDTH = 1024.0f; // Largeur de la fenêtre du jeu
constexpr float WINDOW_HEIGHT = 640.0f; // Hauteur de la fenêtre du jeu

// ==================== PARAMÈTRES DU MENU ==================== //
namespace Menu
{
    constexpr float BUTTON_WIDTH = 200.0f; // Largeur des boutons
    constexpr float BUTTON_HEIGHT = 50.0f; // Hauteur des boutons

    constexpr float START_BUTTON_POS_Y = WINDOW_HEIGHT * 7.0f / 12; // Position verticale du bouton "Start"
    constexpr float END_BUTTON_POS_Y = WINDOW_HEIGHT * 11.0f / 12; // Position verticale du bouton "Start"
    constexpr float QUIT_BUTTON_POS_Y = WINDOW_HEIGHT * 11.0f / 12; // Position verticale du bouton "Quit"

    constexpr int BUTTON_FONT_SIZE = 24; // Taille de la police des boutons

    // Couleurs des boutons
    const sf::Color BUTTON_START_COLOR = sf::Color::Green;
    const sf::Color BUTTON_HELP_COLOR = sf::Color::Blue;
    const sf::Color BUTTON_QUIT_COLOR = sf::Color::Red;
    const sf::Color BUTTON_TEXT_COLOR = sf::Color::White;

    // Musique de fond
    constexpr float MUSIC_VOLUME = 50.0f; // Volume de la musique du menu
}

// ==================== PARAMÈTRES DE LA SÉLECTION ==================== //
namespace Selection
{

    // Musique de fond
    constexpr float SELECTION_MUSIC_VOLUME = 50.0f; // Volume de la musique à la fin du jeu
}

// ==================== PARAMÈTRES DU COMBAT ==================== //
namespace Battle
{

    // Musique de fond
    constexpr float COMBAT_MUSIC_VOLUME = 60.0f; // Volume de la musique pendant le combat
}

// ==================== PARAMÈTRES DE LA FIN DU JEU ==================== //
namespace End
{

    // Musique de fond
    constexpr float END_MUSIC_VOLUME = 50.0f; // Volume de la musique à la fin du jeu
}
