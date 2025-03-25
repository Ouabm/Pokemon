#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "ResourceManager.hpp" // Pour récupérer les polices

/**
 * @file GraphicsUtils.hpp
 * @brief Utilitaire de création d'éléments graphiques SFML
 * 
 * Fournit des fonctions helper pour créer facilement des éléments UI courants
 */

/**
 * @brief Crée un objet texte SFML configuré
 * @param fontKey Clé de la police dans le ResourceManager ("" pour police par défaut)
 * @param text Contenu du texte (vide par défaut)
 * @param size Taille de la police (0 par défaut)
 * @param color Couleur du texte (Transparent par défaut)
 * @param position Position du texte (0,0 par défaut)
 * @return Objet sf::Text configuré
 * 
 * @note Si fontKey est vide, utilise la police par défaut de SFML
 */
sf::Text createText(const std::string &fontKey = "", 
                   const std::string &text = "", 
                   unsigned int size = 0, 
                   sf::Color const &color = sf::Color::Transparent, 
                   sf::Vector2f const &position = sf::Vector2f(0, 0));

/**
 * @brief Crée un rectangle SFML configuré
 * @param size Dimensions du rectangle (0,0 par défaut)
 * @param position Position du rectangle (0,0 par défaut)
 * @param color Couleur de remplissage (Transparent par défaut)
 * @param outlineThickness Épaisseur du contour (0 par défaut)
 * @param outlineColor Couleur du contour (Transparent par défaut)
 * @return Objet sf::RectangleShape configuré
 */
sf::RectangleShape createRectangle(const sf::Vector2f &size = sf::Vector2f(0, 0), 
                                 const sf::Vector2f &position = sf::Vector2f(0, 0), 
                                 const sf::Color &color = sf::Color::Transparent, 
                                 float outlineThickness = 0.0f, 
                                 const sf::Color &outlineColor = sf::Color::Transparent);

/**
 * @brief Crée un cercle SFML configuré
 * @param radius Rayon du cercle (0 par défaut)
 * @param position Position du cercle (0,0 par défaut)
 * @param fillColor Couleur de remplissage (Transparent par défaut)
 * @param outlineThickness Épaisseur du contour (0 par défaut)
 * @param outlineColor Couleur du contour (Transparent par défaut)
 * @return Objet sf::CircleShape configuré
 */
sf::CircleShape createCircle(float radius = 0.0f, 
                           const sf::Vector2f &position = sf::Vector2f(0, 0), 
                           const sf::Color &fillColor = sf::Color::Transparent, 
                           float outlineThickness = 0.0f, 
                           const sf::Color &outlineColor = sf::Color::Transparent);

/**
 * @struct Button
 * @brief Structure représentant un bouton UI
 * 
 * Combine un rectangle (fond) et un texte (label)
 */
struct Button
{
    sf::RectangleShape shape; ///< Forme rectangulaire du bouton
    sf::Text text;           ///< Texte affiché sur le bouton
};

/**
 * @brief Crée un bouton configuré
 * @param size Dimensions du bouton (0,0 par défaut)
 * @param position Position du bouton (0,0 par défaut)
 * @param buttonColor Couleur du bouton (Transparent par défaut)
 * @param outlineThickness Épaisseur du contour (0 par défaut)
 * @param outlineColor Couleur du contour (Transparent par défaut)
 * @param fontKey Clé de la police pour le texte ("" par défaut)
 * @param buttonText Texte du bouton (vide par défaut)
 * @param textSize Taille du texte (0 par défaut)
 * @param textColor Couleur du texte (Transparent par défaut)
 * @return Structure Button configurée
 * 
 * @note Le texte est automatiquement centré dans le bouton
 */
Button createButton(const sf::Vector2f &size = sf::Vector2f(0, 0), 
                   const sf::Vector2f &position = sf::Vector2f(0, 0), 
                   const sf::Color &buttonColor = sf::Color::Transparent, 
                   float outlineThickness = 0.0f, 
                   const sf::Color &outlineColor = sf::Color::Transparent, 
                   const std::string &fontKey = "", 
                   const std::string &buttonText = "", 
                   const int textSize = 0, 
                   const sf::Color &textColor = sf::Color::Transparent);