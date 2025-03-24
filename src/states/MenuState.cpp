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
    ResourceManager::getInstance().playMusic(Menu::Music::BACKGROUND_MUSIC, Menu::Music::VOLUME, true);

    // Chargement de l'arrière-plan du menu
    backgroundSprite.setTexture(ResourceManager::getInstance().getTexture(Menu::Background::TEXTURE));

    createMenuButtons();
}

// ======================= CRÉATION DES BOUTONS DU MENU =======================//
void MenuState::createMenuButtons()
{
    // Création des boutons avec les paramètres du fichier GameParameters.hpp
    startButton = createButton(
        Menu::Button::BUTTON_SIZE, Menu::Button::START_BUTTON_POS,
        Menu::Button::START_BUTTON_COLOR, Menu::Button::BUTTON_OUTLINE_THICKNESS, Menu::Button::BUTTON_OUTLINE_COLOR,
        Menu::Font::KEY, Menu::Button::START_BUTTON_TEXT, Menu::Button::FONT_SIZE, Menu::Button::BUTTON_TEXT_COLOR);
    helpButton = createButton(
        Menu::Button::BUTTON_SIZE, Menu::Button::HELP_BUTTON_POS,
        Menu::Button::HELP_BUTTON_COLOR, Menu::Button::BUTTON_OUTLINE_THICKNESS, Menu::Button::BUTTON_OUTLINE_COLOR,
        Menu::Font::KEY, Menu::Button::HELP_BUTTON_TEXT, Menu::Button::FONT_SIZE, Menu::Button::BUTTON_TEXT_COLOR);
    quitButton = createButton(
        Menu::Button::BUTTON_SIZE, Menu::Button::QUIT_BUTTON_POS,
        Menu::Button::QUIT_BUTTON_COLOR, Menu::Button::BUTTON_OUTLINE_THICKNESS, Menu::Button::BUTTON_OUTLINE_COLOR,
        Menu::Font::KEY, Menu::Button::QUIT_BUTTON_TEXT, Menu::Button::FONT_SIZE, Menu::Button::BUTTON_TEXT_COLOR);
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
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            // On vérifie sur quel bouton l'utilisateur a cliqué
            handleButtonClick(sf::Vector2f(event.mouseButton.x, event.mouseButton.y), window);
        }
    }
}

// ================ SOUS-FONCTIONS POUR LA GESTION DES ENTRÉES ================//
void MenuState::handleButtonClick(const sf::Vector2f &mousePos, sf::RenderWindow &window)
{
    // Vérifie si l'utilisateur a cliqué sur le bouton "Start"
    if (startButton.shape.getGlobalBounds().contains(mousePos))
    {
        gameManager->changeState(std::make_unique<SelectionState>(gameManager)); // Transition vers l'état "SelectionState"
    }
    // Vérifie si l'utilisateur a cliqué sur le bouton "Help"
    else if (helpButton.shape.getGlobalBounds().contains(mousePos))
    {
        // A implémenter HELP ICI
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
    window.draw(button.shape); 
    window.draw(button.text);
}
