#include "MenuState.hpp"
#include "SelectionState.hpp"
#include "GameStateManager.hpp"
#include "GameParameters.hpp"

/*==============================================================================
|                               CONSTRUCTEUR                                   |
==============================================================================*/
MenuState::MenuState(GameStateManager *manager) : GameState(manager)
{
    // Chargement et lecture de la musique de fond pour cet état
    ResourceManager::getInstance().playMusic("MenuStateMusic", Menu::MUSIC_VOLUME, true);

    // Chargement de l'arrière-plan du menu
    backgroundSprite.setTexture(ResourceManager::getInstance().getTexture("MenuStateBG"));

    // Création des boutons du menu
    sf::Vector2f buttonSize(Menu::BUTTON_WIDTH, Menu::BUTTON_HEIGHT);
    createMenuButtons(WINDOW_WIDTH, WINDOW_HEIGHT, buttonSize);
}

// ======================= CRÉATION DES BOUTONS DU MENU =======================//
void MenuState::createMenuButtons(float mainMenuwindowWidth, float mainMenuwindowHeight, const sf::Vector2f &buttonSize)
{
    // Calcul des positions verticales des boutons
    float startButtonsPos = Menu::START_BUTTON_POS_Y;
    float endButtonsPos = Menu::END_BUTTON_POS_Y;

    // Calcul des positions horizontales des boutons pour les centrer
    sf::Vector2f startButtonPos((mainMenuwindowWidth - buttonSize.x) / 2, startButtonsPos);
    sf::Vector2f helpButtonPos((mainMenuwindowWidth - buttonSize.x) / 2, startButtonsPos + (endButtonsPos - startButtonsPos) * 1 / 3);
    sf::Vector2f exitButtonPos((mainMenuwindowWidth - buttonSize.x) / 2, startButtonsPos + (endButtonsPos - startButtonsPos) * 2 / 3);

    // Création des boutons avec les paramètres du fichier GameParameters.hpp
    startButton = createButton("MenuStateFont", "Start", buttonSize, startButtonPos, Menu::BUTTON_FONT_SIZE, Menu::BUTTON_START_COLOR, Menu::BUTTON_TEXT_COLOR);
    helpButton = createButton("MenuStateFont", "Help", buttonSize, helpButtonPos, Menu::BUTTON_FONT_SIZE, Menu::BUTTON_HELP_COLOR, Menu::BUTTON_TEXT_COLOR);
    quitButton = createButton("MenuStateFont", "Quit", buttonSize, exitButtonPos, Menu::BUTTON_FONT_SIZE, Menu::BUTTON_QUIT_COLOR, Menu::BUTTON_TEXT_COLOR);
}

/*==============================================================================
|                        GESTION DES ENTRÉES UTILISATEUR                       |
==============================================================================*/
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
            handleButtonsClick(sf::Vector2f(event.mouseButton.x, event.mouseButton.y), window);
        }
    }
}

// ================ SOUS-FONCTIONS POUR LA GESTION DES ENTRÉES ================//
void MenuState::handleButtonsClick(const sf::Vector2f &mousePos, sf::RenderWindow &window)
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

/*==============================================================================
|                            GESTION DES UPDATES                               |
==============================================================================*/
void MenuState::update()
{
    // Aucune mise à jour nécessaire pour le moment
}

/*==============================================================================
|                          GESTION DES GRAPHISMES                              |
==============================================================================*/
void MenuState::render(sf::RenderWindow &window)
{
    window.clear();

    window.draw(backgroundSprite);

    drawButton(startButton, window);
    drawButton(helpButton, window);
    drawButton(quitButton, window);

    window.display();
}

// ============== SOUS-FONCTIONS POUR LA GESTION DES GRAPHISMES ===============//
void MenuState::drawButton(const Button &button, sf::RenderWindow &window)
{
    window.draw(button.shape); // Dessine la forme du bouton (rectangle)
    window.draw(button.text);  // Dessine le texte sur le bouton
}
