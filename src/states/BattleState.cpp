#include "../../include/states/BattleState.hpp"
#include "../../include/GameStateManager.hpp"
#include "EndState.hpp"
#include "ElementUI.hpp"
#include "../../include/PokemonManager.hpp"

BattleState::BattleState(GameStateManager *manager, const std::vector<std::string> &redTeamNames, const std::vector<std::string> &blueTeamNames)
    : GameState(manager)
{
    // Musique et texte de combat
    ResourceManager::getInstance().playMusic("BattleStateMusic", 50.0f, true);
    battleText = createText("EndStateFont", "Début du combat !", 24, sf::Color::White, sf::Vector2f(50, 200));


    Pokemon* a = PokemonManager::getInstance().getPokemonByName(blueTeamNames[0]);
    Pokemon* b = PokemonManager::getInstance().getPokemonByName(blueTeamNames[1]);
    Pokemon* c = PokemonManager::getInstance().getPokemonByName(redTeamNames[0]);
    Pokemon* d = PokemonManager::getInstance().getPokemonByName(redTeamNames[1]);

    std::cout << a->getName() << std::endl;
    std::cout << b->getName() << std::endl;
    std::cout << c->getName() << std::endl;
    std::cout << d->getName() << std::endl;

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
    window.draw(battleText);

    window.display();
}
