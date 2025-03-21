#include "../../include/states/SelectionState.hpp"
#include <iostream>

SelectionState::SelectionState(GameStateManager *manager) : GameState(manager)
{
    // Lecture de la musique de fond
    ResourceManager::getInstance().playMusic("SelectionStateMusic", 50.0f, true);

    // Chargement de l'arrière-plan
    backgroundSprite.setTexture(ResourceManager::getInstance().getTexture("SelectionStateBG"));

    // Récupérer les noms des Pokémon depuis PokemonManager
    std::vector<std::string> pokemonNames = PokemonManager::getInstance().getAllPokemonNames();

    // Charger les sprites des Pokémon en fonction de leurs noms
    for (const std::string &name : pokemonNames)
    {
        sf::Sprite sprite;
        sprite.setTexture(ResourceManager::getInstance().getTexture(name));
        pokemonSprites.push_back(sprite);
    }

    Pokemon* a = PokemonManager::getInstance().getPokemonByName("Pikachu");

    std::cout << typeToString(a->getType1()) << std::endl; // CA MARCHE INCROYALE LA STRUCTURE DE REVE

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
            if (event.key.code == sf::Keyboard::Enter) // A modifier selon ton choix de touche
            {
                gameManager->changeState(std::make_unique<BattleState>(gameManager)); // Transition vers BattleState
            }
        }
    }
}

void SelectionState::update() {}

void SelectionState::render(sf::RenderWindow &window)
{
    window.clear();
    window.draw(backgroundSprite); // Dessiner l'arrière-plan

    // Afficher les sprites des Pokémon
    for (size_t i = 0; i < pokemonSprites.size(); i++)
    {
        int row = i / 5;
        int col = i % 5;
        pokemonSprites[i].setPosition(60 + col * 180, 30 + row * 150);
        pokemonSprites[i].setScale(0.7f, 0.7f); // Ajuster la taille
        window.draw(pokemonSprites[i]); // Dessiner chaque sprite de Pokémon
    }

    window.display();
}
