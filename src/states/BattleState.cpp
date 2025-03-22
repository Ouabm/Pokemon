#include "../../include/states/BattleState.hpp" // Etat actuel ou l'on se trouve
#include "../../include/states/EndState.hpp"    // Sert uniquement pour la transition

#include "../../include/GameStateManager.hpp"
#include "../../include/PokemonManager.hpp"

BattleState::BattleState(GameStateManager *manager, const std::vector<std::string> &redTeamNames, const std::vector<std::string> &blueTeamNames) : GameState(manager)
{
    ResourceManager::getInstance().playMusic("BattleStateMusic", 50.0f, true);
    backgroundSprite.setTexture(ResourceManager::getInstance().getTexture("BattleStateBG"));

    // Création des Pokémon choisis
    std::vector<Pokemon *> pokemons = {
        PokemonManager::getInstance().getPokemonByName(blueTeamNames[0]),
        PokemonManager::getInstance().getPokemonByName(blueTeamNames[1]),
        PokemonManager::getInstance().getPokemonByName(redTeamNames[0]),
        PokemonManager::getInstance().getPokemonByName(redTeamNames[1])};

    for (const auto &p : pokemons)
        std::cout << p->getName() << std::endl;

    // Définition des tailles et positions des boutons
    const sf::Vector2f buttonSize(200, 40);
    const std::vector<sf::Vector2f> movePositions = {{40, 540}, {250, 540}, {40, 590}, {250, 590}, {600, 540}, {810, 540}, {600, 590}, {810, 590}};

    // Création des boutons avec une boucle
    for (size_t i = 0; i < movePositions.size(); i++)
    {
        moveButtons.push_back(createButton("BattleStateFont", "moveButton" + std::to_string(i + 1), buttonSize, movePositions[i], sf::Color::White, sf::Color::Black));
    }
}

void BattleState::handleInput(sf::RenderWindow &window)
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
                gameManager->changeState(std::make_unique<EndState>(gameManager)); // Transition vers EndState
            }
        }
    }
}

void BattleState::update() {}

void BattleState::render(sf::RenderWindow &window)
{
    window.clear();

    // Affichage de l'arrière-plan
    window.draw(backgroundSprite);

    // Dessiner tous les boutons dynamiquement
    for (const auto &button : moveButtons)
    {
        window.draw(button.shape);
        window.draw(button.text);
    }

    window.display();
}
