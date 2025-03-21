#include "../../include/states/SelectionState.hpp"
#include <iostream>

SelectionState::SelectionState(GameStateManager *manager)
    : GameState(manager), selectedIndex(0), playerTurn(0)
{
    ResourceManager::getInstance().playMusic("SelectionStateMusic", 50.0f, true);
    backgroundSprite.setTexture(ResourceManager::getInstance().getTexture("SelectionStateBG"));

    std::vector<std::string> pokemonNames = PokemonManager::getInstance().getAllPokemonNames();
    for (const std::string &name : pokemonNames)
    {
        sf::Sprite sprite;
        sprite.setTexture(ResourceManager::getInstance().getTexture(name));
        pokemonSprites.push_back(sprite);
    }

    selectionBox.setSize(sf::Vector2f(120, 120));
    selectionBox.setFillColor(sf::Color::Transparent);
    selectionBox.setOutlineThickness(5);
    selectionBox.setOutlineColor(sf::Color::Yellow);
}

void SelectionState::handleInput(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                std::string selectedPokemonName = PokemonManager::getInstance().getAllPokemonNames()[selectedIndex];

                // Vérifie si le Pokémon est déjà dans l'une des équipes
                bool pokemonAlreadyInRedTeam = std::find(redTeam.begin(), redTeam.end(), selectedPokemonName) != redTeam.end();
                bool pokemonAlreadyInBlueTeam = std::find(blueTeam.begin(), blueTeam.end(), selectedPokemonName) != blueTeam.end();

                // Ajoute le Pokémon à l'équipe rouge ou bleue :
                if (playerTurn)
                {
                    if (!pokemonAlreadyInRedTeam) // On peut ajouter && !pokemonAlreadyInBlueTeam pour n'avoir aucun doublons // Revient a le mettre avant le playTurn
                    {
                        redTeam.push_back(selectedPokemonName); // Ajoute à l'équipe rouge
                        playerTurn = !playerTurn;
                    }
                }
                else
                {
                    if (!pokemonAlreadyInBlueTeam) // On peut ajouter && !pokemonAlreadyInRedTeam pour n'avoir aucun doublons // Revient a le mettre avant le playTurn
                    {
                        blueTeam.push_back(selectedPokemonName); // Ajoute à l'équipe bleue
                        playerTurn = !playerTurn;
                    }
                }

                // Si les deux équipes sont complètes, lance l'état suivant
                if (redTeam.size() == 2 && blueTeam.size() == 2)
                {
                    gameManager->changeState(std::make_unique<BattleState>(gameManager, redTeam, blueTeam)); // On passe en argument les noms des pokemons choisis
                }
            }
            else if (event.key.code == sf::Keyboard::Right && (selectedIndex % 5) < 4)
                selectedIndex++;
            else if (event.key.code == sf::Keyboard::Left && (selectedIndex % 5) > 0)
                selectedIndex--;
            else if (event.key.code == sf::Keyboard::Down && selectedIndex + 5 < pokemonSprites.size())
                selectedIndex += 5;
            else if (event.key.code == sf::Keyboard::Up && selectedIndex >= 5)
                selectedIndex -= 5;
        }
    }
}

void SelectionState::update() {}

void SelectionState::render(sf::RenderWindow &window)
{
    window.clear();
    window.draw(backgroundSprite);

    for (size_t i = 0; i < pokemonSprites.size(); i++)
    {
        int row = i / 5;
        int col = i % 5;
        pokemonSprites[i].setPosition(60 + col * 180, 30 + row * 150);
        pokemonSprites[i].setScale(0.7f, 0.7f);
        window.draw(pokemonSprites[i]);
    }

    int row = selectedIndex / 5;
    int col = selectedIndex % 5;
    selectionBox.setPosition(60 + col * 180, 30 + row * 150);

    // Change la couleur du rectangle en fonction de l'équipe en cours
    if (playerTurn)
    {
        selectionBox.setOutlineColor(sf::Color::Red); // Équipe rouge
    }
    else
    {
        selectionBox.setOutlineColor(sf::Color::Blue); // Équipe bleue
    }

    window.draw(selectionBox);
    window.display();
}