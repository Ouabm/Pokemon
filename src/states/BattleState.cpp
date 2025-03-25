#include "BattleState.hpp"
#include "EndState.hpp"

#include "GameParameters.hpp"
#include "GameStateManager.hpp"
#include "PokemonManager.hpp"

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
    std::vector<sf::Vector2f> redTeamPokemonPositions = {{600.0, 170.0}, {750.0, 170.0}};

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
        if (blueTeamStruct.pokemons[0]->getHpRestant() == 0 && blueTeamStruct.pokemons[1]->getHpRestant() == 0)
        {
            gameManager->changeState(std::make_unique<EndState>(gameManager, "Red Win "));
        }
        else
        {
            gameManager->changeState(std::make_unique<EndState>(gameManager, "Blue Win "));
        }
    }

    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::KeyPressed:
            handleKeyPress(event);

            if (event.key.code == sf::Keyboard::A)
            {
                // Affichage des valeurs pour l'équipe bleue
                std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++:" << std::endl;
                std::cout << "Équipe Bleue:" << std::endl;
                std::cout << "activePokemon: " << blueTeamStruct.activePokemon << std::endl;
                std::cout << "isMoveChosen: " << std::boolalpha << blueTeamStruct.isMoveChosen << std::endl;
                std::cout << "isTargetChosen: " << std::boolalpha << blueTeamStruct.isTargetChosen << std::endl;
                std::cout << "pokemonTargeted: " << blueTeamStruct.pokemonTargeted << std::endl;

                // Affichage des valeurs pour l'équipe rouge
                std::cout << "\nÉquipe Rouge:" << std::endl;
                std::cout << "activePokemon: " << redTeamStruct.activePokemon << std::endl;
                std::cout << "isMoveChosen: " << std::boolalpha << redTeamStruct.isMoveChosen << std::endl;
                std::cout << "isTargetChosen: " << std::boolalpha << redTeamStruct.isTargetChosen << std::endl;
                std::cout << "pokemonTargeted: " << redTeamStruct.pokemonTargeted << std::endl;
            }
            break;
        }
    }
}

/* ================ SOUS-FONCTIONS POUR LA GESTION DES ENTRÉES ================*/
void BattleState::handleKeyPress(const sf::Event &event)
{
    // Gérer les touches pour l'équipe bleue (ZQSD)
    std::array<sf::Keyboard::Key, 4> blueTeamMoveKeys = {sf::Keyboard::Z, sf::Keyboard::Q, sf::Keyboard::S, sf::Keyboard::D};
    // Gérer les touches pour l'équipe rouge (flèches)
    std::array<sf::Keyboard::Key, 4> redTeamMoveKeys = {sf::Keyboard::Up, sf::Keyboard::Left, sf::Keyboard::Down, sf::Keyboard::Right};

    // L'équipe bleue

    if (!blueTeamStruct.isMoveChosen)
    {
        // Process les key
        for (size_t i = 0; i < blueTeamMoveKeys.size(); ++i)
        {
            if (event.key.code == blueTeamMoveKeys[i])
            {
                blueTeamStruct.currentMove = blueTeamStruct.pokemons[blueTeamStruct.activePokemon]->getMoves()[i];
                std::cout << "Move " << (i + 1) << " choisi pour l'équipe bleue." << std::endl;

                // Change l'outline pour le bouton du move choisi
                resetMoveButtonsOutline(blueTeamStruct);
                blueTeamStruct.moveButtons[i].shape.setOutlineColor(sf::Color::Blue);
                blueTeamStruct.moveButtons[i].shape.setOutlineThickness(3);
                blueTeamStruct.moveButtons[i].shape.setFillColor(sf::Color(100, 100, 255, 230));
                break; // Sortir dès qu'un mouvement est choisi
            }
        }
    }
    if (event.key.code == sf::Keyboard::Tab)
    {
        if (!blueTeamStruct.isMoveChosen)
        {
            if (countAlivePokemons(blueTeamStruct) == 2)
            {
                blueTeamStruct.currentMove = nullptr;
                blueTeamStruct.activePokemon = (blueTeamStruct.activePokemon + 1) % blueTeamStruct.pokemons.size();
                resetMoveButtonsOutline(blueTeamStruct);
            }
        }

        if (blueTeamStruct.isMoveChosen && !blueTeamStruct.isTargetChosen)
        {
            if (countAlivePokemons(redTeamStruct) == 2)
            {
                size_t nextIndex = (blueTeamStruct.pokemonTargeted + 1) % blueTeamStruct.pokemons.size();
                blueTeamStruct.pokemonTargeted = nextIndex;
            }
            else
            {
                std::cout << "Impossible: le Pokémon ciblé est KO." << std::endl;
            }
        }
    }

    // L'équipe rouge
    if (!redTeamStruct.isMoveChosen)
    {
        for (size_t i = 0; i < redTeamMoveKeys.size(); ++i)
        {
            if (event.key.code == redTeamMoveKeys[i])
            {
                redTeamStruct.currentMove = redTeamStruct.pokemons[redTeamStruct.activePokemon]->getMoves()[i];
                std::cout << "Move " << (i + 1) << " choisi pour l'équipe rouge." << std::endl;

                // Change l'outline pour le bouton du move choisi
                resetMoveButtonsOutline(redTeamStruct);
                redTeamStruct.moveButtons[i].shape.setOutlineColor(sf::Color::Red);
                redTeamStruct.moveButtons[i].shape.setOutlineThickness(3);
                redTeamStruct.moveButtons[i].shape.setFillColor(sf::Color(255, 100, 100, 230));
                break; // Sortir dès qu'un mouvement est choisi
            }
        }
    }
    if (event.key.code == sf::Keyboard::P)
    {
        if (!redTeamStruct.isMoveChosen)
        {
            if (countAlivePokemons(redTeamStruct) == 2)
            {
                redTeamStruct.currentMove = nullptr;
                redTeamStruct.activePokemon = (redTeamStruct.activePokemon + 1) % redTeamStruct.pokemons.size();
                resetMoveButtonsOutline(redTeamStruct);
            }
        }

        if (redTeamStruct.isMoveChosen && !redTeamStruct.isTargetChosen)
        {
            if (countAlivePokemons(blueTeamStruct) == 2)
            {
                size_t nextIndex = (redTeamStruct.pokemonTargeted + 1) % redTeamStruct.pokemons.size();
                redTeamStruct.pokemonTargeted = nextIndex;
            }
            else
            {
                std::cout << "Impossible: le Pokémon ciblé est KO." << std::endl;
            }
        }
    }

    // Validation du mouvement et changement de cible (Space et Tab)
    if (event.key.code == sf::Keyboard::Space)
    {
        processEnterKey(blueTeamStruct);
    }

    if (event.key.code == sf::Keyboard::Enter)
    {
        processEnterKey(redTeamStruct);
    }
}

void BattleState::processEnterKey(BattleTeamStruct &currentTeam)
{
    // Si aucun mouvement n'a encore été choisi
    if (!currentTeam.isMoveChosen)
    {
        // Vérifier si un mouvement a été choisi
        if (currentTeam.currentMove != nullptr)
        {
            // Afficher quel mouvement a été choisi pour l'équipe correspondante
            std::cout << "Move de l'équipe " << (&currentTeam == &blueTeamStruct ? "bleue" : "rouge") << " validé." << std::endl;

            // Marquer que le mouvement a été choisi
            currentTeam.isMoveChosen = true;
        }
        else
        {
            // Si aucun mouvement n'a été sélectionné, afficher un message
            std::cout << "Aucun mouvement choisi." << std::endl;
        }
    }
    // Si un mouvement a été choisi, mais que la cible n'a pas encore été choisie
    else if (!currentTeam.isTargetChosen && currentTeam.isMoveChosen)
    {
        // Marquer la cible comme choisie
        currentTeam.isTargetChosen = true;
        currentTeam.isReady = true;

        // Afficher que la cible a été choisie
        std::cout << "Cible choisie pour l'équipe " << (&currentTeam == &blueTeamStruct ? "bleue" : "rouge") << "." << std::endl;
    }
}

int BattleState::countAlivePokemons(const BattleTeamStruct &team)
{
    int aliveCount = 0;
    for (const auto &pokemon : team.pokemons)
    {
        if (pokemon->getHpRestant() > 0)
            ++aliveCount;
    }
    return aliveCount;
}

void BattleState::resetMoveButtonsOutline(BattleTeamStruct &currentTeam)
{
    for (size_t i = 0; i < 4; i++)
    {
        currentTeam.moveButtons[i].shape.setOutlineThickness(0);         // Remet l'épaisseur de l'outline par défaut
        currentTeam.moveButtons[i].shape.setFillColor(sf::Color::White); // Remet l'épaisseur de l'outline par défaut
    }
}

/*==============================================================================
|                            GESTION DES UPDATES                               |
==============================================================================*/
void BattleState::update()
{
    // Exemple : vérifier si le combat est terminé
    // if (checkBattleOver())

    if (blueTeamStruct.isReady && redTeamStruct.isReady)
    {
        turnHandeler(blueTeamStruct, redTeamStruct);
    }
}

// ================ SOUS-FONCTIONS POUR LA GESTION DES UPDATE ================//
bool BattleState::checkBattleOver()
{
    auto checkFaintedForTeam = [](BattleTeamStruct &teamStruct)
    { return (teamStruct.pokemons[0]->getHpRestant() == 0 && teamStruct.pokemons[1]->getHpRestant() == 0); };

    return checkFaintedForTeam(blueTeamStruct) || checkFaintedForTeam(redTeamStruct);
}

void BattleState::updateHealthBars(BattleTeamStruct &teamStruct)
{
    auto updateHealthBar = [](sf::RectangleShape &bar, float healthPercentage)
    {
        bar.setSize(sf::Vector2f(200 * healthPercentage, bar.getSize().y));

        int red = 0, green = 0;
        if (healthPercentage > 0.8f)
            red = 0, green = 255; // Vert pur
        else if (healthPercentage > 0.5f)
            red = static_cast<int>(255 * (1.0f - (healthPercentage - 0.5f) * 3.333)), green = 255; // Vert à Jaune
        else if (healthPercentage > 0.2f)
            red = 255, green = static_cast<int>(255 * ((healthPercentage - 0.2f) * 3.333)); // Jaune à Orange
        else
            red = 255; // Rouge pur

        bar.setFillColor(sf::Color(red, green, 0));
    };

    // Mise à jour des barres de vie pour chaque Pokémon de l'équipe
    for (size_t i = 0; i < teamStruct.pokemons.size(); ++i)
    {
        if (i < teamStruct.healthBars.size())
        {
            float healthPercentage = static_cast<float>(teamStruct.pokemons[i]->getHpRestant()) / teamStruct.pokemons[i]->getHp();
            updateHealthBar(teamStruct.healthBars[i], healthPercentage);
        }
    }
}

void BattleState::turnHandeler(BattleTeamStruct &blueTeamStruct, BattleTeamStruct &redTeamStruct)
{
    int blueSpeed = blueTeamStruct.pokemons[blueTeamStruct.activePokemon]->getSpeed();
    int redSpeed = redTeamStruct.pokemons[redTeamStruct.activePokemon]->getSpeed();

    if (blueSpeed == redSpeed) // Si vitesse egale on fait au hasard
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

    if (blueSpeed > redSpeed) //Pour savoir qui agit en premier on regarde les vitesse
    {
        int damage1 = calculDamage(*blueTeamStruct.pokemons[blueTeamStruct.activePokemon], *redTeamStruct.pokemons[blueTeamStruct.pokemonTargeted], *blueTeamStruct.currentMove);
        std::cout << "Dammage1 : " << damage1 << std::endl;
        int oldHp1 = redTeamStruct.pokemons[blueTeamStruct.pokemonTargeted]->getHpRestant();
        int newHp1 = std::max(0, oldHp1 - damage1);
        redTeamStruct.pokemons[blueTeamStruct.pokemonTargeted]->setHpRestant(newHp1);
        std::cout << "PV du Pokémon rouge attaqué: " << oldHp1 << " -> " << newHp1 << std::endl;
        updateHealthBars(redTeamStruct);

        if (redTeamStruct.pokemons[redTeamStruct.activePokemon]->getHpRestant() > 0)
        {
            int damage2 = calculDamage(*redTeamStruct.pokemons[redTeamStruct.activePokemon], *blueTeamStruct.pokemons[redTeamStruct.pokemonTargeted], *redTeamStruct.currentMove);
            std::cout << "Dammage2 : " << damage2 << std::endl;
            int oldHp = blueTeamStruct.pokemons[redTeamStruct.pokemonTargeted]->getHpRestant();
            int newHp = std::max(0, oldHp - damage2);
            blueTeamStruct.pokemons[redTeamStruct.pokemonTargeted]->setHpRestant(newHp);
            std::cout << "PV du Pokémon bleu attaqué: " << oldHp << " -> " << newHp << std::endl;
            updateHealthBars(blueTeamStruct);
        }
    }
    else
    {
        int damage2 = calculDamage(*redTeamStruct.pokemons[redTeamStruct.activePokemon], *blueTeamStruct.pokemons[redTeamStruct.pokemonTargeted], *redTeamStruct.currentMove);
        std::cout << "Dammage2 : " << damage2 << std::endl;
        int oldHp = blueTeamStruct.pokemons[redTeamStruct.pokemonTargeted]->getHpRestant();
        int newHp = std::max(0, oldHp - damage2);
        blueTeamStruct.pokemons[redTeamStruct.pokemonTargeted]->setHpRestant(newHp);
        std::cout << "PV du Pokémon bleu attaqué: " << oldHp << " -> " << newHp << std::endl;
        updateHealthBars(blueTeamStruct);

        if (blueTeamStruct.pokemons[blueTeamStruct.activePokemon]->getHpRestant() > 0)
        {
            int damage1 = calculDamage(*blueTeamStruct.pokemons[blueTeamStruct.activePokemon], *redTeamStruct.pokemons[blueTeamStruct.pokemonTargeted], *blueTeamStruct.currentMove);
            std::cout << "Dammage1 : " << damage1 << std::endl;
            int oldHp1 = redTeamStruct.pokemons[blueTeamStruct.pokemonTargeted]->getHpRestant();
            int newHp1 = std::max(0, oldHp1 - damage1);
            redTeamStruct.pokemons[blueTeamStruct.pokemonTargeted]->setHpRestant(newHp1);
            std::cout << "PV du Pokémon rouge attaqué: " << oldHp1 << " -> " << newHp1 << std::endl;
            updateHealthBars(redTeamStruct);
        }
    }

    // Mise a jour

    if (blueTeamStruct.pokemons[blueTeamStruct.activePokemon]->getHpRestant() == 0)
    {
        blueTeamStruct.activePokemon = blueTeamStruct.activePokemon == 0 ? 1 : 0;
    }
    if (blueTeamStruct.pokemons[redTeamStruct.pokemonTargeted]->getHpRestant() == 0)
    {
        redTeamStruct.pokemonTargeted = redTeamStruct.pokemonTargeted == 0 ? 1 : 0;
    }
    if (redTeamStruct.pokemons[redTeamStruct.activePokemon]->getHpRestant() == 0)
    {
        redTeamStruct.activePokemon = redTeamStruct.activePokemon == 0 ? 1 : 0;
    }
    if (redTeamStruct.pokemons[blueTeamStruct.pokemonTargeted]->getHpRestant() == 0)
    {
        blueTeamStruct.pokemonTargeted = blueTeamStruct.pokemonTargeted == 0 ? 1 : 0;
    }

    blueTeamStruct.currentMove = nullptr;
    blueTeamStruct.isMoveChosen = false;
    blueTeamStruct.isTargetChosen = false;
    blueTeamStruct.isReady = false;

    redTeamStruct.currentMove = nullptr;
    redTeamStruct.isMoveChosen = false;
    redTeamStruct.isTargetChosen = false;
    redTeamStruct.isReady = false;

    resetMoveButtonsOutline(blueTeamStruct);
    resetMoveButtonsOutline(redTeamStruct);
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

    for (size_t i = 0; i < teamStruct.pokemons.size(); i++)
    {
        window.draw(teamStruct.healthBars[i]);
        window.draw(teamStruct.barsText[i]);
    }
}

void BattleState::drawTargetIndicator(sf::RenderWindow &window, BattleTeamStruct &teamStruct)
{
    // Vérifie si un Pokémon est ciblé et si un mouvement a été choisi
    if (!teamStruct.isTargetChosen && teamStruct.isMoveChosen)
    {
        // Détermine l'équipe active et l'équipe adverse
        BattleTeamStruct &currentTeam = teamStruct;
        BattleTeamStruct &opponentTeam = (&teamStruct == &blueTeamStruct) ? redTeamStruct : blueTeamStruct;

        // Récupère le Pokémon ciblé et sa position
        const auto &targetPokemonSprite = opponentTeam.pokemonSprites[currentTeam.pokemonTargeted];
        sf::FloatRect targetBounds = targetPokemonSprite.getGlobalBounds();
        sf::Vector2f targetPos = targetPokemonSprite.getPosition();
        targetPos.x += targetBounds.width / 2;
        targetPos.y += targetBounds.height / 2;

        // Positionne l'indicateur de ciblage
        currentTeam.targetIndicator.setPosition(targetPos);
        window.draw(currentTeam.targetIndicator);

        // Crée et affiche un texte de mode de ciblage
        static sf::Text targetingText = createText("BattleStateFont", "TARGETING MODE - Press Tab to cycle targets", 16, sf::Color::Red, {320, 30});
        window.draw(targetingText);
    }
}
