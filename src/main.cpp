#include "ResourceManager.hpp"
#include "GameStateManager.hpp"

#include "MenuState.hpp"

int main()
{
    ResourceManager::getInstance().loadAllResources();

    sf::RenderWindow window(sf::VideoMode(1024, 700), "Pokemon");

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


// A faire : 

// Comprendre pourquoi checkbattleover ne fonction pas dans update a cause erreur seg sur un sf::Shape update() (gdb)

// Selectionner en meme temps les pokemons dans le menu selection (optionnel)

// Target mode a gerer quand un des deux pokemons est mort 

// AnimationAttack

// Switch button unique 

// Note : 

// 1 Ajouter un destroy ressources pour utiliser que les ressources utiles pendant un etat

// 2 Ajout d'un hpp GameParameters pour centraliser toutes les positions des elements etc... (en cours)

// Ajuster taille des images pour fenetre coherente