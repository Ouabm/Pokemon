#include "../../include/states/MenuState.hpp"      // Etat actuel ou l'on se trouve
#include "../../include/states/SelectionState.hpp" // Sert uniquement pour la transition

#include "../../include/GameStateManager.hpp"

MenuState::MenuState(GameStateManager *manager) : GameState(manager)
{
    ResourceManager::getInstance().playMusic("MenuStateMusic", 50.0f, true);
    backgroundSprite.setTexture(ResourceManager::getInstance().getTexture("MenuStateBG"));

    // Taille de la fenêtre
    float mainMenuwindowWidth = 1024.0; // Faudrait avoir acces a window ici; A modifier plus tard ??
    float mainMenuwindowHeight = 640.0;

    // Taille des boutons
    sf::Vector2f buttonSize(200, 50);
    float startButtonsPos = mainMenuwindowHeight * 7.0 / 12;
    float endButtonsPos = mainMenuwindowHeight * 11.0 / 12;

    // Calcul des positions pour centrer les boutons
    sf::Vector2f startButtonPos((mainMenuwindowWidth - buttonSize.x) / 2, startButtonsPos);
    sf::Vector2f helpButtonPos((mainMenuwindowWidth - buttonSize.x) / 2, startButtonsPos + (endButtonsPos - startButtonsPos) * 1 / 3);
    sf::Vector2f exitButtonPos((mainMenuwindowWidth - buttonSize.x) / 2, startButtonsPos + (endButtonsPos - startButtonsPos) * 2 / 3);

    startButton = createButton("MenuStateFont", "Start", buttonSize, startButtonPos, sf::Color::Green, sf::Color::White);
    helpButton = createButton("MenuStateFont", "Help", buttonSize, helpButtonPos, sf::Color::Blue, sf::Color::White);
    quitButton = createButton("MenuStateFont", "Quit", buttonSize, exitButtonPos, sf::Color::Red, sf::Color::White);
}

void MenuState::handleInput(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                // Vérifie si l'utilisateur a cliqué sur le bouton Start
                if (startButton.shape.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                {
                    // Transition vers SelectionState
                    gameManager->changeState(std::make_unique<SelectionState>(gameManager));
                }

                // Vérifie si l'utilisateur a cliqué sur le bouton Help
                if (helpButton.shape.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                {
                    // A implementer
                }

                // Vérifie si l'utilisateur a cliqué sur le bouton Quit
                if (quitButton.shape.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                {
                    window.close(); // Ferme la fenêtre du jeu
                }
            }
        }
    }
}

void MenuState::update() {}

void MenuState::render(sf::RenderWindow &window)
{
    window.clear();

    // Affichage de l'arrière-plan
    window.draw(backgroundSprite);

    // Affichage des boutons
    window.draw(startButton.shape);
    window.draw(startButton.text);
    window.draw(helpButton.shape);
    window.draw(helpButton.text);
    window.draw(quitButton.shape);
    window.draw(quitButton.text);

    window.display();
}
