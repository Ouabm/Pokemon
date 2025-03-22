#include "../../include/states/BattleState.hpp"
#include "../../include/states/EndState.hpp"

#include "../../include/GameStateManager.hpp"
#include "../../include/PokemonManager.hpp"

BattleState::BattleState(GameStateManager *manager, const std::vector<std::string> &blueTeamPokemonsNames, const std::vector<std::string> &redTeamPokemonsNames) : GameState(manager)
{
    // =================== GRAPHISMES ===================
    // Joue la musique de fond
    ResourceManager::getInstance().playMusic("BattleStateMusic", 50.0f, true);
    backgroundSprite.setTexture(ResourceManager::getInstance().getTexture("BattleStateBG"));

    std::vector<sf::Vector2f> blueTeamPositions = {{100.0, 200.0}, {200.0, 200.0}};
    std::vector<sf::Vector2f> redTeamPositions = {{100.0, 400.0}, {200.0, 400.0}};

    loadPokemonTeamSprites(blueTeamPokemonsNames, blueTeamStruct, blueTeamPositions, true);
    loadPokemonTeamSprites(redTeamPokemonsNames, redTeamStruct, redTeamPositions, false);

    // Charge les équipes
    loadPokemonTeamsInfos(blueTeamPokemonsNames, redTeamPokemonsNames);

    // Initialise les boutons et les sprites
    createMoveButtons();
    initHealthBars();
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
            gameManager->changeState(std::make_unique<EndState>(gameManager));
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            // Vérifie si un bouton de changement de Pokémon a été cliqué
            if (blueTeamStruct.switchButton.shape.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            {
                blueTeamStruct.activePokemon = (blueTeamStruct.activePokemon + 1) % blueTeamStruct.pokemons.size();
            }
            if (redTeamStruct.switchButton.shape.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            {
                redTeamStruct.activePokemon = (redTeamStruct.activePokemon + 1) % redTeamStruct.pokemons.size();
            }
        }
    }
}

void BattleState::update()
{
    // Exemple : vérifier si le combat est terminé
    if (checkBattleOver())
    {
        gameManager->changeState(std::make_unique<EndState>(gameManager));
    }
}

void BattleState::render(sf::RenderWindow &window)
{
    window.clear();
    window.draw(backgroundSprite);

    drawPokemonTeam(window, blueTeamStruct);
    drawPokemonTeam(window, redTeamStruct);

    drawMoveButtons(window, blueTeamStruct);
    drawMoveButtons(window, redTeamStruct);

    window.display();
}

// =================== CHARGEMENT DES TEAMS ===================
void BattleState::loadPokemonTeamsInfos(const std::vector<std::string> &blueTeamNames, const std::vector<std::string> &redTeamNames)
{
    blueTeamStruct.pokemons = {
        PokemonManager::getInstance().getPokemonByName(blueTeamNames[0]),
        PokemonManager::getInstance().getPokemonByName(blueTeamNames[1])};

    redTeamStruct.pokemons = {
        PokemonManager::getInstance().getPokemonByName(redTeamNames[0]),
        PokemonManager::getInstance().getPokemonByName(redTeamNames[1])};
}

void BattleState::loadPokemonTeamSprites(const std::vector<std::string> &teamPokemonsNames, PokemonTeam &teamStruct, const std::vector<sf::Vector2f> &initPos, bool reverseTexture)
{
    teamStruct.pokemonSprites.clear(); // Nettoyer la liste des sprites avant d'ajouter les nouveaux

    for (size_t i = 0; i < teamPokemonsNames.size(); i++)
    {
        sf::Sprite sprite;
        std::string extension = reverseTexture ? "Back" : "";
        sprite.setTexture(ResourceManager::getInstance().getTexture(teamPokemonsNames[i] + extension));

        // Vérifier s'il y a une position fournie pour ce sprite
        if (i < initPos.size())
            sprite.setPosition(initPos[i]);
        else
            sprite.setPosition(0, 0); // Position par défaut si pas assez de positions

        sprite.setScale(0.7f, 0.7f);
        teamStruct.pokemonSprites.push_back(sprite); // Ajouter le sprite au vecteur
    }
}

void BattleState::initHealthBars()
{
    // Initialisation des barres de vie
}

void BattleState::updateHealthBars()
{
    // Mise à jour des barres de vie
}

// =================== BOUTONS ===================
void BattleState::createMoveButtons()
{
    const sf::Vector2f buttonSize(200, 40);
    const std::vector<sf::Vector2f> blueMovePositions = {{40, 540}, {250, 540}, {40, 590}, {250, 590}};
    const std::vector<sf::Vector2f> redMovePositions = {{600, 540}, {810, 540}, {600, 590}, {810, 590}};

    for (size_t i = 0; i < 4; i++)
    {
        blueTeamStruct.moveButtons.push_back(createButton("BattleStateFont", blueTeamStruct.pokemons[blueTeamStruct.activePokemon]->getMoves()[i]->getName(), buttonSize, blueMovePositions[i], 20, sf::Color::White, sf::Color::Black));
        redTeamStruct.moveButtons.push_back(createButton("BattleStateFont", redTeamStruct.pokemons[redTeamStruct.activePokemon]->getMoves()[i]->getName(), buttonSize, redMovePositions[i], 20, sf::Color::White, sf::Color::Black));
    }

    // Boutons pour changer de Pokémon
    blueTeamStruct.switchButton = createButton("BattleStateFont", "SwitchBlue", buttonSize, {400, 300}, 20, sf::Color::Blue, sf::Color::Black);
    redTeamStruct.switchButton = createButton("BattleStateFont", "SwitchRed", buttonSize, {600, 300}, 20, sf::Color::Red, sf::Color::Black);
}

void BattleState::drawPokemonTeam(sf::RenderWindow &window, PokemonTeam &teamStruct)
{
    for (auto &sprite : teamStruct.pokemonSprites)
    {
        window.draw(sprite);
    }
}

void BattleState::drawMoveButtons(sf::RenderWindow &window, PokemonTeam &teamStruct)
{
    for (size_t i = 0; i < 4; i++)
    {
        teamStruct.moveButtons[i].text.setString(teamStruct.pokemons[teamStruct.activePokemon]->getMoves()[i]->getName());
        window.draw(teamStruct.moveButtons[i].shape);
        window.draw(teamStruct.moveButtons[i].text);
    }

    window.draw(teamStruct.switchButton.shape);
    window.draw(teamStruct.switchButton.text);
}

// =================== LOGIQUE DU JEU ===================
bool BattleState::checkBattleOver()
{
    bool blueDefeated = checkFainted(blueTeamStruct.pokemons[0]) && checkFainted(blueTeamStruct.pokemons[1]);
    bool redDefeated = checkFainted(redTeamStruct.pokemons[0]) && checkFainted(redTeamStruct.pokemons[1]);
    return redDefeated || blueDefeated;
}

bool BattleState::checkFainted(Pokemon *pokemon)
{
    return pokemon->getHpRestant() <= 0;
}
