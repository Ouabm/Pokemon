#include "ElementUI.hpp"

sf::Text createText(const std::string &fontKey, const std::string &text, unsigned int charSize, const sf::Color &color, const sf::Vector2f &position)
{
    sf::Text newText;

    // Charger la police à partir de la clé
    newText.setFont(ResourceManager::getInstance().getFont(fontKey));
    newText.setString(text);
    newText.setCharacterSize(charSize);
    newText.setFillColor(color);
    newText.setPosition(position);

    return newText;
}

sf::RectangleShape createRectangle(const sf::Vector2f &size, const sf::Vector2f &position, const sf::Color &color)
{
    sf::RectangleShape rectangle;
    rectangle.setSize(size);
    rectangle.setPosition(position);
    rectangle.setFillColor(color);
    return rectangle;
}

// Le 24 doit etre un param
Button createButton(const std::string &fontKey, const std::string &buttonText, const sf::Vector2f &size, const sf::Vector2f &position, const int textSize, const sf::Color &buttonColor, const sf::Color &textColor)
{
    Button button;
    button.shape = createRectangle(size, position, buttonColor);

    // Centrage du texte dans le bouton
    button.text = createText(fontKey, buttonText, textSize, textColor, position);
    sf::FloatRect textBounds = button.text.getLocalBounds();
    button.text.setPosition(
        position.x + (size.x - textBounds.width) / 2,
        position.y + (size.y - textBounds.height) / 2);

    return button;
}


