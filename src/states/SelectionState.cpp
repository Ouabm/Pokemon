#include "SelectionState.hpp" // Etat actuel ou l'on se trouve
#include "BattleState.hpp"    // Sert uniquement pour la transition

#include "GameStateManager.hpp"
#include "PokemonManager.hpp"

#include "GameParameters.hpp"

/*==============================================================================
|                               CONSTRUCTEUR                                   |
==============================================================================*/
SelectionState::SelectionState(GameStateManager *manager) : GameState(manager)
{
    // Joue la musique de fond pour l'état de sélection
    ResourceManager::getInstance().playMusic(Selection::Music::BACKGROUND_MUSIC, Selection::Music::VOLUME, true);

    // Charge l'arrière-plan
    backgroundSprite.setTexture(ResourceManager::getInstance().getTexture(Selection::Background::TEXTURE));

    // Charge les sprites des Pokémon
    loadAllPokemonSprites();

    // Initialisation des boîtes de sélection pour les deux équipes
    blueTeamSelection.currentBox = createRectangle(Selection::Box::BLUE_BOX_SIZE, Selection::Box::BLUE_BOX_POS, Selection::Box::BLUE_BOX_COLOR, Selection::Box::BLUE_BOX_OUTLINE_THICKNESS, Selection::Box::BLUE_BOX_OUTLINE_COLOR);
    redTeamSelection.currentBox = createRectangle(Selection::Box::RED_BOX_SIZE, Selection::Box::RED_BOX_POS, Selection::Box::RED_BOX_COLOR, Selection::Box::RED_BOX_OUTLINE_THICKNESS, Selection::Box::RED_BOX_OUTLINE_COLOR);
}

/* ================== CHARGEMENT DES SPRITES DES POKEMONS ==================== */
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
            // Gérer les touches uniquement pour les équipes non prêtes
            if (!blueTeamSelection.isReady)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Enter:
                    handlePokemonSelection(blueTeamSelection);
                    break;

                case sf::Keyboard::Right:
                    if (blueTeamSelection.selectionIndex % 5 < 4)
                        blueTeamSelection.selectionIndex++;
                    break;
                case sf::Keyboard::Left:
                    if (blueTeamSelection.selectionIndex % 5 > 0)
                        blueTeamSelection.selectionIndex--;
                    break;
                case sf::Keyboard::Down:
                    if (blueTeamSelection.selectionIndex + 5 < pokemonSprites.size())
                        blueTeamSelection.selectionIndex += 5;
                    break;
                case sf::Keyboard::Up:
                    if (blueTeamSelection.selectionIndex >= 5)
                        blueTeamSelection.selectionIndex -= 5;
                    break;
                default:
                    break;
                }
            }

            if (!redTeamSelection.isReady)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Space:
                    handlePokemonSelection(redTeamSelection);
                    break;
                case sf::Keyboard::Z: // Haut (Rouge)
                    if (redTeamSelection.selectionIndex >= 5)
                        redTeamSelection.selectionIndex -= 5;
                    break;
                case sf::Keyboard::Q: // Gauche (Rouge)
                    if (redTeamSelection.selectionIndex % 5 > 0)
                        redTeamSelection.selectionIndex--;
                    break;
                case sf::Keyboard::S: // Bas (Rouge)
                    if (redTeamSelection.selectionIndex + 5 < pokemonSprites.size())
                        redTeamSelection.selectionIndex += 5;
                    break;
                case sf::Keyboard::D: // Droite (Rouge)
                    if (redTeamSelection.selectionIndex % 5 < 4)
                        redTeamSelection.selectionIndex++;
                    break;
                default:
                    break;
                }
            }
        }
    }
}

/* ================ SOUS-FONCTIONS POUR LA GESTION DES ENTRÉES ================*/
void SelectionState::handlePokemonSelection(TeamSelectionStruct &teamSelection)
{
    if (!teamSelection.isReady)
    {
        std::string selectedPokemonName = PokemonManager::getInstance().getAllPokemonNames()[teamSelection.selectionIndex];

        // Vérifie si le Pokémon est déjà dans l'équipe
        bool pokemonAlreadyInTeam = std::find(teamSelection.pokemonNames.begin(), teamSelection.pokemonNames.end(), selectedPokemonName) != teamSelection.pokemonNames.end();

        // Si le Pokémon n'est pas déjà dans l'équipe, ajoute-le et la boîte de sélection dans selectedBoxes
        if (!pokemonAlreadyInTeam)
        {
            teamSelection.pokemonNames.push_back(selectedPokemonName);
            teamSelection.selectedBoxes.push_back(teamSelection.currentBox); // Ajouter la boîte de sélection actuelle à selectedBoxes
            std::cout << "PokeOk" << std::endl;
        }

        if (teamSelection.pokemonNames.size() == 2)
        {
            teamSelection.currentBox.setPosition(-1000, -1000); // Déplace la boîte en dehors de l'écran
            teamSelection.isReady = true;
            std::cout << "Good !!!" << std::endl;
            return;
        }
    }
}

/*==============================================================================
|                            GESTION DES UPDATES                               |
==============================================================================*/
void SelectionState::update()
{
    // Si les deux équipes sont complètes, on passe à l'état suivant (BattleState)
    if (redTeamSelection.pokemonNames.size() == 2 && blueTeamSelection.pokemonNames.size() == 2)
    {
        gameManager->changeState(std::make_unique<BattleState>(gameManager, blueTeamSelection.pokemonNames, redTeamSelection.pokemonNames)); // Transition vers la bataille
    }
}

/*==============================================================================
|                          GESTION DES GRAPHISMES                              |
==============================================================================*/
void SelectionState::render(sf::RenderWindow &window)
{
    window.clear();
    window.draw(backgroundSprite);

    // Affiche les Pokémon
    for (size_t i = 0; i < pokemonSprites.size(); i++)
    {
        int row = i / 5;
        int col = i % 5;
        pokemonSprites[i].setPosition(60 + col * 180, 30 + row * 150);
        pokemonSprites[i].setScale(0.7f, 0.7f);
        window.draw(pokemonSprites[i]);
    }

    // Affiche les boîtes de sélection pour l'équipe rouge
    for (const auto &box : redTeamSelection.selectedBoxes)
    {
        window.draw(box);
    }

    // Affiche les boîtes de sélection pour l'équipe bleue
    for (const auto &box : blueTeamSelection.selectedBoxes)
    {
        window.draw(box);
    }

    // Affiche la boîte de sélection actuelle pour l'équipe rouge, si elle n'est pas prête
    if (!redTeamSelection.isReady)
    {
        int redRow = redTeamSelection.selectionIndex / 5;
        int redCol = redTeamSelection.selectionIndex % 5;
        redTeamSelection.currentBox.setPosition(60 - 3 + redCol * 180, 30 - 3 + redRow * 150);
        window.draw(redTeamSelection.currentBox);
    }

    // Affiche la boîte de sélection actuelle pour l'équipe bleue, si elle n'est pas prête
    if (!blueTeamSelection.isReady)
    {
        int blueRow = blueTeamSelection.selectionIndex / 5;
        int blueCol = blueTeamSelection.selectionIndex % 5;
        blueTeamSelection.currentBox.setPosition(60 + blueCol * 180, 30 + blueRow * 150);
        window.draw(blueTeamSelection.currentBox);
    }

    window.display();
}
