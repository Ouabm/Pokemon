// In your main.cpp or wherever you create your Window
#include "Game_master.hpp"

int main() {
    // Create the window
    Window window;
   
    window.showPokemonSelection();
    window.init();
    
    // Create the game master with a pointer to the window
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