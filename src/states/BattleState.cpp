#include "BattleState.hpp"
#include "EndState.hpp"

#include "GameStateManager.hpp"
#include "PokemonManager.hpp"

#include "GameParameters.hpp"

#include "DamageCalculator.hpp"

/*==============================================================================
|                               CONSTRUCTEUR                                   |
==============================================================================*/
BattleState::BattleState(GameStateManager *manager, const std::vector<std::string> &blueTeamPokemonsNames, const std::vector<std::string> &redTeamPokemonsNames) : GameState(manager)
{
    // Joue la musique de fond
    ResourceManager::getInstance().playMusic(Battle::Music::BACKGROUND_MUSIC, Battle::Music::VOLUME, true);
    backgroundSprite.setTexture(ResourceManager::getInstance().getTexture("BattleStateBG"));

    std::vector<sf::Vector2f> blueTeamPokemonPositions = {{20.0, 290.0}, {300.0, 290.0}};
    std::vector<sf::Vector2f> redTeamPokemonPositions = {{600.0, 150.0}, {750.0, 150.0}};

    loadPokemonTeamSprites(blueTeamPokemonsNames, blueTeamStruct, blueTeamPokemonPositions, true);
    loadPokemonTeamSprites(redTeamPokemonsNames, redTeamStruct, redTeamPokemonPositions, false);

    // Charge les équipes
    loadPokemonTeamsInfos(blueTeamPokemonsNames, redTeamPokemonsNames);

    createMoveButtons(); // Il faudrait ajouter la thickness comme param a cette fonction
    createHealthBars();
    createTargetIndicator();
}

// ==================== CHARGEMENT DES INFOS DES ÉQUIPES =====================//
void BattleState::loadPokemonTeamSprites(const std::vector<std::string> &teamPokemonsNames, BattleTeamStruct &teamStruct, const std::vector<sf::Vector2f> &initPos, bool reverseTexture)
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

        sprite.setScale(1.f, 1.f);
        teamStruct.pokemonSprites.push_back(sprite); // Ajouter le sprite au vecteur
    }
}

void BattleState::loadPokemonTeamsInfos(const std::vector<std::string> &blueTeamNames, const std::vector<std::string> &redTeamNames)
{
    // Charger les Pokémon pour l'équipe bleue en créant des copies des objets Pokémon
    blueTeamStruct.pokemons = {
        PokemonManager::getInstance().getPokemonByName(blueTeamNames[0])->clone(),
        PokemonManager::getInstance().getPokemonByName(blueTeamNames[1])->clone()};

    // Charger les Pokémon pour l'équipe rouge en créant des copies des objets Pokémon
    redTeamStruct.pokemons = {
        PokemonManager::getInstance().getPokemonByName(redTeamNames[0])->clone(),
        PokemonManager::getInstance().getPokemonByName(redTeamNames[1])->clone()};
}

// ====================== CRÉATION DES BOUTONS DE COMBAT ======================//
void BattleState::createMoveButtons()
{
    // Récupération des dimensions du fond
    float backgroundWidth = backgroundSprite.getLocalBounds().width;
    float backgroundHeight = backgroundSprite.getLocalBounds().height;

    // Décalage pour les positions des attaques
    float moveOffsetX = 19;
    float moveOffsetY = 19;
    float moveOffsetX2 = 10;
    float moveOffsetY2 = 10;

    const sf::Vector2f buttonSize(200, 40);

    sf::Vector2f blueBGMoveButtonPos = {moveOffsetX / 2, backgroundHeight + moveOffsetY / 2};
    sf::Vector2f redBGMoveButtonPos = {backgroundWidth - 2 * buttonSize.x - (1.5f * moveOffsetX) - moveOffsetX2, backgroundHeight + moveOffsetY / 2};
    sf::Vector2f bgSize = {2 * buttonSize.x + moveOffsetX + moveOffsetX2, 2 * buttonSize.y + moveOffsetY + moveOffsetY2};

    // Positions des attaques pour l'équipe bleue
    const std::vector<sf::Vector2f> blueMovePositions = {
        {moveOffsetX, backgroundHeight + moveOffsetY},
        {moveOffsetX + buttonSize.x + moveOffsetX2, backgroundHeight + moveOffsetY},
        {moveOffsetX, backgroundHeight + buttonSize.y + moveOffsetY + moveOffsetY2},
        {moveOffsetX + buttonSize.x + moveOffsetX2, backgroundHeight + buttonSize.y + moveOffsetY + moveOffsetY2}};

    // Positions des attaques pour l'équipe rouge
    const std::vector<sf::Vector2f> redMovePositions = {
        {backgroundWidth - 2 * buttonSize.x - moveOffsetX - moveOffsetX2, backgroundHeight + moveOffsetY},
        {backgroundWidth - buttonSize.x - moveOffsetX, backgroundHeight + moveOffsetY},
        {backgroundWidth - 2 * buttonSize.x - moveOffsetX - moveOffsetX2, backgroundHeight + buttonSize.y + moveOffsetY + moveOffsetY2},
        {backgroundWidth - buttonSize.x - moveOffsetX, backgroundHeight + buttonSize.y + moveOffsetY + moveOffsetY2}};

    for (size_t i = 0; i < 4; i++)
    {
        blueTeamStruct.moveButtons.push_back(createButton(buttonSize, blueMovePositions[i], sf::Color::White, 0.0f, sf::Color::Black, "BattleStateFont", blueTeamStruct.pokemons[blueTeamStruct.activePokemon]->getMoves()[i]->getName(), 11, sf::Color::Black));
        redTeamStruct.moveButtons.push_back(createButton(buttonSize, redMovePositions[i], sf::Color::White, 0.0f, sf::Color::Black, "BattleStateFont", redTeamStruct.pokemons[redTeamStruct.activePokemon]->getMoves()[i]->getName(), 11, sf::Color::Black));
    }

    blueTeamStruct.bgMoveButtons = createRectangle(bgSize, blueBGMoveButtonPos, sf::Color(100, 100, 200, 230), 2, sf::Color::Blue);
    redTeamStruct.bgMoveButtons = createRectangle(bgSize, redBGMoveButtonPos, sf::Color(200, 100, 100, 230), 2, sf::Color::Red);

    // Boutons pour changer de Pokémon
    sf::Vector2f switchButtonSize = {118, 109};
    sf::Vector2f switchButtonPos = {(backgroundSprite.getLocalBounds().width - switchButtonSize.x) / 2,
                                    (backgroundSprite.getLocalBounds().height + moveOffsetY / 2)};
    switchButton = createButton(switchButtonSize, switchButtonPos, sf::Color(128, 128, 128), 0.0f, sf::Color::Black, "BattleStateFont", "Switch", 14, sf::Color::Black);
}

void BattleState::createHealthBars()
{
    // Positions et tailles pour les barres de fond
    sf::Vector2f blueBGBarsPos = {30, 30};
    sf::Vector2f redBGBarsPos = {backgroundSprite.getLocalBounds().width - 310 - 30, backgroundSprite.getLocalBounds().height - 50 - 30};
    sf::Vector2f bgSizes = {310, 50}; // 210 + 100

    // Positions et tailles pour les barres de vie
    sf::Vector2f barOffset = {105, 5}; // Décalage des barres de vie
    sf::Vector2f barSizes = {200, 15};

    // Initialisation des barres de fond
    blueTeamStruct.bgHealthBar = createRectangle(bgSizes, blueBGBarsPos, sf::Color(100, 100, 100), 3, sf::Color::Black);
    redTeamStruct.bgHealthBar = createRectangle(bgSizes, redBGBarsPos, sf::Color(100, 100, 100), 3, sf::Color::Black);

    // Initialisation des barres de vie et textes pour chaque équipe
    createTeamBars(blueTeamStruct, blueBGBarsPos, barOffset);
    createTeamBars(redTeamStruct, redBGBarsPos, barOffset);
}

void BattleState::createTeamBars(BattleTeamStruct &teamStruct, sf::Vector2f bgPos, sf::Vector2f barOffset)
{
    for (int i = 0; i < teamStruct.pokemons.size(); i++)
    {
        // Positions des barres de vie
        sf::Vector2f barPos = {bgPos.x + barOffset.x, bgPos.y + barOffset.y + (i * 25)};
        teamStruct.healthBars.push_back(createRectangle(sf::Vector2f(200, 15), barPos, sf::Color::Green, 1, sf::Color::Black));

        // Texte à gauche des barres de vie
        sf::Text barText = createText("BattleStateFont", teamStruct.pokemons[i]->getName(), 10, sf::Color::White, {bgPos.x + 6, bgPos.y + barOffset.y + (i * 25)});
        teamStruct.barsText.push_back(barText);
    }
}

void BattleState::createTargetIndicator()
{
    blueTeamStruct.targetIndicator = createCircle(25, {0, 0}, sf::Color(255, 0, 0, 80), 5, sf::Color::Red);
    redTeamStruct.targetIndicator = createCircle(25, {1000, 0}, sf::Color(255, 0, 0, 80), 5, sf::Color::Red);
}

/*==============================================================================
|                        GESTION DES ENTRÉES UTILISATEUR                       |
==============================================================================*/
void BattleState::handleInput(sf::RenderWindow &window)
{
    if (checkBattleOver())
    {
        gameManager->changeState(std::make_unique<EndState>(gameManager));
        endBattle = true;
    }

    static bool enterPressed = false;
    static bool tabPressed = false;

    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                handleMouseClick(window);
            }
            break;

        case sf::Event::KeyPressed:
            handleKeyPress(event, enterPressed, tabPressed);
            break;

        case sf::Event::KeyReleased:
            handleKeyRelease(event, enterPressed, tabPressed);
            break;
        }
    }
}

/* ================ SOUS-FONCTIONS POUR LA GESTION DES ENTRÉES ================*/
void BattleState::handleMouseClick(sf::RenderWindow &window)
{
    BattleTeamStruct &currentTeam = (isBlueTeamTurn) ? blueTeamStruct : redTeamStruct;
    if (!currentTeam.isMoveChosen)
    {
        if (handleSwitchButtonClick(window, currentTeam))
        {
            std::cout << "Pokemon switché (" << (isBlueTeamTurn ? "Equipe bleue" : "Equipe rouge") << "), Nouveau Pokémon: "
                      << currentTeam.pokemons[currentTeam.activePokemon]->getName() << std::endl;
        }

        if (handleMoveButtonClick(window, currentTeam))
        {
            std::cout << "Move (" << (isBlueTeamTurn ? "Equipe bleue" : "Equipe rouge") << "), Move: "
                      << currentTeam.currentMove->getName() << std::endl;
        }
    }
}

bool BattleState::handleSwitchButtonClick(sf::RenderWindow &window, BattleTeamStruct &currentTeam)
{
    if (switchButton.shape.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
    {
        if (countAlivePokemons(currentTeam) == 2)
        {
            currentTeam.currentMove = nullptr;
            currentTeam.activePokemon = (currentTeam.activePokemon + 1) % currentTeam.pokemons.size();
            resetMoveButtonsOutline(currentTeam);
            return true; // Un switch a eu lieu
        }
    }
    return false; // Aucun switch effectué
}

bool BattleState::handleMoveButtonClick(sf::RenderWindow &window, BattleTeamStruct &currentTeam)
{
    for (size_t i = 0; i < 4; i++)
    {
        if (currentTeam.moveButtons[i].shape.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
        {
            currentTeam.currentMove = currentTeam.pokemons[currentTeam.activePokemon]->getMoves()[i];

            // Change l'outline pour le bouton du move choisi
            resetMoveButtonsOutline(currentTeam);
            currentTeam.moveButtons[i].shape.setOutlineColor(isBlueTeamTurn ? sf::Color::Blue : sf::Color::Red);
            currentTeam.moveButtons[i].shape.setOutlineThickness(3);
            currentTeam.moveButtons[i].shape.setFillColor(isBlueTeamTurn ? sf::Color(100, 100, 255, 230) : sf::Color(255, 100, 100, 230));

            return true; // Un move a été choisi
        }
    }
    return false; // Aucun move sélectionné
}

int BattleState::countAlivePokemons(const BattleTeamStruct &team)
{
    return std::count_if(team.pokemons.begin(), team.pokemons.end(),
                         [](const auto &pokemon)
                         { return pokemon->getHpRestant() > 0; });
}

void BattleState::resetMoveButtonsOutline(BattleTeamStruct &currentTeam)
{
    for (size_t i = 0; i < 4; i++)
    {
        currentTeam.moveButtons[i].shape.setOutlineThickness(0);         // Remet l'épaisseur de l'outline par défaut
        currentTeam.moveButtons[i].shape.setFillColor(sf::Color::White); // Remet l'épaisseur de l'outline par défaut
    }
}

void BattleState::handleKeyPress(const sf::Event &event, bool &enterPressed, bool &tabPressed)
{
    if (!enterPressed && event.key.code == sf::Keyboard::Enter)
    {
        processEnterKey();
        enterPressed = true;
    }

    if (!tabPressed && event.key.code == sf::Keyboard::Tab)
    {
        processTabKey();
        tabPressed = true;
    }
}

void BattleState::handleKeyRelease(const sf::Event &event, bool &enterPressed, bool &tabPressed)
{
    if (event.key.code == sf::Keyboard::Enter)
        enterPressed = false;
    if (event.key.code == sf::Keyboard::Tab)
        tabPressed = false;
}

void BattleState::processEnterKey()
{
    BattleTeamStruct &currentTeam = (isBlueTeamTurn) ? blueTeamStruct : redTeamStruct;

    if (!currentTeam.isMoveChosen)
    {
        if (currentTeam.currentMove != nullptr)
        {
            std::cout << "Move de l'équipe " << (isBlueTeamTurn ? "bleue" : "rouge") << " validé." << std::endl;
            currentTeam.isMoveChosen = true;
        }
        else
        {
            std::cout << "Aucun mouvement choisi." << std::endl;
        }
    }
    else if (!currentTeam.isTargetChosen && currentTeam.isMoveChosen)
    {
        currentTeam.isTargetChosen = true;
        if (isBlueTeamTurn)
        {
            isBlueTeamTurn = false;
            std::cout << "Debut tour des rouges maintenant." << std::endl;
        }
        else
        {
            isTurnReady = true;
            std::cout << "Fin de la sélection." << std::endl;
            // displayMoveDetails(); // J'ai suppr la fonction flemme de refaire
        }
    }
}

void BattleState::processTabKey()
{
    BattleTeamStruct &currentTeam = isBlueTeamTurn ? blueTeamStruct : redTeamStruct;

    if (currentTeam.isMoveChosen && !currentTeam.isTargetChosen)
    {
        BattleTeamStruct &opponentTeam = isBlueTeamTurn ? redTeamStruct : blueTeamStruct;

        if (countAlivePokemons(opponentTeam) == 2)
        {
            size_t nextIndex = (opponentTeam.pokemonTargeted + 1) % opponentTeam.pokemons.size();
            opponentTeam.pokemonTargeted = nextIndex;
        }
        else
        {
            std::cout << "Impossible: le Pokémon ciblé est KO." << std::endl;
        }
    }
}

/*==============================================================================
|                            GESTION DES UPDATES                               |
==============================================================================*/
void BattleState::update()
{
    // Exemple : vérifier si le combat est terminé
    // if (checkBattleOver())

    if (isTurnReady)
    {
        // executeTurn(blueTeamStruct, redTeamStruct); // Calcul les degats a infliger et recevoir sur chaque pokemons
        int blueSpeed = blueTeamStruct.pokemons[blueTeamStruct.activePokemon]->getSpeed();
        int redSpeed = redTeamStruct.pokemons[redTeamStruct.activePokemon]->getSpeed();

        if (blueSpeed == redSpeed)
        {
            if (rand() % 2 == 1)
            {
                blueSpeed = blueSpeed + 1;
            }
            else
            {
                redSpeed = redSpeed + 1;
            }
        }

        if (blueSpeed > redSpeed)
        {
            int damage1 = calculDamage(*blueTeamStruct.pokemons[blueTeamStruct.activePokemon], *redTeamStruct.pokemons[redTeamStruct.pokemonTargeted], *blueTeamStruct.currentMove);
            std::cout << "Dammage1 : " << damage1 << std::endl;
            int oldHp1 = redTeamStruct.pokemons[redTeamStruct.pokemonTargeted]->getHpRestant();
            int newHp1 = std::max(0, oldHp1 - damage1);
            redTeamStruct.pokemons[redTeamStruct.pokemonTargeted]->setHpRestant(newHp1);
            std::cout << "PV du Pokémon rouge attaqué: " << oldHp1 << " -> " << newHp1 << std::endl;
            updateHealthBars(redTeamStruct);
            if (redTeamStruct.pokemons[redTeamStruct.activePokemon]->getHpRestant() > 0)
            {
                int damage2 = calculDamage(*redTeamStruct.pokemons[redTeamStruct.activePokemon], *blueTeamStruct.pokemons[blueTeamStruct.pokemonTargeted], *redTeamStruct.currentMove);
                std::cout << "Dammage2 : " << damage2 << std::endl;
                int oldHp = blueTeamStruct.pokemons[blueTeamStruct.pokemonTargeted]->getHpRestant();
                int newHp = std::max(0, oldHp - damage2);
                blueTeamStruct.pokemons[blueTeamStruct.pokemonTargeted]->setHpRestant(newHp);
                std::cout << "PV du Pokémon bleu attaqué: " << oldHp << " -> " << newHp << std::endl;
                updateHealthBars(blueTeamStruct);
            }
        }
        else
        {
            int damage2 = calculDamage(*redTeamStruct.pokemons[redTeamStruct.activePokemon], *blueTeamStruct.pokemons[blueTeamStruct.pokemonTargeted], *redTeamStruct.currentMove);
            std::cout << "Dammage2 : " << damage2 << std::endl;
            int oldHp = blueTeamStruct.pokemons[blueTeamStruct.pokemonTargeted]->getHpRestant();
            int newHp = std::max(0, oldHp - damage2);
            blueTeamStruct.pokemons[blueTeamStruct.pokemonTargeted]->setHpRestant(newHp);
            std::cout << "PV du Pokémon bleu attaqué: " << oldHp << " -> " << newHp << std::endl;
            updateHealthBars(blueTeamStruct);
            if (blueTeamStruct.pokemons[blueTeamStruct.activePokemon]->getHpRestant() > 0)
            {
                int damage1 = calculDamage(*blueTeamStruct.pokemons[blueTeamStruct.activePokemon], *redTeamStruct.pokemons[redTeamStruct.pokemonTargeted], *blueTeamStruct.currentMove);
                std::cout << "Dammage1 : " << damage1 << std::endl;
                int oldHp1 = redTeamStruct.pokemons[redTeamStruct.pokemonTargeted]->getHpRestant();
                int newHp1 = std::max(0, oldHp1 - damage1);
                redTeamStruct.pokemons[redTeamStruct.pokemonTargeted]->setHpRestant(newHp1);
                std::cout << "PV du Pokémon rouge attaqué: " << oldHp1 << " -> " << newHp1 << std::endl;
                updateHealthBars(redTeamStruct);
            }
        }

        // Mise a jour

        if (blueTeamStruct.pokemons[blueTeamStruct.activePokemon]->getHpRestant() == 0)
        {
            blueTeamStruct.activePokemon = blueTeamStruct.activePokemon == 0 ? 1 : 0;
            blueTeamStruct.pokemonTargeted = blueTeamStruct.pokemonTargeted == 0 ? 1 : 0;
        }
        if (redTeamStruct.pokemons[redTeamStruct.activePokemon]->getHpRestant() == 0)
        {
            redTeamStruct.activePokemon = redTeamStruct.activePokemon == 0 ? 1 : 0;
            redTeamStruct.pokemonTargeted = redTeamStruct.pokemonTargeted == 0 ? 1 : 0;
        }

        isTurnReady = !isTurnReady;

        blueTeamStruct.currentMove = nullptr;
        blueTeamStruct.isMoveChosen = false;
        blueTeamStruct.isTargetChosen = false;

        redTeamStruct.currentMove = nullptr;
        redTeamStruct.isMoveChosen = false;
        redTeamStruct.isTargetChosen = false;

        isBlueTeamTurn = true;

        resetMoveButtonsOutline(blueTeamStruct);
        resetMoveButtonsOutline(redTeamStruct);
    }
}
// ================ SOUS-FONCTIONS POUR LA GESTION DES UPDATE ================//
bool BattleState::checkBattleOver()
{
    bool blueDefeated = checkFainted(blueTeamStruct);
    bool redDefeated = checkFainted(redTeamStruct);
    return redDefeated || blueDefeated;
}

bool BattleState::checkFainted(BattleTeamStruct &teamStruct)
{
    if (teamStruct.pokemons[0]->getHpRestant() == 0 && teamStruct.pokemons[1]->getHpRestant() == 0)
    {
        std::cout << "Jeu fini" << std::endl;

        return 1;
    }
    else
        return 0;
}

void BattleState::updateHealthBars(BattleTeamStruct &teamStruct)
{
    // Fonction lambda pour mettre à jour chaque barre de vie
    auto updateHealthBar = [](sf::RectangleShape &bar, float healthPercentage)
    {
        bar.setSize(sf::Vector2f(200 * healthPercentage, bar.getSize().y));

        sf::Color color;

        if (healthPercentage > 0.8f)
        {
            // Vert pur
            color = sf::Color(0, 255, 0);
        }
        else if (healthPercentage > 0.5f)
        {
            // Dégradé de Vert à Jaune (Rouge augmente)
            int red = static_cast<int>(255 * (1.0f - (healthPercentage - 0.5f) * 3.333)); // Rougit progressivement
            color = sf::Color(red, 255, 0);
        }
        else if (healthPercentage > 0.2f)
        {
            // Dégradé de Jaune à Orange (Vert diminue)
            int green = static_cast<int>(255 * ((healthPercentage - 0.2f) * 3.333)); // Réduction du vert
            color = sf::Color(255, green, 0);
        }
        else
        {
            // Rouge pur en dessous de 0.2
            color = sf::Color(255, 0, 0);
        }

        bar.setFillColor(color);
    };

    // Parcours de l'équipe et mise à jour des barres de vie
    for (size_t i = 0; i < teamStruct.pokemons.size(); i++)
    {
        if (i < teamStruct.healthBars.size()) // Vérifie qu'on ne dépasse pas le nombre de barres de vie
        {
            float healthPercentage = static_cast<float>(teamStruct.pokemons[i]->getHpRestant()) / teamStruct.pokemons[i]->getHp();
            updateHealthBar(teamStruct.healthBars[i], healthPercentage);
        }
    }
}

/*==============================================================================
|                          GESTION DES GRAPHISMES                              |
==============================================================================*/
void BattleState::render(sf::RenderWindow &window)
{
    window.clear();
    window.draw(backgroundSprite);

    drawPokemonTeam(window, blueTeamStruct);
    drawPokemonTeam(window, redTeamStruct);

    drawMoveButtons(window, blueTeamStruct);
    drawMoveButtons(window, redTeamStruct);

    drawHealthBars(window, blueTeamStruct);
    drawHealthBars(window, redTeamStruct);

    drawTargetIndicator(window, blueTeamStruct);
    drawTargetIndicator(window, redTeamStruct);

    window.display();
}

// ============== SOUS-FONCTIONS POUR LA GESTION DES GRAPHISMES ===============//
void BattleState::drawPokemonTeam(sf::RenderWindow &window, BattleTeamStruct &teamStruct)
{
    for (auto &sprite : teamStruct.pokemonSprites)
    {
        window.draw(sprite);
    }
}

void BattleState::drawMoveButtons(sf::RenderWindow &window, BattleTeamStruct &teamStruct)
{
    window.draw(teamStruct.bgMoveButtons);

    for (size_t i = 0; i < 4; i++)
    {
        // Met à jour le texte sur le bouton avec le nom du mouvement
        teamStruct.moveButtons[i].text.setString(teamStruct.pokemons[teamStruct.activePokemon]->getMoves()[i]->getName());

        sf::FloatRect textBounds = teamStruct.moveButtons[i].text.getLocalBounds();
        sf::FloatRect buttonBounds = teamStruct.moveButtons[i].shape.getLocalBounds();

        // Centre le texte par rapport au bouton
        teamStruct.moveButtons[i].text.setPosition(
            teamStruct.moveButtons[i].shape.getPosition().x + (buttonBounds.width - textBounds.width) / 2,
            teamStruct.moveButtons[i].shape.getPosition().y + (buttonBounds.height - textBounds.height) / 2);

        window.draw(teamStruct.moveButtons[i].shape);
        window.draw(teamStruct.moveButtons[i].text);
    }
    window.draw(switchButton.shape);
    window.draw(switchButton.text);
}

void BattleState::drawHealthBars(sf::RenderWindow &window, BattleTeamStruct &teamStruct)
{
    window.draw(teamStruct.bgHealthBar);

    // Dessiner les barres de vie pour chaque Pokémon
    for (size_t i = 0; i < teamStruct.pokemons.size(); i++)
    {
        // Dessiner les barres de vie
        window.draw(teamStruct.healthBars[i]);
        window.draw(teamStruct.barsText[i]);
    }
}

void BattleState::drawTargetIndicator(sf::RenderWindow &window, BattleTeamStruct &teamStruct)
{
    // Vérifie si un Pokémon est ciblé et si un mouvement a été choisi

    if (!teamStruct.isTargetChosen && teamStruct.isMoveChosen)
    {
        // Obtenez la position du Pokémon ciblé
        BattleTeamStruct &currentTeam = (isBlueTeamTurn) ? redTeamStruct : blueTeamStruct;

        sf::Vector2f targetPos = currentTeam.pokemonSprites[currentTeam.pokemonTargeted].getPosition();
        targetPos.x += currentTeam.pokemonSprites[currentTeam.pokemonTargeted].getGlobalBounds().width / 2;
        targetPos.y += currentTeam.pokemonSprites[currentTeam.pokemonTargeted].getGlobalBounds().height / 2;

        // Positionne l'indicateur de ciblage
        currentTeam.targetIndicator.setPosition(targetPos);
        window.draw(currentTeam.targetIndicator);

        // Ajouter un texte indiquant que le mode de ciblage est actif
        sf::Text targetingText = createText("BattleStateFont", "TARGETING MODE - Press Tab to cycle targets", 16, sf::Color::Red, {320, 30});
        window.draw(targetingText);
    }
}
