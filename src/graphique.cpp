#include "Graphique.hpp"
#include "Pokemon.hpp"


Window::Window() : pokemon1(Pokemondb.getPokemonByName("Palkia")),
                   pokemon2(Pokemondb.getPokemonByName("Dialga")),
                   pokemon3(Pokemondb.getPokemonByName("Arceus")),
                   pokemon4(Pokemondb.getPokemonByName("Giratina")), debut(false), isAnimating(false), isFirstPokemonAttaking(false), isSecondPokemonAttaking(false), isThirdPokemonAttaking(false), isFourthPokemonAttaking(false)
{
    // Initialisation de la fenêtre

    std::cout << "Pokemon1 : [" << pokemon1->getType() << "]" << std::endl;
    animationProgress = 0.0f;
    isTargetingMode = false;
    isDamageAnimating = false;
    damageAnimationDuration = 0.01f;

    // Initialisation des éléments de l'interface graphique
    this->init_pokemon_positon();

    this->initializeHealthBars();

    this->setupUI();

    this->setupSwitchButtons();
    std::cout << "Appel de initializeMoves pour " << pokemon1->getName() << std::endl;
    // Initialize attack effect
    attackAnimationTimer = 0.0f;
    attackFrame = 0;
}

Window::~Window()
{
    delete pokemon1;
    delete pokemon2;
    delete pokemon3;
    delete pokemon4;
    delete this->window; // Libération de la mémoire de la fenêtre
}

void Window::playMusic(const std::string &filename)
{
    if (music.getStatus() == sf::Music::Playing)
    {
        music.stop(); // Arrêter la musique actuelle avant de changer
    }

    if (!music.openFromFile(filename))
    {
        std::cerr << "Erreur : Impossible de charger la musique " << filename << std::endl;
        return;
    }

    music.setLoop(true);
    music.setVolume(50);
    music.play();
}
void Window::init_music()
{
    playMusic("assets/audio/Music.ogg");
}

void Window::init()
{
    updatemovebutton(pokemon1);
    updatemovebutton(pokemon3);
    updatemovebutton(pokemon2);
    updatemovebutton(pokemon4);
}
void Window::init_pokemon_positon()
{
    if (!font.loadFromFile("assets/font/prstartk.ttf"))
    {
        std::cout << "Font loaded successfully " << std::endl;
    }

    // Création des objets Pokémon avec le constructeur
    // Appliquer la texture aux sprites
    pokemonSprite[0].setTexture(pokemon1->getTextureback()); // Pokémon 1 (Gauche)
    pokemonSprite[1].setTexture(pokemon2->getTexturefront());
    pokemonSprite[2].setTexture(pokemon3->getTextureback());
    pokemonSprite[3].setTexture(pokemon4->getTexturefront()); // Pokémon 2 (Droite)

    pokemonSprite[0].setPosition(20, 290);  // Position du Pokémon 1 (Gauche)
    pokemonSprite[1].setPosition(600, 150); // Position du Pokémon 2 (Droite)
    pokemonSprite[2].setPosition(300, 290);
    pokemonSprite[3].setPosition(750, 150);
}

void Window::setupUI()
{
   

    healthbg[0].setSize(sf::Vector2f(300, 90));
    healthbg[0].setPosition(10, 10);
    healthbg[0].setFillColor(sf::Color(100, 100, 100));
    healthbg[0].setOutlineThickness(5);
    healthbg[0].setOutlineColor(sf::Color::Black);

    healthbg[1].setSize(sf::Vector2f(300, 90));
    healthbg[1].setPosition(610, 450);
    healthbg[1].setFillColor(sf::Color(100, 100, 100));
    healthbg[1].setOutlineThickness(5);
    healthbg[1].setOutlineColor(sf::Color::Black);

    // Pokemon1

    // Initialiser les boutons de mouvement
    for (int i = 0; i < 8; i++)
    {
        moveButtons[i].setSize(sf::Vector2f(190, 50));
        moveButtons[i].setFillColor(sf::Color(200, 200, 200));
    }
    // J1
    moveButtons[0].setPosition(50, 600);
    moveButtons[1].setPosition(250, 600);
    moveButtons[2].setPosition(50, 660);
    moveButtons[3].setPosition(250, 660);
    // J2
    moveButtons[4].setPosition(600, 600);
    moveButtons[5].setPosition(800, 600);
    moveButtons[6].setPosition(600, 660);
    moveButtons[7].setPosition(800, 660);
    for (int i = 0; i < 8; i++)
    {
        moveButtonTexts[i].setFont(font);
        moveButtonTexts[i].setCharacterSize(12);
        moveButtonTexts[i].setFillColor(sf::Color::Black);
        moveButtonTexts[i].setPosition(moveButtons[i].getPosition().x + 10,
                                       moveButtons[i].getPosition().y + 10);
    }

    // Target
    targetIndicator.setRadius(25);
    targetIndicator.setFillColor(sf::Color(255, 0, 0, 80)); // Semi-transparent red
    targetIndicator.setOutlineColor(sf::Color::Red);
    targetIndicator.setOutlineThickness(5);
    targetIndicator.setOrigin(25, 25); //
    // Default targets
    currentTargetTeam1 = 0;
    currentTargetTeam2 = 0;
}

void Window::initializeHealthBars()
{
    // Setup health bar backgrounds
    healthBarBackground[0].setSize(sf::Vector2f(200, 10));
    healthBarBackground[0].setPosition(50, 20);
    healthBarBackground[0].setFillColor(sf::Color(100, 100, 100));

    healthBarBackground[1].setSize(sf::Vector2f(200, 20));
    healthBarBackground[1].setPosition(700, 450);
    healthBarBackground[1].setFillColor(sf::Color(100, 100, 100));

    healthBarBackground[2].setSize(sf::Vector2f(200, 20));
    healthBarBackground[2].setPosition(50, 50);
    healthBarBackground[2].setFillColor(sf::Color(100, 100, 100));

    healthBarBackground[3].setSize(sf::Vector2f(200, 20));
    healthBarBackground[3].setPosition(700, 480);
    healthBarBackground[3].setFillColor(sf::Color(100, 100, 100));

    // Setup health bars
    healthBar[0].setSize(sf::Vector2f(200, 10));
    healthBar[0].setPosition(100, 30);
    healthBar[0].setFillColor(sf::Color::Green);
    healthBar[0].setOutlineThickness(2);

    healthBar[1].setSize(sf::Vector2f(200, 10));
    healthBar[1].setPosition(700, 470);
    healthBar[1].setFillColor(sf::Color::Green);
    healthBar[1].setOutlineThickness(2);

    healthBar[2].setSize(sf::Vector2f(200, 5));
    healthBar[2].setPosition(100, 60);
    healthBar[2].setFillColor(sf::Color::Green);
    healthBar[2].setOutlineThickness(2);

    healthBar[3].setSize(sf::Vector2f(200, 5));
    healthBar[3].setPosition(700, 500);
    healthBar[3].setFillColor(sf::Color::Green);
    healthBar[3].setOutlineThickness(2);

    // Store original positions for animations
    originalPos[0] = pokemonSprite[0].getPosition();
    originalPos[1] = pokemonSprite[1].getPosition();
    originalPos[2] = pokemonSprite[2].getPosition();
    originalPos[3] = pokemonSprite[3].getPosition();
}

void Window::updateHealthBars(float health1Percentage, float health2Percentage, float health3Percentage, float health4Percentage)
{
    healthBar[0].setSize(sf::Vector2f(200 * health1Percentage, 20));
    healthBar[1].setSize(sf::Vector2f(200 * health2Percentage, 20));
    healthBar[2].setSize(sf::Vector2f(200 * health3Percentage, 20));
    healthBar[3].setSize(sf::Vector2f(200 * health4Percentage, 20));

    // Change color based on health
    if (health1Percentage > 0.5f)
        healthBar[0].setFillColor(sf::Color::Green);
    else if (health1Percentage > 0.2f)
        healthBar[0].setFillColor(sf::Color::Yellow);
    else
        healthBar[0].setFillColor(sf::Color::Red);

    if (health2Percentage > 0.5f)
        healthBar[1].setFillColor(sf::Color::Green);
    else if (health2Percentage > 0.2f)
        healthBar[1].setFillColor(sf::Color::Yellow);
    else
        healthBar[1].setFillColor(sf::Color::Red);

    if (health3Percentage > 0.5f)
        healthBar[2].setFillColor(sf::Color::Green);
    else if (health2Percentage > 0.2f)
        healthBar[2].setFillColor(sf::Color::Yellow);
    else
        healthBar[2].setFillColor(sf::Color::Red);

    if (health4Percentage > 0.5f)
        healthBar[3].setFillColor(sf::Color::Green);
    else if (health4Percentage > 0.2f)
        healthBar[3].setFillColor(sf::Color::Yellow);
    else
        healthBar[3].setFillColor(sf::Color::Red);
}

void Window::animateAttack(bool isFirstPokemonAttacking)
{
    if (!isAnimating)
    {
        isAnimating = true;
        animationProgress = 0;
        animationClock.restart();
    }
}

void Window::updateAnimations()
{

    if (!isAnimating)
        return;

    float elapsed = attackAnimClock.getElapsedTime().asSeconds();
    float frameDuration = 0.04f;

    if (elapsed > frameDuration)
    {
        attackAnimClock.restart();
        currentFrame++;

        int columns = 2;
        int rows = 7;
        int frameWidth = attackEffectTexture[0].getSize().x / columns;
        int frameHeight = attackEffectTexture[0].getSize().y / rows;
        int numFrames = columns * rows - 1;

        if (currentFrame >= numFrames)
        {
            currentFrame = 0;
            isAnimating = false;

            // Reset Pokemon colors when attack animation ends
            pokemonSprite[0].setColor(sf::Color::White);
            pokemonSprite[1].setColor(sf::Color::White);
            pokemonSprite[2].setColor(sf::Color::White);
            pokemonSprite[3].setColor(sf::Color::White);
        }

        int x = (currentFrame % columns) * frameWidth;
        int y = (currentFrame / columns) * frameHeight;
        attackEffectSprite[0].setTextureRect(sf::IntRect(x, y, frameWidth + 10, frameHeight));
        std::cout << "  Frame mise à jour : " << currentFrame << "/" << numFrames
                  << " | Position : (" << x << ", " << y << ")" << std::endl;
    }

    // ===  Attack movement animation === animateAttack(isSecondPokemonAttaking);

    float attackSpeed = 50.0f;
    float attackTime = 0.5f;

    float attackProgress = animationClock.getElapsedTime().asSeconds() / attackTime;
    sf::Vector2f attackPosition;

    if (attackProgress < 1.0f)
    {
        float xOffset = sin(attackProgress * 3.14159f) * attackSpeed;
        float yOffset = sin(attackProgress * 3.14159f) * attackSpeed;

        // Set the target Pokemon red during the attack
        if (isFirstPokemonAttaking || isThirdPokemonAttaking)
        {
            sf::Sprite &attackerSprite = isFirstPokemonAttaking ? pokemonSprite[0] : pokemonSprite[2];
            sf::Sprite &targetSprite = (currentTargetTeam1 == 0) ? pokemonSprite[1] : pokemonSprite[3];

            // Attacker movement
            attackerSprite.setPosition(
                (isFirstPokemonAttaking ? originalPos[0] : originalPos[2]).x + xOffset,
                (isFirstPokemonAttaking ? originalPos[0] : originalPos[2]).y - yOffset);

            // Target effects
            targetSprite.setColor(sf::Color(255, 0, 0, 255)); // Target turns red
            targetSprite.setPosition(
                (currentTargetTeam1 == 0 ? originalPos[1] : originalPos[3]).x - 8,
                (currentTargetTeam1 == 0 ? originalPos[1] : originalPos[3]).y + 8);

            // Position attack effect sprite
            attackPosition.x = targetSprite.getPosition().x - 70;
            attackPosition.y = targetSprite.getPosition().y - 10;
        }
        // When Team 2 is attacking
        else if (isSecondPokemonAttaking || isFourthPokemonAttaking)
        {
            sf::Sprite &attackerSprite = isSecondPokemonAttaking ? pokemonSprite[1] : pokemonSprite[3];
            sf::Sprite &targetSprite = (currentTargetTeam2 == 0) ? pokemonSprite[0] : pokemonSprite[2];

            // Attacker movement
            attackerSprite.setPosition(
                (isSecondPokemonAttaking ? originalPos[1] : originalPos[3]).x - xOffset,
                (isSecondPokemonAttaking ? originalPos[1] : originalPos[3]).y + yOffset);

            // Target effects
            targetSprite.setColor(sf::Color(255, 0, 0, 255)); // Target turns red
            targetSprite.setPosition(
                (currentTargetTeam2 == 0 ? originalPos[0] : originalPos[2]).x - 8,
                (currentTargetTeam2 == 0 ? originalPos[0] : originalPos[2]).y + 8);

            // Position attack effect sprite
            attackPosition.x = targetSprite.getPosition().x + 40;
            attackPosition.y = targetSprite.getPosition().y + 100;
        }

        attackEffectSprite[0].setPosition(attackPosition);
        attackEffectSprite[1].setPosition(attackPosition);
        attackEffectSprite[2].setPosition(attackPosition);
        attackEffectSprite[3].setPosition(attackPosition);
    }
    else
    {
        // Reset all colors and positions when animation ends
        pokemonSprite[0].setColor(sf::Color::White);
        pokemonSprite[1].setColor(sf::Color::White);
        pokemonSprite[2].setColor(sf::Color::White);
        pokemonSprite[3].setColor(sf::Color::White);

        // Return to original positions
        pokemonSprite[0].setPosition(originalPos[0]);
        pokemonSprite[1].setPosition(originalPos[1]);
        pokemonSprite[2].setPosition(originalPos[2]);
        pokemonSprite[3].setPosition(originalPos[3]);

        // Reset animation states

        isAnimating = false;
        isFirstPokemonAttaking = false;
        isSecondPokemonAttaking = false;
        isThirdPokemonAttaking = false;
        isFourthPokemonAttaking = false;

        currentFrame = 0;
    }
}

void Window::updatemovebutton(Pokemon *pokemon)
{
    if (pokemon)
    {
        active = pokemon;
        const std::vector<move *> &moves = pokemon->getMoves();
        for (size_t i = 0; i < moves.size() && i < 4; i++)
        {
            moveButtonTexts[i].setString(moves[i]->nom);
        }
    }
}

// Update the render function
void Window::render()
{
    this->window->clear();

    // Update animations

    updateAnimations();
    updateSwapAnimation();

    // Draw arena
    if (!Arene_texture.loadFromFile("assets/images/Background.jpg"))
    {
        std::cerr << "Erreur: Impossible de charger le fond." << std::endl;
    }
    Arene_sprite.setTexture(Arene_texture);
    this->window->draw(Arene_sprite);
    window->draw(healthbg[0]);
    window->draw(healthbg[1]);

    // Draw health bars
    this->window->draw(healthBarBackground[0]);
    this->window->draw(healthBarBackground[1]);
    this->window->draw(healthBar[0]);
    this->window->draw(healthBar[1]);
    this->window->draw(healthBar[2]);
    this->window->draw(healthBar[3]);
    this->window->draw(healthText[0]);
    this->window->draw(healthText[1]);
    this->window->draw(healthText[2]);
    this->window->draw(healthText[3]);

    // Draw Pokemon sprites
    this->window->draw(pokemonSprite[0]);
    this->window->draw(pokemonSprite[1]);
    this->window->draw(pokemonSprite[2]);
    this->window->draw(pokemonSprite[3]);

    // Draw move buttons
    for (int i = 0; i < 8; i++)
    {
        window->draw(moveButtons[i]);
        window->draw(moveButtonTexts[i]);
    }
    window->draw(switchButtons);
    window->draw(switchButtonTexts);
    window->draw(switchButtons2);
    window->draw(switchButtonTexts2);

    if (isAnimating && !animationFinished)
    {
        window->draw(attackEffectSprite[0]);
        // window->draw(attackEffectSprite[1]);
    }
    renderTargetIndicator();

    this->window->display();
}

void Window::handleinput()
{
    sf::Vector2f mousePos = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

    if (!isTargetingMode && !isAnimating)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            for (size_t i = 0; i < 4; i++)
            {
                if (moveButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    moveButtons[i].setOutlineThickness(5);
                    moveButtons[i].setOutlineColor(sf::Color::Red);
                }
            }
        }
        else
        {
            for (size_t i = 0; i < 4; i++)
            {
                moveButtons[i].setOutlineThickness(0);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
            std::vector<move *> moves = activeTeam2Index == 0 ? pokemon2->getMoves() : pokemon4->getMoves();
            // Vérifie les boutons des attaques du premier Pokémon

            moveButtons[4].setOutlineThickness(5);
            moveButtons[4].setOutlineColor(sf::Color::Red);
        }
        else
        {
            moveButtons[4].setOutlineThickness(0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {

            std::vector<move *> moves = activeTeam2Index == 0 ? pokemon2->getMoves() : pokemon4->getMoves();

            moveButtons[5].setOutlineThickness(5);
            moveButtons[5].setOutlineColor(sf::Color::Red);
        }
        else
        {
            moveButtons[5].setOutlineThickness(0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            std::vector<move *> moves = activeTeam2Index == 0 ? pokemon2->getMoves() : pokemon4->getMoves();

            moveButtons[6].setOutlineThickness(5);
            moveButtons[6].setOutlineColor(sf::Color::Red);
        }
        else
        {
            moveButtons[6].setOutlineThickness(0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            std::vector<move *> moves = activeTeam2Index == 0 ? pokemon2->getMoves() : pokemon4->getMoves();
            //
            moveButtons[7].setOutlineThickness(5);
            moveButtons[7].setOutlineColor(sf::Color::Red);
        }
        else
        {
            moveButtons[7].setOutlineThickness(0);
        }
    }
}

void Window::processevent()
{

    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
        handleSwitching();
    }
}

void Window::setupSwitchButtons()
{
    // Designe button switch à changer

    switchButtons.setSize(sf::Vector2f(150, 40));
    switchButtonTexts.setFont(font);
    switchButtonTexts.setCharacterSize(9);
    switchButtonTexts.setFillColor(sf::Color::Black);

    switchButtons2.setSize(sf::Vector2f(150, 40));
    switchButtonTexts2.setFont(font);
    switchButtonTexts2.setCharacterSize(9);
    switchButtonTexts2.setFillColor(sf::Color::Black);

    switchButtons.setPosition(50, 550); // Team 1 switch button
    switchButtons2.setPosition(600, 550);

    switchButtons.setFillColor(sf::Color(200, 200, 200));
    switchButtons2.setFillColor(sf::Color(200, 200, 200));

    switchButtonTexts.setString("Switch Pokemon");
    switchButtonTexts2.setString("Switch Pokemon");

    switchButtonTexts.setPosition(60, 560);
    switchButtonTexts2.setPosition(610, 560);

    // Indices des equipe actives
    activeTeam1Index = 0;
    activeTeam2Index = 0;
    isSwapping = false;
    swapProgress = 0.0f;

    // revenir au position initial à changer
    originalPosTeam1[0] = pokemonSprite[0].getPosition();
    originalPosTeam1[1] = pokemonSprite[2].getPosition();
    originalPosTeam2[0] = pokemonSprite[1].getPosition();
    originalPosTeam2[1] = pokemonSprite[3].getPosition();
}

void Window::handleSwitching()
{
    // Position curseur
    sf::Vector2f mousePos = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

    // Gestion des clicks
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        // Check if mouse is over team 1's switch button
        if (switchButtons.getGlobalBounds().contains(mousePos.x, mousePos.y) && !isSwapping)
        {
            switchButtons.setScale(1.1f, 1.1f);
            switchButtonTexts.setScale(1.1f, 1.1f);
            animateSwitch(true);                     // Start swap animation for team 1
            activeTeam1Index = 1 - activeTeam1Index; // Toggle between 0 and 1
            updateMoveButtons();
        }
    }
    else
    {
        switchButtons.setScale(1.f, 1.f);
        switchButtonTexts.setScale(1.f, 1.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && !isSwapping)
    {
        switchButtons2.setScale(1.1f, 1.1f);
        switchButtonTexts2.setScale(1.1f, 1.1f);
        activeTeam2Index = 1 - activeTeam2Index;
        animateSwitch(false); // Start swap animation for team 2
        updateMoveButtons();

        // Toggle between 0 and
    }

    else
    {
        switchButtons2.setScale(1.f, 1.f);
        switchButtonTexts2.setScale(1.f, 1.f);
    }
}

void Window::animateSwitch(bool isTeam1)
{
    if (!isSwapping)
    {
        isSwapping = true;
        swapProgress = 0.0f;
        animationClock.restart();
    }
}

void Window::updateSwapAnimation()
{
    if (isSwapping)
    {
        float elapsed = animationClock.getElapsedTime().asSeconds();
        swapProgress = elapsed * 2; // 0.5 second animation

        if (swapProgress >= 1.0f)
        {
            // Animation complete, reset positions
            pokemonSprite[0].setPosition(originalPosTeam1[0]);
            pokemonSprite[2].setPosition(originalPosTeam1[1]);
            pokemonSprite[1].setPosition(originalPosTeam2[0]);
            pokemonSprite[3].setPosition(originalPosTeam2[1]);
            isSwapping = false;
            // Animate the swap
            float yOffset = sin(swapProgress * 3.14159f) * 10.0f;

            // Team 1 Pokemon
            pokemonSprite[0].setPosition(originalPosTeam1[0].x,
                                        originalPosTeam1[0].y + yOffset);
            pokemonSprite[2].setPosition(originalPosTeam1[1].x,
                                        originalPosTeam1[1].y + yOffset);

            // Team 2 Pokemon
            pokemonSprite[1].setPosition(originalPosTeam2[0].x,
                                        originalPosTeam2[0].y - yOffset);
            pokemonSprite[3].setPosition(originalPosTeam2[1].x,
                                        originalPosTeam2[1].y + yOffset);
        }
    }
}

void Window::setAttackEffectSprite(const std::string &movePath)
{
    if (!attackEffectTexture[0].loadFromFile(movePath))
    {
        std::cerr << "Erreur : Impossible de charger l'effet d'attaque " << movePath << std::endl;
        return;
    }
    attackEffectSprite[0].setTexture(attackEffectTexture[0]);
}

// On definie le cercle pour les targets
void Window::setupTargetingSystem()
{
    // Setup target indicator
    targetIndicator.setRadius(15);
    targetIndicator.setFillColor(sf::Color::Transparent);
    targetIndicator.setOutlineColor(sf::Color::Red);
    targetIndicator.setOutlineThickness(3);
    targetIndicator.setOrigin(15, 15); // Center the circle

    // Default targets
    currentTargetTeam1 = 1; // Default to pokemon2
    currentTargetTeam2 = 1; // Default to pokemon1
}
// Method to cycle through targets
void Window::cycleTargets(bool isTeam1)
{
    if (isTeam1)
    {
        currentTargetTeam1 = 1 - currentTargetTeam1; // ici c'est gauche qui attack
    }
    else
    {
        currentTargetTeam2 = 1 - currentTargetTeam2; // ici c'est droit qui attack
    }
}

// Get the currently targeted Pokemon
Pokemon *Window::getCurrentTarget(bool isTeam1)
{
    if (isTeam1)
    {
        return (currentTargetTeam1 == 0) ? pokemon2 : pokemon4; // si c'est tema1 et qu'il target
    }
    else
    {
        return (currentTargetTeam2 == 0) ? pokemon1 : pokemon3;
    }
}

void Window::renderTargetIndicator()
{
    if (!isTargetingMode)
        return;

    // Position the indicator on the current target
    sf::Vector2f targetPos;

    // If team 1 is targeting
    if (isFirstPokemonAttaking || isThirdPokemonAttaking)
    {
        if (currentTargetTeam1 == 0)
        {
            // Targeting pokemon2
            targetPos = pokemonSprite[1].getPosition();
            targetPos.x += pokemonSprite[1].getGlobalBounds().width / 2;
            targetPos.y += pokemonSprite[1].getGlobalBounds().height / 2;
        }
        else
        {
            // Targeting pokemon4
            targetPos = pokemonSprite[3].getPosition();
            targetPos.x += pokemonSprite[3].getGlobalBounds().width / 2;
            targetPos.y += pokemonSprite[3].getGlobalBounds().height / 2;
        }
    }
    // If team 2 is targeting
    else if (isSecondPokemonAttaking || isFourthPokemonAttaking)
    {
        if (currentTargetTeam2 == 0)
        {
            // Targeting pokemon1
            targetPos = pokemonSprite[0].getPosition();
            targetPos.x += pokemonSprite[0].getGlobalBounds().width / 2;
            targetPos.y += pokemonSprite[0].getGlobalBounds().height / 2;
        }
        else
        {
            // Targeting pokemon3
            targetPos = pokemonSprite[2].getPosition();
            targetPos.x += pokemonSprite[2].getGlobalBounds().width / 2;
            targetPos.y += pokemonSprite[2].getGlobalBounds().height / 2;
        }
    }

    targetIndicator.setPosition(targetPos);
    window->draw(targetIndicator);

    // Add a text indicator to show targeting mode is active
    sf::Text targetingText;
    targetingText.setFont(font);
    targetingText.setString("TARGETING MODE - Press Tab to cycle targets");
    targetingText.setCharacterSize(16);
    targetingText.setFillColor(sf::Color::Red);
    targetingText.setPosition(320, 30);
    window->draw(targetingText);
}
void Window::updateMoveButtons()
{
    // Get the currently active Pokemon for each team
    Pokemon *activePokemon1 = (activeTeam1Index == 0) ? pokemon1 : pokemon3;
    Pokemon *activePokemon2 = (activeTeam2Index == 0) ? pokemon2 : pokemon4;

    // Get their moves
    std::vector<move *> moves1 = activePokemon1->getMoves();
    std::vector<move *> moves2 = activePokemon2->getMoves();

    // Debug output to check what's happening
    std::cout << "Updating move buttons. Team 1 active: "
              << activePokemon1->getName()
              << " with " << moves1.size() << " moves" << std::endl;
    std::cout << "Updating move buttons. Team 2 active: "
              << activePokemon2->getName()
              << " with " << moves2.size() << " moves" << std::endl;

    // Make sure we have moves to display
    if (moves1.size() >= 4 && moves2.size() >= 4)
    {
        // Update Team 1 move buttons (0-3)
        for (int i = 0; i < 4; i++)
        {
            moveButtonTexts[i].setString(moves1[i]->getmovename());
            std::cout << "Team 1 move " << i << ": " << moves1[i]->getmovename() << std::endl;
        }

        // Update Team 2 move buttons (4-7)
        for (int i = 0; i < 4; i++)
        {
            moveButtonTexts[i + 4].setString(moves2[i]->getmovename());
            std::cout << "Team 2 move " << i << ": " << moves2[i]->getmovename() << std::endl;
        }
    }
    else
    {
        std::cerr << "Error: Not enough moves for one or both Pokemon" << std::endl;
    }
}
void Window::showPokemonSelection()
{

    sf::RenderWindow selectionWindow(sf::VideoMode(1024, 700), "Sélection des Pokémon");
    playMusic("assets/audio/selection.ogg");
    // Charger l'image de fond
    sf::Texture background;
    if (!background.loadFromFile("assets/images/selection_background.jpg"))
    {
        std::cerr << "Error: Unable to load background image" << std::endl;
    }
    sf::Sprite background_sprite(background);

    // Charger la police
    if (!font.loadFromFile("assets/font/prstartk.ttf"))
    {
        std::cerr << "Erreur de chargement de la police !" << std::endl;
    }

    // Charger les textures des Pokémon
    std::vector<sf::Texture> pokemonTextures(allPokemon.size());
    std::vector<sf::Sprite> pokemonSprites(allPokemon.size());

    for (size_t i = 0; i < allPokemon.size(); i++)
    {
        if (!pokemonTextures[i].loadFromFile("assets/images/" + allPokemon[i]->getName() + ".png"))
        {
            std::cerr << "Erreur de chargement de l'image pour " << allPokemon[i]->getName() << std::endl;
        }
        pokemonSprites[i].setTexture(pokemonTextures[i]);
        pokemonSprites[i].setScale(0.7f, 0.7f); // Ajuster la taille
    }

    size_t selectedIndexJ1 = 0, selectedIndexJ2 = 0;
    bool j1Confirmed = false, j2Confirmed = false;
    std::vector<int> teamJ1, teamJ2;

    while (selectionWindow.isOpen())
    {
        sf::Event event;
        while (selectionWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                selectionWindow.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    selectionWindow.close();
                }
                // Sélection du Joueur 1
                if (!j1Confirmed)
                {
                    if (event.key.code == sf::Keyboard::Left)
                        selectedIndexJ1 = (selectedIndexJ1 - 1 + allPokemon.size()) % allPokemon.size();
                    if (event.key.code == sf::Keyboard::Right)
                        selectedIndexJ1 = (selectedIndexJ1 + 1) % allPokemon.size();
                    if (event.key.code == sf::Keyboard::Enter)
                    {
                        if (teamJ1.size() < 2 && std::find(teamJ1.begin(), teamJ1.end(), selectedIndexJ1) == teamJ1.end())
                        {
                            teamJ1.push_back(selectedIndexJ1);
                        }
                        if (teamJ1.size() == 2)
                            j1Confirmed = true;
                    }
                }

                // Sélection du Joueur 2
                else if (!j2Confirmed)
                {
                    if (event.key.code == sf::Keyboard::Q)
                        selectedIndexJ2 = (selectedIndexJ2 - 1 + allPokemon.size()) % allPokemon.size();
                    if (event.key.code == sf::Keyboard::D)
                        selectedIndexJ2 = (selectedIndexJ2 + 1) % allPokemon.size();
                    if (event.key.code == sf::Keyboard::Space)
                    {
                        if (teamJ2.size() < 2 && std::find(teamJ2.begin(), teamJ2.end(), selectedIndexJ2) == teamJ2.end())
                        {
                            teamJ2.push_back(selectedIndexJ2);
                        }
                        if (teamJ2.size() == 2)
                            j2Confirmed = true;
                    }
                }

                // Démarrer le combat
                if (j1Confirmed && j2Confirmed)
                {
                    this->pokemon1 = allPokemon[teamJ1[0]];
                    this->pokemon3 = allPokemon[teamJ1[1]];
                    this->pokemon2 = allPokemon[teamJ2[0]];
                    this->pokemon4 = allPokemon[teamJ2[1]];

                    updatePokemonSprites();

                    init_pokemon_positon();
                    pokemon1->initializeMoves();
                    pokemon2->initializeMoves();
                    pokemon3->initializeMoves();
                    pokemon4->initializeMoves();
                    selectionWindow.close();
                    init_music();
                    this->window = new sf::RenderWindow(sf::VideoMode(1024, 700), "Combat Pokémon");
                    this->debut = true;
                }
            }
        }

        selectionWindow.clear();
        selectionWindow.draw(background_sprite);

        // Affichage des Pokémon
        for (size_t i = 0; i < allPokemon.size(); i++)
        {
            int row = i / 5;
            int col = i % 5;
            pokemonSprites[i].setPosition(50 + col * 180, 50 + row * 150);
            selectionWindow.draw(pokemonSprites[i]);

            // Encadrer les Pokémon sélectionnés
            if (std::find(teamJ1.begin(), teamJ1.end(), i) != teamJ1.end() ||
                std::find(teamJ2.begin(), teamJ2.end(), i) != teamJ2.end() ||
                (!j1Confirmed && i == selectedIndexJ1) ||
                (!j2Confirmed && i == selectedIndexJ2))
            {
                sf::RectangleShape highlight(sf::Vector2f(120, 120));
                highlight.setPosition(50 + col * 180, 50 + row * 150);
                highlight.setOutlineThickness(5);
                highlight.setOutlineColor(
                    std::find(teamJ1.begin(), teamJ1.end(), i) != teamJ1.end() ? sf::Color::Blue : sf::Color::Red);
                highlight.setFillColor(sf::Color::Transparent);
                selectionWindow.draw(highlight);
            }
        }

        healthText[0].setString(pokemon1->getName());
        healthText[0].setFont(font);
        healthText[0].setCharacterSize(10);
        healthText[0].setFillColor(sf::Color::White);
        healthText[0].setPosition(15, 29);
        // Pokemon2
        healthText[1].setString(pokemon3->getName());
        healthText[1].setFont(font);
        healthText[1].setCharacterSize(10);
        healthText[1].setFillColor(sf::Color::White);
        healthText[1].setPosition(15, 60);
        // Pokemon3
        healthText[2].setString(pokemon2->getName());
        healthText[2].setFont(font);
        healthText[2].setCharacterSize(10);
        healthText[2].setFillColor(sf::Color::White);
        healthText[2].setPosition(615, 469);
        // Pokemon4
        healthText[3].setString(pokemon4->getName());
        healthText[3].setFont(font);
        healthText[3].setCharacterSize(10);
        healthText[3].setFillColor(sf::Color::White);
        healthText[3].setPosition(615, 500);

        selectionWindow.display();
    }
}

void Window::showMainMenu()
{
    sf::RenderWindow menuWindow(sf::VideoMode(1024, 640), "Menu Principal");
    playMusic("assets/audio/Title.ogg");
    // Charger la police
    if (!font.loadFromFile("assets/font/prstartk.ttf"))
    {
        std::cerr << "Erreur de chargement de la police !" << std::endl;
    }

    // Fond

    if (!backgroundm.loadFromFile("assets/images/Menu.jpg"))
    {
        std::cerr << "Error: Unable to load background image" << std::endl;
    }
    background_spritem.setTexture(backgroundm);

    // Bouton "Start"
    sf::RectangleShape startButton(sf::Vector2f(200, 50));
    startButton.setPosition(430, 400);
    startButton.setFillColor(sf::Color(100, 200, 100));

    sf::Text startText("START", font, 20);
    startText.setFillColor(sf::Color::White);
    startText.setPosition(490, 410);

    // Bouton "Help"
    sf::RectangleShape helpButton(sf::Vector2f(200, 50));
    helpButton.setPosition(430, 500);
    helpButton.setFillColor(sf::Color(200, 100, 100));

    sf::Text helpText("HELP", font, 20);
    helpText.setFillColor(sf::Color::White);
    helpText.setPosition(490, 510);

    while (menuWindow.isOpen())
    {
        sf::Event event;
        while (menuWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                menuWindow.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mousePos = menuWindow.mapPixelToCoords(sf::Mouse::getPosition(menuWindow));

                // Vérifier si "Start" est cliqué
                if (startButton.getGlobalBounds().contains(mousePos))
                {
                    menuWindow.close();
                    showPokemonSelection(); // Lancer la sélection de Pokémon
                }

                // Vérifier si "Help" est cliqué
                if (helpButton.getGlobalBounds().contains(mousePos))
                {
                    sf::RenderWindow helpWindow(sf::VideoMode(600, 400), "Instructions");
                    sf::Text instructions("Choisissez 2 Pokemon chacun et combattez !\nUtilisez les attaques pour battre votre adversaire.", font, 7);
                    instructions.setFillColor(sf::Color::White);
                    instructions.setPosition(50, 100);

                    while (helpWindow.isOpen())
                    {
                        sf::Event helpEvent;
                        while (helpWindow.pollEvent(helpEvent))
                        {
                            if (helpEvent.type == sf::Event::Closed)
                                helpWindow.close();
                        }

                        helpWindow.clear(sf::Color::Black);
                        helpWindow.draw(instructions);
                        helpWindow.display();
                    }
                }
            }
        }

        menuWindow.clear();
        menuWindow.draw(background_spritem);
        menuWindow.draw(startButton);
        menuWindow.draw(startText);
        menuWindow.draw(helpButton);
        menuWindow.draw(helpText);
        menuWindow.display();
    }
}

void Window::showEndGameMenu(int winningTeam)
{
    sf::RenderWindow endGameWindow(sf::VideoMode(1024, 640), "Fin du jeu");

    // Charger la police
    if (!font.loadFromFile("assets/font/prstartk.ttf"))
    {
        std::cerr << "Erreur de chargement de la police !" << std::endl;
    }

    if (!backgroundfin.loadFromFile("assets/images/end_game.jpg"))
    {
        std::cerr << "Error: Unable to load background image" << std::endl;
    }
    background_spritefin.setTexture(backgroundfin);

    // Texte de victoire
    sf::Text winnerText("Team " + std::to_string(winningTeam) + " Wins ", font, 20);
    winnerText.setFillColor(sf::Color::White);
    winnerText.setPosition(300, 150);

    // Bouton "Rejouer"
    sf::RectangleShape replayButton(sf::Vector2f(200, 50));
    replayButton.setPosition(412, 250);
    replayButton.setFillColor(sf::Color(100, 200, 100));

    sf::Text replayText("Rejouer", font, 20);
    replayText.setFillColor(sf::Color::White);

    sf::FloatRect replayTextBounds = replayText.getLocalBounds();
    replayText.setOrigin(replayTextBounds.left + replayTextBounds.width / 2.0f, replayTextBounds.top + replayTextBounds.height / 2.0f);
    replayText.setPosition(replayButton.getPosition().x + replayButton.getSize().x / 2.0f, replayButton.getPosition().y + replayButton.getSize().y / 2.0f);

    // Bouton "Quitter"
    sf::RectangleShape quitButton(sf::Vector2f(200, 50));
    quitButton.setPosition(412, 350);
    quitButton.setFillColor(sf::Color(200, 100, 100));

    sf::Text quitText("Quitter", font, 20);
    quitText.setFillColor(sf::Color::White);
    sf::FloatRect quitTextBounds = quitText.getLocalBounds();
    quitText.setOrigin(quitTextBounds.left + quitTextBounds.width / 2.0f, quitTextBounds.top + quitTextBounds.height / 2.0f);
    quitText.setPosition(quitButton.getPosition().x + quitButton.getSize().x / 2.0f, quitButton.getPosition().y + quitButton.getSize().y / 2.0f);

    while (endGameWindow.isOpen())
    {
        sf::Event event;
        window->close();
        while (endGameWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                endGameWindow.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mousePos = endGameWindow.mapPixelToCoords(sf::Mouse::getPosition(endGameWindow));

                if (replayButton.getGlobalBounds().contains(mousePos))
                {
                    endGameWindow.close();
                    showMainMenu(); // Retour au menu principal
                }

                if (quitButton.getGlobalBounds().contains(mousePos))
                {
                    endGameWindow.close();
                    exit(0); // Quitte totalement le jeu
                }
            }
        }

        endGameWindow.clear();
        endGameWindow.draw(background_spritefin);
        endGameWindow.draw(winnerText);
        endGameWindow.draw(replayButton);
        endGameWindow.draw(replayText);
        endGameWindow.draw(quitButton);
        endGameWindow.draw(quitText);
        endGameWindow.display();
    }
}

void Window::updatePokemonSprites()
{
    if (pokemon1)
    {
        pokemonSprite[0].setTexture(pokemon1->getTextureback());
    }
    if (pokemon2)
    {
        pokemonSprite[1].setTexture(pokemon2->getTexturefront());
    }
    if (pokemon3)
    {
        pokemonSprite[2].setTexture(pokemon3->getTextureback());
    }
    if (pokemon4)
    {
        pokemonSprite[3].setTexture(pokemon4->getTexturefront());
    }
}