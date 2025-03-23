#pragma once // Version plus moderne des guardians #indef et #endif

#include <SFML/Graphics.hpp>
#include <memory> // Permet l'utilisation de pointeurs intelligents (comme std::unique_ptr) pour une gestion automatique de la mémoire.

class GameStateManager; // Déclaration avant usage : on déclare la classe GameStateManager ici sans l'inclure pour éviter les dépendances circulaires.

class GameState
{
public:
    // Le destructeur virtuel permet de s'assurer que les ressources des classes dérivées seront libérées correctement
    // lors de la destruction de l'objet, en respectant le principe du polymorphisme.
    virtual ~GameState() = default;

    // Fonction virtuelle pure : chaque état du jeu (MenuState, BattleState, etc.) doit implémenter ces méthodes
    // pour gérer les entrées utilisateur, les mises à jour de l'état, et le rendu graphique.
    virtual void handleInput(sf::RenderWindow &window) = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow &window) = 0;

protected:
    // Constructeur protégé, de sorte que seuls les états du jeu peuvent l'utiliser pour initialiser un GameState.
    // Cela permet de garantir que chaque état a une référence au GameStateManager pour gérer la transition entre les états.
    GameState(GameStateManager *manager) : gameManager(manager) {}

    // Pointeur vers le GameStateManager, nécessaire pour interagir avec d'autres états (par exemple, changer d'état).
    GameStateManager *gameManager;
};
