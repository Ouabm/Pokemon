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

    // Initialise les boutons et les sprites
    createMoveButtons(); // Il faudrait ajouter la thickness comme param a cette fonction
    createHealthBars();
    createTargetIndicator();
}

// ==================== CHARGEMENT DES INFOS DES ÉQUIPES =====================//
void BattleState::loadPokemonTeamSprites(const std::vector<std::string> &teamPokemonsNames, TeamStruct &teamStruct, const std::vector<sf::Vector2f> &initPos, bool reverseTexture)
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
    const sf::Vector2f buttonSize(200, 40);
    const std::vector<sf::Vector2f> blueMovePositions = {{40, 540}, {250, 540}, {40, 590}, {250, 590}};
    const std::vector<sf::Vector2f> redMovePositions = {{600, 540}, {810, 540}, {600, 590}, {810, 590}};

    for (size_t i = 0; i < 4; i++)
    {
        blueTeamStruct.moveButtons.push_back(createButton("BattleStateFont", blueTeamStruct.pokemons[blueTeamStruct.activePokemon]->getMoves()[i]->getName(), buttonSize, blueMovePositions[i], 14, sf::Color::White, sf::Color::Black));
        redTeamStruct.moveButtons.push_back(createButton("BattleStateFont", redTeamStruct.pokemons[redTeamStruct.activePokemon]->getMoves()[i]->getName(), buttonSize, redMovePositions[i], 14, sf::Color::White, sf::Color::Black));
    }

    // Boutons pour changer de Pokémon
    blueTeamStruct.switchButton = createButton("BattleStateFont", "SwitchBlue", buttonSize, {400, 300}, 14, sf::Color::Blue, sf::Color::Black);
    redTeamStruct.switchButton = createButton("BattleStateFont", "SwitchRed", buttonSize, {600, 300}, 14, sf::Color::Red, sf::Color::Black);
}

void BattleState::createHealthBars()
{
    // Positions et tailles pour les barres de fond
    sf::Vector2f blueBGBarsPos = {100, 30};
    sf::Vector2f redBGBarsPos = {695, 465};
    sf::Vector2f bgSizes = {210 + 100, 50};

    // Positions et tailles pour les barres de vie
    std::vector<sf::Vector2f> blueBarsPos = {{blueBGBarsPos.x + 5 + 100, blueBGBarsPos.y + 5}, {blueBGBarsPos.x + 5 + 100, blueBGBarsPos.y + 5 + 25}};
    std::vector<sf::Vector2f> redBarsPos = {{redBGBarsPos.x + 5 + 100, redBGBarsPos.y + 5}, {redBGBarsPos.x + 5 + 100, redBGBarsPos.y + 5 + 25}};
    sf::Vector2f barSizes = {200, 15};

    // Initialisation des barres de fond et des barres de vie
    for (int i = 0; i < 2; i++)
    {
        // Initialisation des barres de fond
        blueTeamStruct.healthBars.push_back(createRectangle(barSizes, blueBarsPos[i], sf::Color::Green, 1, sf::Color::Black));
        redTeamStruct.healthBars.push_back(createRectangle(barSizes, redBarsPos[i], sf::Color::Green, 1, sf::Color::Black));
    }
    blueTeamStruct.bgHealthBar = createRectangle(bgSizes, blueBGBarsPos, sf::Color(100, 100, 100), 3, sf::Color::Black);
    redTeamStruct.bgHealthBar = createRectangle(bgSizes, redBGBarsPos, sf::Color(100, 100, 100), 3, sf::Color::Black);

    // Ajouter dynamiquement les textes dans les structures avec push_back
    blueTeamStruct.barsText.push_back(createText("BattleStateFont", "Charizard", 10, sf::Color::White, {blueBGBarsPos.x + 6, blueBGBarsPos.y + 6}));
    blueTeamStruct.barsText.push_back(createText("BattleStateFont", "Charizard", 10, sf::Color::White, {blueBGBarsPos.x + 6, blueBGBarsPos.y + 32}));
    redTeamStruct.barsText.push_back(createText("BattleStateFont", "Pikachu", 10, sf::Color::White, {redBGBarsPos.x + 6, redBGBarsPos.y + 6}));
    redTeamStruct.barsText.push_back(createText("BattleStateFont", "Kio", 10, sf::Color::White, {redBGBarsPos.x + 6, redBGBarsPos.y + 32}));
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

    static bool enterPressed = false; // Variable pour savoir si la touche Enter a déjà été pressée
    static bool tabPressed = false;   // Variable pour savoir si la touche Tab a déjà été pressée

    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        // Gestion des clics de souris
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            TeamStruct &currentTeam = (isBlueTeamTurn) ? blueTeamStruct : redTeamStruct;
            if (!currentTeam.isMoveChosen)
            {
                if (handleSwitchButtonClick(window, currentTeam))
                {
                    std::cout << "Pokemon switché (" << (isBlueTeamTurn ? "Equipe bleue" : "Equipe rouge") << "), Nouveau Pokémon: "
                              << currentTeam.pokemons[currentTeam.activePokemon]->getName() << std::endl;
                }

                if (handleMoveButtonClick(window, currentTeam))
                {
                    // Attention si on ne choisi pas de move et qu'on valide => erreur seg car move = nullptr // Ameliorer
                }
            }
        }

        // Gestion de la touche Enter
        if (event.type == sf::Event::KeyPressed && !enterPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                TeamStruct &currentTeam = (isBlueTeamTurn) ? blueTeamStruct : redTeamStruct;

                if (!currentTeam.isMoveChosen)
                {
                    std::cout << "Move de l'équipe " << (isBlueTeamTurn ? "bleue" : "rouge") << " validé." << std::endl;
                    currentTeam.isMoveChosen = true;
                }
                else if (!currentTeam.isTargetChosen)
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

                        // Test pour debug
                        std::cout << blueTeamStruct.pokemons[blueTeamStruct.activePokemon]->getName()
                                  << " qui possède des types: "
                                  << typeToString(blueTeamStruct.pokemons[blueTeamStruct.activePokemon]->getType1())
                                  << "/"
                                  << typeToString(blueTeamStruct.pokemons[blueTeamStruct.activePokemon]->getType2())
                                  << " va attaquer ("
                                  << redTeamStruct.pokemons[redTeamStruct.pokemonTargeted]->getName()
                                  << " qui possède des types: "
                                  << typeToString(redTeamStruct.pokemons[redTeamStruct.pokemonTargeted]->getType1())
                                  << "/"
                                  << typeToString(redTeamStruct.pokemons[redTeamStruct.pokemonTargeted]->getType2())
                                  << ") avec "
                                  << blueTeamStruct.currentMove->getName()
                                  << " qui est un move de type: "
                                  << typeToString(blueTeamStruct.currentMove->getType())
                                  << "." << std::endl;

                        // Test pour debug
                        std::cout << redTeamStruct.pokemons[redTeamStruct.activePokemon]->getName()
                                  << " qui possède des types: "
                                  << typeToString(redTeamStruct.pokemons[redTeamStruct.activePokemon]->getType1())
                                  << "/"
                                  << typeToString(redTeamStruct.pokemons[redTeamStruct.activePokemon]->getType2())
                                  << " va attaquer ("
                                  << blueTeamStruct.pokemons[blueTeamStruct.pokemonTargeted]->getName()
                                  << " qui possède des types: "
                                  << typeToString(blueTeamStruct.pokemons[blueTeamStruct.pokemonTargeted]->getType1())
                                  << "/"
                                  << typeToString(blueTeamStruct.pokemons[blueTeamStruct.pokemonTargeted]->getType2())
                                  << ") avec "
                                  << redTeamStruct.currentMove->getName()
                                  << " qui est un move de type: "
                                  << typeToString(redTeamStruct.currentMove->getType())
                                  << "." << std::endl;
                    }
                }

                enterPressed = true; // On marque que la touche a été pressée pour ne pas répéter l'action
            }

            if (event.key.code == sf::Keyboard::A && isTurnReady)
            {
                int oldHp = blueTeamStruct.pokemons[0]->getHpRestant();
                int newHp = std::max(0, oldHp - 10);
                blueTeamStruct.pokemons[0]->setHpRestant(newHp);

                int oldHp1 = blueTeamStruct.pokemons[1]->getHpRestant();
                int newHp1 = std::max(0, oldHp1 - 10);
                blueTeamStruct.pokemons[1]->setHpRestant(newHp1);

                std::cout << "PV du Pokémon 0: " << oldHp << " -> " << newHp << std::endl;
                std::cout << "PV du Pokémon 1: " << oldHp1 << " -> " << newHp1 << std::endl;
            }
        }

        // Gestion de la touche Tab
        if (event.type == sf::Event::KeyPressed && !tabPressed)
        {
            if (event.key.code == sf::Keyboard::Tab)
            {
                if ((isBlueTeamTurn && blueTeamStruct.isMoveChosen && !blueTeamStruct.isTargetChosen) ||
                    (!isBlueTeamTurn && redTeamStruct.isMoveChosen && !redTeamStruct.isTargetChosen))
                {
                    TeamStruct &currentTeam = (isBlueTeamTurn) ? redTeamStruct : blueTeamStruct;

                    currentTeam.pokemonTargeted = (currentTeam.pokemonTargeted + 1) % currentTeam.pokemons.size();
                    std::cout << "Appel Target " << currentTeam.pokemonTargeted << " switch" << std::endl;
                }

                tabPressed = true; // On marque que la touche a été pressée pour ne pas répéter l'action
            }
        }

        // Réinitialisation de la touche Enter et Tab une fois relâchée
        if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                enterPressed = false;
            }

            if (event.key.code == sf::Keyboard::Tab)
            {
                tabPressed = false;
            }
        }
    }
}

/* ================ SOUS-FONCTIONS POUR LA GESTION DES ENTRÉES ================*/
bool BattleState::handleSwitchButtonClick(sf::RenderWindow &window, TeamStruct &currentTeam)
{
    if (currentTeam.switchButton.shape.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
    {
        currentTeam.activePokemon = (currentTeam.activePokemon + 1) % currentTeam.pokemons.size();
        resetMoveButtonsOutline(currentTeam);
        return true; // Un switch a eu lieu
    }
    return false; // Aucun switch effectué
}

bool BattleState::handleMoveButtonClick(sf::RenderWindow &window, TeamStruct &currentTeam)
{
    for (size_t i = 0; i < 4; i++)
    {
        if (currentTeam.moveButtons[i].shape.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
        {
            currentTeam.currentMove = currentTeam.pokemons[currentTeam.activePokemon]->getMoves()[i];
            // std::cout << "Move choisi pour l'équipe: " << currentTeam.currentMove << std::endl;

            // Change l'outline pour le bouton du move choisi
            resetMoveButtonsOutline(currentTeam);
            currentTeam.moveButtons[i].shape.setOutlineColor(isBlueTeamTurn ? sf::Color::Blue : sf::Color::Red);
            currentTeam.moveButtons[i].shape.setOutlineThickness(3);

            return true; // Un move a été choisi
        }
    }
    return false; // Aucun move sélectionné
}

void BattleState::resetMoveButtonsOutline(TeamStruct &currentTeam)
{
    for (size_t i = 0; i < 4; i++)
    {
        currentTeam.moveButtons[i].shape.setOutlineThickness(0); // Remet l'épaisseur de l'outline par défaut
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

        int damage1 = calculDamage(*blueTeamStruct.pokemons[blueTeamStruct.activePokemon], *redTeamStruct.pokemons[redTeamStruct.pokemonTargeted], *blueTeamStruct.currentMove);
        int damage2 = calculDamage(*redTeamStruct.pokemons[redTeamStruct.activePokemon], *blueTeamStruct.pokemons[blueTeamStruct.pokemonTargeted], *redTeamStruct.currentMove);

        std::cout << "Dammage1 : " << damage1 << std::endl;
        std::cout << "Dammage2 : " << damage2 << std::endl;

        // Degat que l'on va infligé au Bleu
        int oldHp = blueTeamStruct.pokemons[blueTeamStruct.pokemonTargeted]->getHpRestant();
        int newHp = std::max(0, oldHp - damage2);
        blueTeamStruct.pokemons[blueTeamStruct.pokemonTargeted]->setHpRestant(newHp);

        // Degat que l'on va infligé au Rouge
        int oldHp1 = redTeamStruct.pokemons[redTeamStruct.pokemonTargeted]->getHpRestant();
        int newHp1 = std::max(0, oldHp1 - damage1);
        redTeamStruct.pokemons[redTeamStruct.pokemonTargeted]->setHpRestant(newHp1);

        std::cout << "PV du Pokémon rouge attaqué: " << oldHp << " -> " << newHp << std::endl;
        std::cout << "PV du Pokémon bleu attaqué: " << oldHp1 << " -> " << newHp1 << std::endl;

        updateHealthBars(blueTeamStruct);
        updateHealthBars(redTeamStruct);

        isTurnReady = !isTurnReady;
        blueTeamStruct.activePokemon = 0;
        blueTeamStruct.currentMove = nullptr;
        blueTeamStruct.isMoveChosen = false;
        blueTeamStruct.isTargetChosen = false;
        blueTeamStruct.pokemonTargeted = false;

        redTeamStruct.activePokemon = 0;
        redTeamStruct.activePokemon = 0;
        redTeamStruct.currentMove = nullptr;
        redTeamStruct.isMoveChosen = false;
        redTeamStruct.isTargetChosen = false;
        redTeamStruct.pokemonTargeted = false;

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

bool BattleState::checkFainted(TeamStruct &teamStruct)
{
    if (teamStruct.pokemons[0]->getHpRestant() == 0 && teamStruct.pokemons[1]->getHpRestant() == 0)
    {
        std::cout << "Jeu fini" << std::endl;

        return 1;
    }
    else
        return 0;
}

void BattleState::updateHealthBars(TeamStruct &teamStruct)
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
void BattleState::drawPokemonTeam(sf::RenderWindow &window, TeamStruct &teamStruct)
{
    for (auto &sprite : teamStruct.pokemonSprites)
    {
        window.draw(sprite);
    }
}

void BattleState::drawMoveButtons(sf::RenderWindow &window, TeamStruct &teamStruct)
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

void BattleState::drawHealthBars(sf::RenderWindow &window, TeamStruct &teamStruct)
{
    window.draw(teamStruct.bgHealthBar);
    // Dessiner les barres de vie pour chaque Pokémon
    for (size_t i = 0; i < 2; i++)
    {
        // Dessiner les barres de vie
        window.draw(teamStruct.healthBars[i]);
        window.draw(teamStruct.barsText[i]);
    }
}

void BattleState::drawTargetIndicator(sf::RenderWindow &window, TeamStruct &teamStruct)
{
    // Vérifie si un Pokémon est ciblé et si un mouvement a été choisi

    if (!teamStruct.isTargetChosen && teamStruct.isMoveChosen)
    {
        // Obtenez la position du Pokémon ciblé
        TeamStruct &currentTeam = (isBlueTeamTurn) ? redTeamStruct : blueTeamStruct;

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
