#include "../../include/states/BattleState.hpp"


#include "../../include/GameStateManager.hpp"
#include "EndState.hpp"
#include "ElementUI.hpp"

BattleState::BattleState(GameStateManager *manager) : GameState(manager)
{
    ResourceManager::getInstance().playMusic("BattleStateMusic", 50.0f, true);

    battleText = createText("EndStateFont", "Coucou les chinois", 24, sf::Color::White, sf::Vector2f(50, 200));
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
                gameManager->changeState(std::make_unique<EndState>(gameManager));  // Transition vers EndState
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
