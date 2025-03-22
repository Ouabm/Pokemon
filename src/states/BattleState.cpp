#include "../../include/states/BattleState.hpp"
#include "../../include/states/EndState.hpp"

#include "../../include/GameStateManager.hpp"
#include "../../include/PokemonManager.hpp"

BattleState::BattleState(GameStateManager *manager, const std::vector<std::string> &blueTeamNames, const std::vector<std::string> &redTeamNames) : GameState(manager)
{
    // Joue la musique de fond
    ResourceManager::getInstance().playMusic("BattleStateMusic", 50.0f, true);
    backgroundSprite.setTexture(ResourceManager::getInstance().getTexture("BattleStateBG"));

    // Crée les boutons pour les actions du combat
    createMoveButtons();

    // Charge les sprites des Pokémon de l'équipe bleue
    loadTeamSprites(blueTeamNames, blueTeamPokemonSprites);

    // Charge les Pokémon des deux équipes
    loadTeamPokemons(blueTeamNames, redTeamNames);
}

void BattleState::handleInput(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (checkBattleOver())
        {
            gameManager->changeState(std::make_unique<EndState>(gameManager)); // Transition vers EndState
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            // Vérifie si l'un des boutons "switch" a été cliqué
            if (moveButtons[8].shape.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            {
                // Changer de Pokémon bleu
                blueActivePokemon = (blueActivePokemon + 1) % blueTeamPokemons.size(); // Cyclique
            }
            if (moveButtons[9].shape.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            {
                // Changer de Pokémon rouge
                redActivePokemon = (redActivePokemon + 1) % redTeamPokemons.size(); // Cyclique
            }
        }
    }
}

void BattleState::update()
{
    // Exemple : vérifie si un Pokémon a fainté
    // for (auto *pokemon : blueTeamPokemons)
    // {
    //     if (pokemon->getHpRestant() <= 0)
    //     {
    //         std::cout << pokemon->getName() << " has fainted!" << std::endl;
    //         pokemon->setHpRestant(0);
    //     }
    // }

    // Exemple : vérifier si le combat est terminé
    // if (checkBattleOver())
    // {
    //     gameManager->changeState(std::make_unique<EndState>(gameManager));
    // }
}

void BattleState::render(sf::RenderWindow &window)
{
    window.clear();
    window.draw(backgroundSprite);

    drawTeamSprites(window);
    drawMoveButtons(window);

    window.display();
}

void BattleState::loadTeamSprites(const std::vector<std::string> &teamNames, std::vector<sf::Sprite> &teamSprites)
{
    for (const std::string &name : teamNames)
    {
        sf::Sprite sprite;
        sprite.setTexture(ResourceManager::getInstance().getTexture(name));
        teamSprites.push_back(sprite);
    }
}

void BattleState::loadTeamPokemons(const std::vector<std::string> &blueTeamNames, const std::vector<std::string> &redTeamNames)
{
    blueTeamPokemons = {
        PokemonManager::getInstance().getPokemonByName(blueTeamNames[0]),
        PokemonManager::getInstance().getPokemonByName(blueTeamNames[1])};

    redTeamPokemons = {
        PokemonManager::getInstance().getPokemonByName(redTeamNames[0]),
        PokemonManager::getInstance().getPokemonByName(redTeamNames[1])};

    // Debug pour afficher les Pokémon de l'équipe bleue
    for (const auto &p : blueTeamPokemons)
    {
        std::cout << p->getName() << std::endl;
        std::cout << typeToString(p->getMoves()[0]->getType()) << std::endl;
        std::cout << p->getMoves()[0]->getName() << std::endl;
    }
}

void BattleState::createMoveButtons()
{
    const sf::Vector2f buttonSize(200, 40);
    const std::vector<sf::Vector2f> blueMovePositions = {{40, 540}, {250, 540}, {40, 590}, {250, 590}};
    const std::vector<sf::Vector2f> redMovePositions = {{600, 540}, {810, 540}, {600, 590}, {810, 590}};

    // Crée des boutons pour les attaques de l'équipe bleue
    for (size_t i = 0; i < 4; i++)
    {
        moveButtons.push_back(createButton("BattleStateFont",
                                           "blueMoveButton" + std::to_string(i + 1), buttonSize,
                                           blueMovePositions[i], sf::Color::White, sf::Color::Black));
    }

    // Crée des boutons pour les attaques de l'équipe rouge
    for (size_t i = 0; i < 4; i++)
    {
        moveButtons.push_back(createButton("BattleStateFont",
                                           "redMoveButton" + std::to_string(i + 1), buttonSize,
                                           redMovePositions[i], sf::Color::White, sf::Color::Black));
    }

    // Crée des boutons pour changer de Pokémon (un pour chaque équipe)
    sf::Vector2f switchButtonPosition(400, 300);
    moveButtons.push_back(createButton("BattleStateFont", "switchBluePokemon", buttonSize, switchButtonPosition, sf::Color::Blue, sf::Color::Black));
    moveButtons.push_back(createButton("BattleStateFont", "switchRedPokemon", buttonSize, {600, 300}, sf::Color::Red, sf::Color::Black));
}

void BattleState::drawTeamSprites(sf::RenderWindow &window)
{
    for (size_t i = 0; i < blueTeamPokemonSprites.size(); i++)
    {
        blueTeamPokemonSprites[i].setPosition(60, 150);
        blueTeamPokemonSprites[i].setScale(0.7f, 0.7f);
        window.draw(blueTeamPokemonSprites[i]);
    }
}

void BattleState::drawMoveButtons(sf::RenderWindow &window)
{
    // Affiche les mouvements pour l'équipe bleue en fonction du Pokémon actif
    for (size_t i = 0; i < 4; i++)
    {
        std::string moveName = blueTeamPokemons[blueActivePokemon]->getMoves()[i]->getName();
        moveButtons[i].text.setString(moveName);
        window.draw(moveButtons[i].shape);
        window.draw(moveButtons[i].text);
    }

    // Affiche les mouvements pour l'équipe rouge en fonction du Pokémon actif
    for (size_t i = 4; i < 8; i++)
    {
        std::string moveName = redTeamPokemons[redActivePokemon]->getMoves()[i - 4]->getName();
        moveButtons[i].text.setString(moveName);
        window.draw(moveButtons[i].shape);
        window.draw(moveButtons[i].text);
    }

    // Affiche les boutons de changement de Pokémon
    window.draw(moveButtons[8].shape); // Switch équipe bleue
    window.draw(moveButtons[8].text);
    window.draw(moveButtons[9].shape); // Switch équipe rouge
    window.draw(moveButtons[9].text);
}

bool BattleState::checkBattleOver()
{
    // Vérifie si les deux Pokémon des équipes ont fainté
    bool blueTeamDefeated = checkFainted(blueTeamPokemons[0]) && checkFainted(blueTeamPokemons[1]);
    bool redTeamDefeated = checkFainted(redTeamPokemons[0]) && checkFainted(redTeamPokemons[1]);

    // Retourne true si l'une des équipes a perdu
    return redTeamDefeated || blueTeamDefeated;
}

bool BattleState::checkFainted(Pokemon *pokemon)
{
    return pokemon->getHpRestant() <= 0;
}
