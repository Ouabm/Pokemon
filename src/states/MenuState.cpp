#include "MenuState.hpp"      // Etat actuel ou l'on se trouve
#include "SelectionState.hpp" // Sert uniquement pour la transition
#include "GameStateManager.hpp"

MenuState::MenuState(GameStateManager *manager) : GameState(manager)
{
    // Chargement et lecture de la musique de fond pour cet état
    ResourceManager::getInstance().playMusic("MenuStateMusic", 50.0f, true);

    // Chargement de l'arrière-plan du menu
    backgroundSprite.setTexture(ResourceManager::getInstance().getTexture("MenuStateBG"));

    // Taille de la fenêtre statique pour le menu (valeurs codées en dur pour l'instant)
    float mainMenuwindowWidth = 1024.0; // Largeur de la fenêtre (à ajuster plus tard)
    float mainMenuwindowHeight = 640.0; // Hauteur de la fenêtre (à ajuster plus tard)

    // Création des boutons du menu en fonction des dimensions de la fenêtre
    sf::Vector2f buttonSize(200, 50);
    createMenuButtons(mainMenuwindowWidth, mainMenuwindowHeight, buttonSize);
}

void MenuState::handleInput(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event)) // Boucle pour traiter les événements
    {
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) // Si l'utilisateur clique sur la souris
        {
            // On vérifie sur quel bouton l'utilisateur a cliqué
            handleButtonClicks(sf::Vector2f(event.mouseButton.x, event.mouseButton.y), window);
        }
    }
}

void MenuState::update()
{
    // Aucune mise à jour nécessaire pour le moment
}

void MenuState::render(sf::RenderWindow &window)
{
    window.clear();

    // Affichage de l'arrière-plan
    window.draw(backgroundSprite);

    // Affichage des boutons dans la fenêtre
    drawButton(startButton, window);
    drawButton(helpButton, window);
    drawButton(quitButton, window);

    window.display();
}

// Sous fonctions pour ne pas surcharger les fonctions principales

void MenuState::createMenuButtons(float mainMenuwindowWidth, float mainMenuwindowHeight, const sf::Vector2f &buttonSize)
{
    // Calcul des positions verticales des boutons (en fonction de la hauteur de la fenêtre)
    float startButtonsPos = mainMenuwindowHeight * 7.0f / 12; // Position du bouton "Start"
    float endButtonsPos = mainMenuwindowHeight * 11.0f / 12;  // Position du bouton "Quit"

    // Calcul des positions horizontales des boutons pour les centrer dans la fenêtre
    sf::Vector2f startButtonPos((mainMenuwindowWidth - buttonSize.x) / 2, startButtonsPos);
    sf::Vector2f helpButtonPos((mainMenuwindowWidth - buttonSize.x) / 2, startButtonsPos + (endButtonsPos - startButtonsPos) * 1 / 3);
    sf::Vector2f exitButtonPos((mainMenuwindowWidth - buttonSize.x) / 2, startButtonsPos + (endButtonsPos - startButtonsPos) * 2 / 3);

    // Création des boutons en spécifiant leur texte, taille, couleur, et position
    startButton = createButton("MenuStateFont", "Start", buttonSize, startButtonPos, 24, sf::Color::Green, sf::Color::White);
    helpButton = createButton("MenuStateFont", "Help", buttonSize, helpButtonPos, 24, sf::Color::Blue, sf::Color::White);
    quitButton = createButton("MenuStateFont", "Quit", buttonSize, exitButtonPos, 24, sf::Color::Red, sf::Color::White);
}

void MenuState::handleButtonClicks(const sf::Vector2f &mousePos, sf::RenderWindow &window)
{
    // Vérifie si l'utilisateur a cliqué sur le bouton "Start"
    if (startButton.shape.getGlobalBounds().contains(mousePos))
    {
        gameManager->changeState(std::make_unique<SelectionState>(gameManager)); // Transition vers l'état "SelectionState"
    }
    // Vérifie si l'utilisateur a cliqué sur le bouton "Help"
    else if (helpButton.shape.getGlobalBounds().contains(mousePos))
    {
        // A implémenter
    }
    // Vérifie si l'utilisateur a cliqué sur le bouton "Quit"
    else if (quitButton.shape.getGlobalBounds().contains(mousePos))
    {
        window.close();
    }
}

void MenuState::drawButton(const Button &button, sf::RenderWindow &window)
{
    window.draw(button.shape); // Dessine la forme du bouton (rectangle)
    window.draw(button.text);  // Dessine le texte sur le bouton
}
