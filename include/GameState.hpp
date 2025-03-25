#pragma once // Version plus moderne des guardians #ifndef et #endif

#include <SFML/Graphics.hpp>
#include <memory> // Pour std::unique_ptr

// Forward declaration pour éviter les dépendances circulaires
class GameStateManager;

/**
 * @class GameState
 * @brief Classe de base abstraite pour tous les états du jeu
 *
 * Cette classe définit l'interface commune que tous les états du jeu doivent implémenter.
 * Elle suit le pattern State pour gérer les différents états du jeu (menu, combat, etc.).
 * Utilise un GameStateManager pour les transitions entre états.
 */
class GameState
{
public:
    /**
     * @brief Destructeur virtuel
     *
     * Garantit une destruction correcte des classes dérivées.
     * Marqué comme default car aucune ressource à libérer dans la classe de base.
     */
    virtual ~GameState() = default;

    /**
     * @brief Gère les entrées utilisateur pour cet état
     * @param window Référence à la fenêtre de rendu SFML
     *
     * Méthode virtuelle pure à implémenter par les états concrets.
     * Doit traiter tous les événements clavier/souris spécifiques à l'état.
     */
    virtual void handleInput(sf::RenderWindow &window) = 0;

    /**
     * @brief Met à jour la logique de l'état
     *
     * Méthode virtuelle pure à implémenter par les états concrets.
     * Contient la logique de mise à jour propre à chaque état.
     */
    virtual void update() = 0;

    /**
     * @brief Dessine l'état dans la fenêtre
     * @param window Référence à la fenêtre de rendu SFML
     *
     * Méthode virtuelle pure à implémenter par les états concrets.
     * Doit effectuer tout le rendu graphique spécifique à l'état.
     */
    virtual void render(sf::RenderWindow &window) = 0;

protected:
    /**
     * @brief Constructeur protégé
     * @param manager Pointeur vers le gestionnaire d'états
     *
     * Seules les classes dérivées peuvent instancier un GameState.
     * Initialise la référence vers le GameStateManager pour les transitions.
     */
    GameState(GameStateManager *manager) : gameManager(manager) {}

    /**
     * @protected
     * @var gameManager
     * @brief Pointeur vers le gestionnaire d'états du jeu
     *
     * Permet aux états concrets d'effectuer des transitions entre états.
     * Ne doit pas être null (la validité est garantie par le constructeur).
     */
    GameStateManager *gameManager;
};