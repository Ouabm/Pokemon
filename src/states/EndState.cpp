#include "EndState.hpp"  // Etat actuel ou l'on se trouve
#include "MenuState.hpp" // Sert uniquement pour la transition (si on rejoue)

#include "GameStateManager.hpp"
#include "GameParameters.hpp"

/*==============================================================================
|                               CONSTRUCTEUR                                   |
==============================================================================*/
EndState::EndState(GameStateManager *manager) : GameState(manager)
{
    ResourceManager::getInstance().playMusic(End::Music::BACKGROUND_MUSIC, End::Music::VOLUME, true);
    backgroundSprite.setTexture(ResourceManager::getInstance().getTexture("EndStateBG"));

    // Création du texte de fin de jeu
    endText.setString("");

    // Taille de la fenêtre
    float mainMenuwindowWidth = 1024.0; // Faudrait avoir acces a window ici; A modifier plus tard ??
    float mainMenuwindowHeight = 640.0;

    // Taille des boutons
    sf::Vector2f buttonSize(200, 50);
    float startButtonsPos = mainMenuwindowHeight * 7.0 / 12;
    float endButtonsPos = mainMenuwindowHeight * 8.5 / 12;

    // Calcul des positions pour centrer les boutons
    sf::Vector2f startButtonPos((mainMenuwindowWidth - buttonSize.x) / 2, startButtonsPos);
    sf::Vector2f helpButtonPos((mainMenuwindowWidth - buttonSize.x) / 2, startButtonsPos + (endButtonsPos - startButtonsPos));

    replayButton = createButton("EndStateFont", "Replay", buttonSize, startButtonPos, 24, sf::Color::Green, sf::Color::White);
    quitButton = createButton("EndStateFont", "Quit", buttonSize, helpButtonPos, 24, sf::Color::Red, sf::Color::White);
}

/*==============================================================================
|                        GESTION DES ENTRÉES UTILISATEUR                       |
==============================================================================*/
void EndState::handleInput(sf::RenderWindow &window)
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
                window.close(); // Ferme la fenêtre du jeu
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                // Vérifie si l'utilisateur a cliqué sur le bouton REJOUER
                if (replayButton.shape.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                {
                    // Transition vers MenuState
                    gameManager->changeState(std::make_unique<MenuState>(gameManager));
                }

                // Vérifie si l'utilisateur a cliqué sur le bouton QUITTER
                if (quitButton.shape.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                {
                    window.close(); // Ferme la fenêtre du jeu
                }
            }
        }
    }
}

/*==============================================================================
|                            GESTION DES UPDATES                               |
==============================================================================*/
void EndState::update()
{
    // Temps écoulé depuis le dernier frame
    float elapsedTime = clock.getElapsedTime().asSeconds();

    // Si le temps écoulé est supérieur à un délai, ajouter un caractère
    const float delay = 0.1f; // Temps entre chaque ajout de caractère

    std::string fullText = "Fin du jeu. Appuyez sur ESC pour quitter.";
    std::string currentText = endText.getString();

    if (elapsedTime > delay && currentText.size() < fullText.size())
    {
        currentText += fullText[currentText.size()]; // Ajoute un caractère à la fois
        endText.setString(currentText);              // Met à jour le texte

        // Redémarre l'horloge après avoir ajouté un caractère
        clock.restart();
    }
}

/*==============================================================================
|                          GESTION DES GRAPHISMES                              |
==============================================================================*/
void EndState::render(sf::RenderWindow &window)
{
    window.clear();

    // Affichage de l'arrière-plan
    window.draw(backgroundSprite);

    window.draw(endText); // Affichage du texte de fin

    // Affichage des boutons
    window.draw(replayButton.shape);
    window.draw(replayButton.text);
    window.draw(quitButton.shape);
    window.draw(quitButton.text);

    window.display();
}
