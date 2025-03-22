#include "SelectionState.hpp" // Etat actuel ou l'on se trouve
#include "BattleState.hpp"    // Sert uniquement pour la transition

#include "GameStateManager.hpp"
#include "PokemonManager.hpp"

SelectionState::SelectionState(GameStateManager *manager) : GameState(manager), selectedIndex(0), playerTurn(0)
{
    // Joue la musique de fond pour l'état de sélection
    ResourceManager::getInstance().playMusic("SelectionStateMusic", 50.0f, true);

    // Charge l'arrière-plan
    backgroundSprite.setTexture(ResourceManager::getInstance().getTexture("SelectionStateBG"));

    // Charge les sprites des Pokémon
    loadPokemonSprites();

    // Configure la boîte de sélection pour mettre en surbrillance le Pokémon sélectionné
    configureSelectionBox();
}

void SelectionState::handleInput(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                handlePokemonSelection();
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

// Sous fonctions pour ne pas surcharger les fonctions principales

void SelectionState::loadPokemonSprites()
{
    std::vector<std::string> pokemonNames = PokemonManager::getInstance().getAllPokemonNames();
    for (const std::string &name : pokemonNames)
    {
        sf::Sprite sprite;
        sprite.setTexture(ResourceManager::getInstance().getTexture(name));
        pokemonSprites.push_back(sprite);
    }
}

void SelectionState::configureSelectionBox()
{
    selectionBox.setSize(sf::Vector2f(120, 120));
    selectionBox.setFillColor(sf::Color::Transparent);
    selectionBox.setOutlineThickness(5);
    selectionBox.setOutlineColor(sf::Color::Blue);
}

// Gère la sélection d'un Pokémon et l'ajout à l'équipe
void SelectionState::handlePokemonSelection()
{
    std::string selectedPokemonName = PokemonManager::getInstance().getAllPokemonNames()[selectedIndex];

    // Vérifie si le Pokémon est déjà dans l'une des équipes
    bool pokemonAlreadyInBlueTeam = std::find(blueTeam.begin(), blueTeam.end(), selectedPokemonName) != blueTeam.end();
    bool pokemonAlreadyInRedTeam = std::find(redTeam.begin(), redTeam.end(), selectedPokemonName) != redTeam.end();

    // Ajoute le Pokémon à l'équipe en fonction du tour du joueur
    if (playerTurn && !pokemonAlreadyInRedTeam)
    {
        redTeam.push_back(selectedPokemonName);
        playerTurn = !playerTurn;
    }
    else if (!playerTurn && !pokemonAlreadyInBlueTeam)
    {
        blueTeam.push_back(selectedPokemonName);
        playerTurn = !playerTurn;
    }

    // Si les deux équipes sont complètes, on passe à l'état suivant (BattleState)
    if (redTeam.size() == 2 && blueTeam.size() == 2)
    {
        gameManager->changeState(std::make_unique<BattleState>(gameManager, blueTeam, redTeam)); // Transition vers la bataille
    }
}