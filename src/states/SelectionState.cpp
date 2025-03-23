#include "SelectionState.hpp" // Etat actuel ou l'on se trouve
#include "BattleState.hpp"    // Sert uniquement pour la transition

#include "GameStateManager.hpp"
#include "PokemonManager.hpp"

#include "GameParameters.hpp"

/*==============================================================================
|                               CONSTRUCTEUR                                   |
==============================================================================*/
SelectionState::SelectionState(GameStateManager *manager) : GameState(manager), selectedIndex(0), playerTurn(0)
{
    // Joue la musique de fond pour l'état de sélection
    ResourceManager::getInstance().playMusic(Selection::Music::BACKGROUND_MUSIC, Selection::Music::VOLUME, true);

    // Charge l'arrière-plan
    backgroundSprite.setTexture(ResourceManager::getInstance().getTexture("SelectionStateBG"));

    // Charge les sprites des Pokémon
    loadAllPokemonSprites();

    // Configure la boîte de sélection pour encadrer le Pokémon sélectionné
    selectionBox = createRectangle(sf::Vector2f(120, 120), sf::Vector2f(60, 30), sf::Color::Transparent, 4, sf::Color::Blue);
}

// ================== CHARGEMENT DES SPRITES DES POKEMONS ====================//
void SelectionState::loadAllPokemonSprites()
{
    std::vector<std::string> pokemonNames = PokemonManager::getInstance().getAllPokemonNames();
    for (const std::string &name : pokemonNames)
    {
        sf::Sprite sprite;
        sprite.setTexture(ResourceManager::getInstance().getTexture(name));
        pokemonSprites.push_back(sprite);
    }
}


/*==============================================================================
|                        GESTION DES ENTRÉES UTILISATEUR                       |
==============================================================================*/
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
            switch (event.key.code)
            {
            case sf::Keyboard::Enter:
                handlePokemonSelection();
                break;
            case sf::Keyboard::Right:
                if (selectedIndex % 5 < 4)
                    selectedIndex++;
                break;
            case sf::Keyboard::Left:
                if (selectedIndex % 5 > 0)
                    selectedIndex--;
                break;
            case sf::Keyboard::Down:
                if (selectedIndex + 5 < pokemonSprites.size())
                    selectedIndex += 5;
                break;
            case sf::Keyboard::Up:
                if (selectedIndex >= 5)
                    selectedIndex -= 5;
                break;
            default:
                break;
            }
        }
    }
}

/* ================ SOUS-FONCTIONS POUR LA GESTION DES ENTRÉES ================*/
void SelectionState::handlePokemonSelection()
{
    std::string selectedPokemonName = PokemonManager::getInstance().getAllPokemonNames()[selectedIndex];

    // Simplification de la recherche dans les équipes
    bool pokemonAlreadyInRedTeam = std::find(redTeam.begin(), redTeam.end(), selectedPokemonName) != redTeam.end();
    bool pokemonAlreadyInBlueTeam = std::find(blueTeam.begin(), blueTeam.end(), selectedPokemonName) != blueTeam.end();

    // Ajoute le Pokémon à l'équipe en fonction du tour du joueur
    if ((playerTurn && !pokemonAlreadyInRedTeam) || (!playerTurn && !pokemonAlreadyInBlueTeam))
    {
        (playerTurn ? redTeam : blueTeam).push_back(selectedPokemonName);
        playerTurn = !playerTurn;
    }

    // Si les deux équipes sont complètes, on passe à l'état suivant (BattleState)
    if (redTeam.size() == 2 && blueTeam.size() == 2)
    {
        gameManager->changeState(std::make_unique<BattleState>(gameManager, blueTeam, redTeam)); // Transition vers la bataille
    }
}

/*==============================================================================
|                            GESTION DES UPDATES                               |
==============================================================================*/
void SelectionState::update()
{
    // Aucune mise à jour nécessaire pour le moment
}

/*==============================================================================
|                          GESTION DES GRAPHISMES                              |
==============================================================================*/
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
    selectionBox.setOutlineColor(playerTurn ? sf::Color::Red : sf::Color::Blue);

    window.draw(selectionBox);
    window.display();
}