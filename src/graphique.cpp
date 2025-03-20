#include "Graphique.hpp"
#include "Pokemon.hpp"

// =================== DEBUT MAIN MENU =================== //
void Window::loadResources(const std::string &fontFile, const std::string &bgTextureFile)
{
    // Charger la police
    if (!font.loadFromFile(fontFile))
    {
        std::cerr << "Erreur de chargement de la police à partir de : " << fontFile << std::endl;
    }

    // Charger l'image de fond
    if (!BGTexture.loadFromFile(bgTextureFile))
    {
        std::cerr << "Erreur de chargement de l'image de fond à partir de : " << bgTextureFile << std::endl;
    }
    BGSprite.setTexture(BGTexture);
}

sf::Text Window::createText(const std::string &textContent, unsigned int fontSize)
{
    sf::Text text;

    // Configurer le texte
    text.setFont(font);                  // Assigner la police au texte
    text.setString(textContent);         // Assigner le texte à afficher
    text.setCharacterSize(fontSize);     // Définir la taille des caractères
    text.setFillColor(sf::Color::White); // Définir la couleur du texte (ici en blanc)
    text.setStyle(sf::Text::Regular);    // Définir le style du texte (normal ici)

    return text;
}

sf::RectangleShape Window::createButton(sf::Vector2f size, sf::Vector2f position, sf::Color color)
{
    sf::RectangleShape button(size);
    button.setPosition(position);
    button.setFillColor(color);
    return button;
}

void Window::showHelpWindow()
{
      sf::RenderWindow helpWindow(sf::VideoMode(1024, 600), "Help");

    // Charger les ressources
    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("assets/images/help.png"))
    {
        std::cerr << "Erreur : Impossible de charger l'image de fond du menu d'aide." << std::endl;
        return;
    }
    sf::Sprite bgSprite(bgTexture);
    std::string helpText = 
        " Regles du combat Pokemon \n\n"
        "  Deroulement :\n"
        "- Chaque joueur choisit 2 Pokemon.\n"
        "- Les combats se deroulent au tour par tour.\n"
        "- A chaque tour, vous pouvez attaquer ou changer de Pokemon.\n\n"
        "  Attaques & Degets :\n"
        "- Chaque Pokemon a 4 attaques.\n"
        "- Les degats sont influences par le type (feu, eau, plante...).\n"
        "- Un coup critique inflige 1,5x les degats normaux.\n"
        "- Une attaque est 'super efficace' si elle cible une faiblesse.\n"
        "- Une attaque est 'peu efficace' si elle cible une resistance.\n\n"
        "  Strategies :\n"
        "- Changer de Pokemon peut etre utile pour eviter une faiblesse.\n"
        "- Utilisez les attaques de statut pour prendre l'avantage.\n"
        "- Gerez vos PV et attaques pour maximiser vos chances de victoire !";

    sf::Text helpWindowText = createText(helpText, 14);
    helpWindowText.setLineSpacing(1.5f);
    helpWindowText.setFillColor(sf::Color::Black);

    sf::FloatRect textBounds = helpWindowText.getLocalBounds();
    helpWindowText.setPosition(500-(textBounds.width) / 2, 40); // Centrer le texte en haut

    while (helpWindow.isOpen())
    {
        sf::Event event;
        while (helpWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                helpWindow.close(); // Fermer proprement la fenêtre
            }
        }

        // Vérification pour éviter d'utiliser la fenêtre après sa fermeture
        if (!helpWindow.isOpen())
            break;

        helpWindow.clear();
        helpWindow.draw(bgSprite);
        helpWindow.draw(helpWindowText);
        //helpWindow.draw(pokemonSprite1);
        //helpWindow.draw(pokemonSprite2);
        helpWindow.display();
    }
}
// =================== FIN MAIN MENU =================== //

void Window::showMainMenu()
{
    sf::RenderWindow mainMenuWindow(sf::VideoMode(1024, 640), "Menu Principal");

    loadResources("assets/font/prstartk.ttf", "assets/images/Menu.jpg");
    playMusic("assets/audio/Title.ogg", 50.0, true);

    // Taille de la fenêtre
    float mainMenuwindowWidth = mainMenuWindow.getSize().x;
    float mainMenuwindowHeight = mainMenuWindow.getSize().y;

    // Taille des boutons
    sf::Vector2f buttonSize(200, 50);
    float startButtonsPos = mainMenuwindowHeight * 7.0 / 12;
    float endButtonsPos = mainMenuwindowHeight * 11.0 / 12;

    // Calcul des positions pour centrer les boutons
    sf::Vector2f startButtonPos((mainMenuwindowWidth - buttonSize.x) / 2, startButtonsPos);
    sf::Vector2f helpButtonPos((mainMenuwindowWidth - buttonSize.x) / 2, startButtonsPos + (endButtonsPos - startButtonsPos) * 1 / 3);
    sf::Vector2f exitButtonPos((mainMenuwindowWidth - buttonSize.x) / 2, startButtonsPos + (endButtonsPos - startButtonsPos) * 2 / 3);

    sf::RectangleShape startButton = createButton(buttonSize, startButtonPos, sf::Color::Green);
    sf::Text startText = createText("Start", 20);
    // Centrer le texte dans le bouton
    sf::FloatRect startTextBounds = startText.getLocalBounds();
    startText.setPosition(startButtonPos.x + (buttonSize.x - startTextBounds.width) / 2, startButtonPos.y + (buttonSize.y - startTextBounds.height) / 2);

    sf::RectangleShape helpButton = createButton(buttonSize, helpButtonPos, sf::Color::Blue);
    sf::Text helpText = createText("Help", 20);
    // Centrer le texte dans le bouton
    sf::FloatRect helpTextBounds = helpText.getLocalBounds();
    helpText.setPosition(helpButtonPos.x + (buttonSize.x - helpTextBounds.width) / 2, helpButtonPos.y + (buttonSize.y - helpTextBounds.height) / 2);

    sf::RectangleShape exitButton = createButton(buttonSize, exitButtonPos, sf::Color::Red);
    sf::Text exitText = createText("Exit", 20);
    // Centrer le texte dans le bouton
    sf::FloatRect exitTextBounds = exitText.getLocalBounds();
    exitText.setPosition(exitButtonPos.x + (buttonSize.x - exitTextBounds.width) / 2, exitButtonPos.y + (buttonSize.y - exitTextBounds.height) / 2);

    while (mainMenuWindow.isOpen())
    {
        sf::Event event;
        while (mainMenuWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                mainMenuWindow.close();
                exit(0);
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mousePos = mainMenuWindow.mapPixelToCoords(sf::Mouse::getPosition(mainMenuWindow));
                if (startButton.getGlobalBounds().contains(mousePos))
                {
                    mainMenuWindow.close();
                    showPokemonSelection();
                }
                else if (helpButton.getGlobalBounds().contains(mousePos))
                {
                    showHelpWindow();
                }
                else if (exitButton.getGlobalBounds().contains(mousePos))
                {
                    mainMenuWindow.close();
                    exit(0);
                }

            }
        }

        mainMenuWindow.clear();
        mainMenuWindow.draw(BGSprite);
        mainMenuWindow.draw(startButton);
        mainMenuWindow.draw(startText);
        mainMenuWindow.draw(helpButton);
        mainMenuWindow.draw(helpText);
        mainMenuWindow.draw(exitButton);
        mainMenuWindow.draw(exitText);
        mainMenuWindow.display();
    }
}

// =================== DEBUT MENU POKEMON SELECTION =================== //

// =================== FIN MENU POKEMON SELECTION =================== //

void Window::handleSelection(bool &jConfirmed, size_t &selectedIndex, std::vector<int> &team, sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey, sf::Keyboard::Key confirmKey)
{
    if (!jConfirmed)
    {
        int rowCount = (allPokemon.size() + 4) / 5; // Calculer le nombre de lignes (en fonction du nombre de Pokémon et de la grille de 5 colonnes)
        int colCount = 5;                           // Le nombre de colonnes est fixé à 5

        // Calculer les indices de la ligne et de la colonne actuelle
        int currentRow = selectedIndex / colCount;
        int currentCol = selectedIndex % colCount;

        if (sf::Keyboard::isKeyPressed(leftKey) && currentCol > 0)
            selectedIndex--; // Se déplacer d'une case à gauche (colonne précédente)

        if (sf::Keyboard::isKeyPressed(rightKey) && currentCol < colCount - 1)
            selectedIndex++; // Se déplacer d'une case à droite (colonne suivante)

        if (sf::Keyboard::isKeyPressed(upKey) && currentRow > 0)
            selectedIndex -= colCount; // Se déplacer d'une ligne vers le haut

        if (sf::Keyboard::isKeyPressed(downKey) && currentRow < rowCount - 1)
            selectedIndex += colCount; // Se déplacer d'une ligne vers le bas

        if (sf::Keyboard::isKeyPressed(confirmKey))
        {
            if (team.size() < 2 && std::find(team.begin(), team.end(), selectedIndex) == team.end())
                team.push_back(selectedIndex);
            if (team.size() == 2)
                jConfirmed = true;
        }
    }
}

void Window::showPokemonSelection()
{
    sf::RenderWindow selectionWindow(sf::VideoMode(1024, 700), "Sélection des Pokémon");

    loadResources("assets/font/prstartk.ttf", "assets/images/selection_background.jpg");
    playMusic("assets/audio/selection.ogg", 50.0, true);

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
            if (event.type == sf::Event::Closed){
                selectionWindow.close();
                exit(0);
            }

            if (event.type == sf::Event::KeyPressed)
            {
                // Sélection du Joueur 1
                handleSelection(j1Confirmed, selectedIndexJ1, teamJ1, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Enter);

                // Sélection du Joueur 2
                handleSelection(j2Confirmed, selectedIndexJ2, teamJ2, sf::Keyboard::Q, sf::Keyboard::D, sf::Keyboard::Z, sf::Keyboard::S, sf::Keyboard::Space);

                // Démarrer le combat
                if (j1Confirmed && j2Confirmed)
                {
                    this->pokemon1 = allPokemon[teamJ1[0]];
                    this->pokemon3 = allPokemon[teamJ1[1]];
                    this->pokemon2 = allPokemon[teamJ2[0]];
                    this->pokemon4 = allPokemon[teamJ2[1]];

                    updatePokemonSprites();
                    initPokemonPostion();
                    pokemon1->initializeMoves();
                    pokemon2->initializeMoves();
                    pokemon3->initializeMoves();
                    pokemon4->initializeMoves();

                    selectionWindow.close();

                    // Affichage des noms des Pokémon sélectionnés
                    displayHealthNames(selectionWindow);

                    playMusic("assets/audio/Music.ogg", 50.0, true);
                    this->window = new sf::RenderWindow(sf::VideoMode(1024, 700), "Combat Pokémon");
                    this->debut = true;
                }
            }
        }

        selectionWindow.clear();
        selectionWindow.draw(BGSprite);

        // Affichage des Pokémon et des encadrés
        for (size_t i = 0; i < allPokemon.size(); i++)
        {
            int row = i / 5;
            int col = i % 5;
            pokemonSprites[i].setPosition(50 + col * 180, 50 + row * 150);
            selectionWindow.draw(pokemonSprites[i]);

            drawHighlight(i, teamJ1, teamJ2, selectedIndexJ1, selectedIndexJ2, j1Confirmed, j2Confirmed, col, row, selectionWindow);
        }
        selectionWindow.display();
    }
}

void Window::drawHighlight(size_t i, const std::vector<int> &teamJ1, const std::vector<int> &teamJ2, size_t selectedIndexJ1, size_t selectedIndexJ2, bool j1Confirmed, bool j2Confirmed, int col, int row, sf::RenderWindow &window)
{
    sf::RectangleShape highlight(sf::Vector2f(120, 120));
    highlight.setPosition(50 + col * 180, 50 + row * 150);

    if (std::find(teamJ1.begin(), teamJ1.end(), i) != teamJ1.end() ||
        std::find(teamJ2.begin(), teamJ2.end(), i) != teamJ2.end() ||
        (!j1Confirmed && i == selectedIndexJ1) ||
        (!j2Confirmed && i == selectedIndexJ2))
    {

        if (!j1Confirmed && std::find(teamJ1.begin(), teamJ1.end(), i) == teamJ1.end() && i == selectedIndexJ1)
        {
            highlight.setOutlineColor(sf::Color::Blue);
            highlight.setOutlineThickness(5);
        }
        else if (j1Confirmed && !j2Confirmed && std::find(teamJ2.begin(), teamJ2.end(), i) == teamJ2.end() && i == selectedIndexJ2)
        {
            highlight.setOutlineColor(sf::Color::Red);
            highlight.setOutlineThickness(6);
        }
        else if (std::find(teamJ1.begin(), teamJ1.end(), i) != teamJ1.end())
        {
            highlight.setOutlineColor(sf::Color::Blue);
            highlight.setOutlineThickness(5);
        }
        else if (std::find(teamJ2.begin(), teamJ2.end(), i) != teamJ2.end())
        {
            highlight.setOutlineColor(sf::Color::Red);
            highlight.setOutlineThickness(6);
        }
        highlight.setFillColor(sf::Color::Transparent);
        window.draw(highlight);
    }
}

void Window::displayHealthNames(sf::RenderWindow &window)
{
    healthText[0].setString(pokemon1->getName());
    healthText[0].setFont(font);
    healthText[0].setCharacterSize(9.5);
    healthText[0].setFillColor(sf::Color::White);
    healthText[0].setPosition(15, 28);
    window.draw(healthText[0]);

    healthText[1].setString(pokemon3->getName());
    healthText[1].setFont(font);
    healthText[1].setCharacterSize(9.5);
    healthText[1].setFillColor(sf::Color::White);
    healthText[1].setPosition(15, 61);
    window.draw(healthText[1]);

    healthText[2].setString(pokemon2->getName());
    healthText[2].setFont(font);
    healthText[2].setCharacterSize(9.5);
    healthText[2].setFillColor(sf::Color::White);
    healthText[2].setPosition(615, 470);
    window.draw(healthText[2]);

    healthText[3].setString(pokemon4->getName());
    healthText[3].setFont(font);
    healthText[3].setCharacterSize(9.5);
    healthText[3].setFillColor(sf::Color::White);
    healthText[3].setPosition(615, 501);
    window.draw(healthText[3]);
}

// =================== MUSIQUE ===================

void Window::playMusic(const std::string &filename, float volume, bool loop)
{
    // Vérifier si la musique en cours est déjà celle demandée
    if (music.getStatus() == sf::Music::Playing && currentMusic == filename)
    {
        return; // Rien à faire si c'est déjà la bonne musique
    }

    if (!music.openFromFile(filename))
    {
        std::cerr << "Erreur : Impossible de charger la musique " << filename << std::endl;
        return;
    }

    music.setLoop(loop);
    music.setVolume(volume);
    music.play();

    currentMusic = filename; // Stocker le nom de la musique en cours pour éviter les rechargements inutiles
}

// =================== MÉTHODES D'INITIALISATION ===================

void Window::initPokemonPostion(void)
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


// =================== BARRE DE VIE =================== //
void Window::initHealthBarElement(sf::RectangleShape &healthElement, const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color &fillColor, const sf::Color &outlineColor, float outlineThickness)
{
    healthElement.setSize(size);
    healthElement.setPosition(position);
    healthElement.setFillColor(fillColor);
    healthElement.setOutlineThickness(outlineThickness);
    healthElement.setOutlineColor(outlineColor);
}

void Window::initializeHealthBars(void)
{
    // Positions et tailles pour les barres de fond
    sf::Vector2f bgBarPos[2] = {{10, 10}, {610, 450}};
    sf::Vector2f bgBarSizes = {300, 90};

    // Positions et tailles pour les barres de vie
    sf::Vector2f barPos[4] = {{100, 30}, {700, 470}, {100, 60}, {700, 500}};
    sf::Vector2f barSizes = {200, 10};

    // Initialisation des barres de fond et des barres de vie
    for (int i = 0; i < 4; i++)
    {
        // Initialisation des barres de fond
        initHealthBarElement(healthBarBackground[i], bgBarPos[i], bgBarSizes, sf::Color(100, 100, 100));

        // Initialisation des barres de vie
        initHealthBarElement(healthBar[i], barPos[i], barSizes, sf::Color::Green, sf::Color::Black, 2.f);
    }
}

void Window::updateHealthBars(float health1Percentage, float health2Percentage, float health3Percentage, float health4Percentage)
{
    // Fonction pour mettre à jour les barres de santé avec un dégradé de couleurs
    auto updateHealthBar = [](sf::RectangleShape &bar, float healthPercentage)
    {
        // Définir la taille de la barre
        bar.setSize(sf::Vector2f(200 * healthPercentage, 20));

        // Dégradé de couleurs (vert -> jaune -> orange -> rouge)
        sf::Color color;
        if (healthPercentage > 0.75f)
        {
            // Vert (santé haute)
            color = sf::Color(0, 255, 0); // Vert
        }
        else if (healthPercentage > 0.5f)
        {
            // Jaune (santé moyenne)
            int green = static_cast<int>(255 * (1.0f - (healthPercentage - 0.5f) * 2));
            color = sf::Color(255, green, 0); // Jaune à orange
        }
        else if (healthPercentage > 0.25f)
        {
            // Orange (santé faible)
            int red = static_cast<int>(255 * (1.0f - (healthPercentage - 0.25f) * 4));
            color = sf::Color(red, 165, 0); // Orange
        }
        else
        {
            // Rouge (santé très faible)
            color = sf::Color(255, 0, 0); // Rouge
        }

        bar.setFillColor(color);
    };

    // Mise à jour des barres de santé pour chaque Pokémon
    updateHealthBar(healthBar[0], health1Percentage);
    updateHealthBar(healthBar[1], health2Percentage);
    updateHealthBar(healthBar[2], health3Percentage);
    updateHealthBar(healthBar[3], health4Percentage);
}
// =================== BARRE DE VIE =================== //



void Window::init()
{
    updatemovebutton(pokemon1);
    updatemovebutton(pokemon3);
    updatemovebutton(pokemon2);
    updatemovebutton(pokemon4);
}

void Window::setupUI()
{
    initializeHealthBars();

    // Stockage des positions originales pour les animations
    for (int i = 0; i < 4; i++)
    {
        originalPos[i] = pokemonSprite[i].getPosition();
    }

    // Initialisation des boutons de mouvement
    sf::Vector2f movePositions[8] = {
        {50, 600}, {250, 600}, {50, 660}, {250, 660}, // J1
        {600, 600},
        {800, 600},
        {600, 660},
        {800, 660} // J2
    };

    for (int i = 0; i < 8; i++)
    {
        initMoveButton(moveButtons[i], moveButtonTexts[i], movePositions[i]);
    }

    // Initialisation du marqueur de ciblage
    targetIndicator.setRadius(25);
    targetIndicator.setFillColor(sf::Color(255, 0, 0, 80)); // Rouge semi-transparent
    targetIndicator.setOutlineColor(sf::Color::Red);
    targetIndicator.setOutlineThickness(5);
    targetIndicator.setOrigin(25, 25);

    // Définition des cibles par défaut
    currentTargetTeam1 = 0;
    currentTargetTeam2 = 0;
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

void Window::initMoveButton(sf::RectangleShape &button, sf::Text &text, sf::Vector2f position)
{
    button.setSize({190, 50});
    button.setFillColor(sf::Color(200, 200, 200));
    button.setPosition(position);

    text.setFont(font);
    text.setCharacterSize(11.5);
    text.setFillColor(sf::Color::Black);
    text.setPosition(position.x + 10, position.y + 10);
}

// =================== MÉTHODES D'ACTION ===================

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
        // Ajouter les touches devant les attaques pour le Joueur 1
        moveButtonTexts[0].setString(moves1[0]->getmovename());
        moveButtonTexts[1].setString(moves1[1]->getmovename());
        moveButtonTexts[2].setString(moves1[2]->getmovename());
        moveButtonTexts[3].setString(moves1[3]->getmovename());

        // Ajouter les touches devant les attaques pour le Joueur 2
        moveButtonTexts[4].setString("Z: " + moves2[0]->getmovename());
        moveButtonTexts[5].setString("Q: " + moves2[1]->getmovename());
        moveButtonTexts[6].setString("S: " + moves2[2]->getmovename());
        moveButtonTexts[7].setString("D: " + moves2[3]->getmovename());
    }
    else
    {
        std::cerr << "Error: Not enough moves for one or both Pokemon" << std::endl;
    }
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

void Window::animateSwitch(bool isTeam1)
{
    if (!isSwapping)
    {
        isSwapping = true;
        swapProgress = 0.0f;
        animationClock.restart();
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

void Window::processevent()
{

    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
            exit(0);
        }
        handleSwitching();
    }
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

// On definie le cercle pour les targets
void Window::setupTargetingSystem(void)
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

// =================== CONSTRUCTEUR / DESTRUCTEUR ===================

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
    this->initPokemonPostion();

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

// =================== AFFICHAGE ===================

// Update the render function
void Window::render()
{
    this->window->clear();

    // Update animations

    updateAnimations();
    updateSwapAnimation();

    // Draw arena
    if (!ArenaTexture.loadFromFile("assets/images/Background.jpg"))
    {
        std::cerr << "Erreur: Impossible de charger le fond." << std::endl;
    }
    ArenaSprite.setTexture(ArenaTexture);
    this->window->draw(ArenaSprite);
    // window->draw(healthbg[0]);
    // window->draw(healthbg[1]);

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
            if (event.type == sf::Event::Closed){
                endGameWindow.close();
                exit(0);
            }

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
