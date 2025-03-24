#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "ResourceManager.hpp" // Pour récupérer les polices

sf::Text createText(const std::string &fontKey = "", const std::string &text = "", unsigned int size = 0, sf::Color const &color = sf::Color::Transparent, sf::Vector2f const &position = sf::Vector2f(0, 0));

sf::RectangleShape createRectangle(const sf::Vector2f &size = sf::Vector2f(0, 0), const sf::Vector2f &position = sf::Vector2f(0, 0), const sf::Color &color = sf::Color::Transparent, float outlineThickness = 0.0f, const sf::Color &outlineColor = sf::Color::Transparent);

sf::CircleShape createCircle(float radius = 0.0f, const sf::Vector2f &position = sf::Vector2f(0, 0), const sf::Color &fillColor = sf::Color::Transparent, float outlineThickness = 0.0f, const sf::Color &outlineColor = sf::Color::Transparent);

struct Button
{
    sf::RectangleShape shape;
    sf::Text text;
};

Button createButton(const sf::Vector2f &size = sf::Vector2f(0, 0), const sf::Vector2f &position = sf::Vector2f(0, 0), const sf::Color &buttonColor = sf::Color::Transparent, float outlineThickness = 0.0f, const sf::Color &outlineColor = sf::Color::Transparent, const std::string &fontKey = "", const std::string &buttonText = "", const int textSize = 0, const sf::Color &textColor = sf::Color::Transparent);
