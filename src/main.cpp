#include "ResourceManager.hpp"
#include "GameStateManager.hpp"

#include "states/MenuState.hpp"

int main()
{
    ResourceManager::getInstance().loadAllResources();
    
    sf::RenderWindow window(sf::VideoMode(1024, 640), "Pokemon");

    // Création du GameStateManager
    GameStateManager manager;

    // Initialisation du premier état : MenuState
    manager.changeState(std::make_unique<MenuState>(&manager));

    while (window.isOpen())
    {
        manager.handleInput(window); // Gérer les entrées de l'utilisateur
        manager.update();            // Mettre à jour l'état actuel
        manager.render(window);      // Afficher l'état actuel
    }

    return 0;
}
