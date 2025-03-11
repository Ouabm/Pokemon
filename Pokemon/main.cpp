#include "Game_master.hpp"

int main() {
    // Créer la fenêtre du menu
    Window window;
    window.showMainMenu();  // Afficher le menu principal
    
    // Attendre que le joueur sélectionne ses Pokémon
    if (!window.debut) {
        return 0;  // Si le joueur quitte avant de choisir, on ferme le jeu proprement
    }

    // Créer le GameMaster après la sélection des Pokémon
    GameMaster gameMaster(&window);

    // Game loop
    sf::Clock clock;
    while (window.window->isOpen()) {
        sf::Time deltaTime = clock.restart();
        
        // Process events
        sf::Event event;
        while (window.window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.window->close();
            }
            
            // Pass events to the game master
            gameMaster.handleInput(event);
        }
        
        // Update game logic
        gameMaster.update(deltaTime.asSeconds());

        // Handle basic window input (for UI elements not related to game logic)
        window.handleinput();
      
        // Render everything
        window.render();
    }
    
    return 0;
}
