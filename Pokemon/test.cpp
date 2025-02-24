#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pokemon Attack Animation");

    // Charger la texture
    sf::Texture texture;
    if (!texture.loadFromFile("attacks/Hydro-Pump.png")) {
        std::cerr << "Erreur : Impossible de charger l'image." << std::endl;
        return -1;
    }

    // Paramètres de l'animation
    int columns = 2;  // Mets le vrai nombre de colonnes ici
    int rows = 7;     // Mets le vrai nombre de lignes ici
    int frameWidth = texture.getSize().x / columns;
    int frameHeight = texture.getSize().y / rows;
    int numFrames = columns * rows;
    int currentFrame = 0;
    float frameDuration = 0.2f;
    bool animationFinished = false; // Variable pour stopper l'animation

    sf::Clock clock;
    sf::Sprite sprite(texture);

    // Afficher uniquement la première frame
    sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));

    // Centrer le sprite
    sf::Vector2f startPosition(100, 150);
    sprite.setPosition(startPosition);
    sprite.setScale(2.0f, 2.0f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Mise à jour de l'animation si elle n'est pas terminée
        if (!animationFinished && clock.getElapsedTime().asSeconds() > frameDuration) {
            currentFrame++;

            if (currentFrame >= numFrames) {
                animationFinished = true;  // Stop l'animation après la dernière frame
            } else {
                int x = (currentFrame % columns) * frameWidth;
                int y = (currentFrame / columns) * frameHeight;
                sprite.setTextureRect(sf::IntRect(x, y, frameWidth, frameHeight));
                
            }

            clock.restart();
        }

        // Effacer et redessiner
        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
