#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "ResourceManager.hpp" // Pour récupérer les polices

sf::Text createText(const std::string &text, const std::string &fontPath, unsigned int size, sf::Color const &color, sf::Vector2f const &position);
sf::RectangleShape createRectangle(sf::Vector2f const &size, sf::Vector2f const &position, sf::Color const &color);sf::RectangleShape createRectangle(const sf::Vector2f &size, const sf::Vector2f &position = sf::Vector2f(0, 0), const sf::Color &color = sf::Color::White, float outlineThickness = 5.0f, const sf::Color &outlineColor = sf::Color::Blue);

struct Button
{
    sf::RectangleShape shape;
    sf::Text text;
};

Button createButton(const std::string &fontKey, const std::string &buttonText, const sf::Vector2f &size, const sf::Vector2f &position, const int textSize, const sf::Color &buttonColor, const sf::Color &textColor);
