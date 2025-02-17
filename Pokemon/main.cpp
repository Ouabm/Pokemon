#include"Graphique.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pokemon Battle");
    window.setFramerateLimit(60);
    
    
    Window battleScene;
    
    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        battleScene.render();
    }
    
    return 0;
}