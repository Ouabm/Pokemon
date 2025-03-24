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

sf::RectangleShape createRectangle(const sf::Vector2f &size, const sf::Vector2f &position, const sf::Color &color, float outlineThickness, const sf::Color &outlineColor)
{
    sf::RectangleShape newRectangle;
    newRectangle.setSize(size);
    newRectangle.setPosition(position);
    newRectangle.setFillColor(color);
    newRectangle.setOutlineThickness(outlineThickness);
    newRectangle.setOutlineColor(outlineColor);
    return newRectangle;
}

sf::CircleShape createCircle(float radius, const sf::Vector2f &position, const sf::Color &fillColor, float outlineThickness, const sf::Color &outlineColor)
{
    sf::CircleShape newCircle;
    newCircle.setRadius(radius);                     // Définir le rayon du cercle
    newCircle.setPosition(position);                 // Définir la position du cercle
    newCircle.setFillColor(fillColor);               // Définir la couleur de remplissage
    newCircle.setOutlineThickness(outlineThickness); // Définir l'épaisseur du contour
    newCircle.setOutlineColor(outlineColor);         // Définir la couleur du contour
    newCircle.setOrigin(radius, radius);             // Définir l'origine du cercle au centre

    return newCircle;
}

Button createButton(const sf::Vector2f &size, const sf::Vector2f &position, const sf::Color &buttonColor, float outLineThickness, const sf::Color &outlineColor,
                    const std::string &fontKey, const std::string &buttonText, const int textSize, const sf::Color &textColor)
{
    Button newButton;
    newButton.shape = createRectangle(size, position, buttonColor, outLineThickness, outlineColor);

    // Centrage du texte dans le bouton
    newButton.text = createText(fontKey, buttonText, textSize, textColor, position);
    sf::FloatRect textBounds = newButton.text.getLocalBounds();
    newButton.text.setPosition(position.x + (size.x - textBounds.width) / 2,
                               position.y + (size.y - textBounds.height) / 2);

    return newButton;
}
