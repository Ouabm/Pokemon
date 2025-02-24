#include "Graphique.hpp"
#include "Pokemon.hpp"
#include "math.h"


Window::Window(): pokemon1("Palkia", "Eau", 100, 100, 100, 100, "images/palkia_back.png"),
    pokemon2("Dialga", "Acier", 100, 100, 100, 100, "images/dialga.png"),
    pokemon3("Giratina", "Acier", 100, 100, 100, 100, "images/giratina_back.png"),
    pokemon4("Arceus", "Acier", 100, 100, 100, 100, "images/arceus.png"),isFirstPokemonAttaking(false),isSecondPokemonAttaking(false),isThirdPokemonAttaking(false),isFourthPokemonAttaking(false),isAnimating(false){
    // Initialisation de la fenêtre
   
    this->window = new sf::RenderWindow(sf::VideoMode(1024, 700), "Combat Pokémon");
    std::cout << "Pokemon1 : [" << pokemon1.getType() << "]" << std::endl;
    animationProgress=0.0f;    
    
    // Initialisation des éléments de l'interface graphique
    this->init_pokemon_positon();
    
    this->pokemon1.initializeMoves();
    this->pokemon2.initializeMoves();
     
    
    this->initializeHealthBars();
    
    this->setupUI();
   
    this->setupSwitchButtons();
     std::cout << "Appel de initializeMoves pour " << this->pokemon1.getName() << std::endl;
      // Initialize attack effect
    attackAnimationTimer = 0.0f;
    attackFrame = 0;
}


Window::~Window() {
    delete this->window; // Libération de la mémoire de la fenêtre
}

void Window::init_pokemon_positon() {
    if (!font.loadFromFile("font/prstartk.ttf")) {
        std::cout << "Font loaded successfully " << std::endl;
    }

    // Création des objets Pokémon avec le constructeur
    // Appliquer la texture aux sprites
    pokemon1_sprite.setTexture(pokemon1.getTexture());  // Pokémon 1 (Gauche)
    pokemon2_sprite.setTexture(pokemon2.getTexture());
    pokemon3_sprite.setTexture(pokemon3.getTexture());
    pokemon4_sprite.setTexture(pokemon4.getTexture());  // Pokémon 2 (Droite)

    pokemon1_sprite.setPosition(20, 290); // Position du Pokémon 1 (Gauche)
    pokemon2_sprite.setPosition(600, 150); // Position du Pokémon 2 (Droite)
    pokemon3_sprite.setPosition(300, 290);
    pokemon4_sprite.setPosition(750, 150);
}

void Window::setupUI() {
    infoJ1.setSize(sf::Vector2f(300, 100));
    infoJ1.setPosition(50, 350);
    infoJ1.setFillColor(sf::Color(255, 255, 255, 200));

    infoJ2.setSize(sf::Vector2f(300, 100));
    infoJ2.setPosition(700, 500);
    infoJ2.setFillColor(sf::Color(255, 255, 255, 200));

    healthbg1.setSize(sf::Vector2f(300, 90));
    healthbg1.setPosition(10, 10);
    healthbg1.setFillColor(sf::Color(100, 100, 100));
    healthbg1.setOutlineThickness(5);
    healthbg1.setOutlineColor(sf::Color::Black);


    healthbg2.setSize(sf::Vector2f(300, 90));
    healthbg2.setPosition(610, 450);
    healthbg2.setFillColor(sf::Color(100, 100, 100));
    healthbg2.setOutlineThickness(5);
    healthbg2.setOutlineColor(sf::Color::Black);

    //Pokemon1
    healthText1.setString(this->pokemon1.getName());
    healthText1.setFont(font);
    healthText1.setCharacterSize(10);
    healthText1.setFillColor(sf::Color::White);
    healthText1.setPosition(15, 29);
    //Pokemon2
    healthText2.setString(this->pokemon3.getName());
    healthText2.setFont(font);
    healthText2.setCharacterSize(10);
    healthText2.setFillColor(sf::Color::White);
    healthText2.setPosition(15, 60);
    //Pokemon3
    healthText3.setString(this->pokemon2.getName());
    healthText3.setFont(font);
    healthText3.setCharacterSize(10);
    healthText3.setFillColor(sf::Color::White);
    healthText3.setPosition(615, 469);
    //Pokemon4
    healthText4.setString(this->pokemon4.getName());
    healthText4.setFont(font);
    healthText4.setCharacterSize(10);
    healthText4.setFillColor(sf::Color::White);
    healthText4.setPosition(615, 500);
    
    


    // Initialiser les boutons de mouvement
    for (int i = 0; i < 8; i++) {
        moveButtons[i].setSize(sf::Vector2f(190, 50));
        moveButtons[i].setFillColor(sf::Color(200, 200, 200));
    }
    //J1
    moveButtons[0].setPosition(50, 600);
    moveButtons[1].setPosition(250, 600);
    moveButtons[2].setPosition(50,660);
    moveButtons[3].setPosition(250,660);
    //J2
    moveButtons[4].setPosition(600, 600);
    moveButtons[5].setPosition(800, 600);
    moveButtons[6].setPosition(600,660);
    moveButtons[7].setPosition(800,660);
    for (int i = 0; i < 8; i++) {
        moveButtonTexts[i].setFont(font);
        moveButtonTexts[i].setCharacterSize(12);
        moveButtonTexts[i].setFillColor(sf::Color::Black);
        moveButtonTexts[i].setPosition(moveButtons[i].getPosition().x + 10,
            moveButtons[i].getPosition().y + 10);
        
    }
    std::vector<move> special1 =pokemon1.getMoves();
    std::vector<move> special2 =pokemon2.getMoves();
    std::cout << "setupUI() : Nombre d'attaques dans special1 : " << special1.size() << std::endl;
    std::cout << "setupUI() : Nombre d'attaques dans special2 : " << special2.size() << std::endl;

if (special1.size() >= 4 && special2.size() >= 4) { 
    moveButtonTexts[0].setString(special1[0].getmovename());
    moveButtonTexts[1].setString(special1[1].getmovename());
    moveButtonTexts[2].setString(special1[2].getmovename());
    moveButtonTexts[3].setString(special1[3].getmovename());
    moveButtonTexts[4].setString(special2[0].getmovename());
    moveButtonTexts[5].setString(special2[1].getmovename());
    moveButtonTexts[6].setString(special2[2].getmovename());
    moveButtonTexts[7].setString(special2[3].getmovename());
} else {
    std::cerr << "Erreur : Pas assez d'attaques disponibles !" << std::endl;
}


}

void Window::initializeHealthBars() {
    // Setup health bar backgrounds
    healthBarBackground1.setSize(sf::Vector2f(200, 10));
    healthBarBackground1.setPosition(50, 20);
    healthBarBackground1.setFillColor(sf::Color(100, 100, 100));

    healthBarBackground2.setSize(sf::Vector2f(200, 20));
    healthBarBackground2.setPosition(700, 450);
    healthBarBackground2.setFillColor(sf::Color(100, 100, 100));

    healthBarBackground3.setSize(sf::Vector2f(200, 20));
    healthBarBackground3.setPosition(50, 50);
    healthBarBackground3.setFillColor(sf::Color(100, 100, 100));

    healthBarBackground4.setSize(sf::Vector2f(200, 20));
    healthBarBackground4.setPosition(700, 480);
    healthBarBackground4.setFillColor(sf::Color(100, 100, 100));


    // Setup health bars
    healthBar1.setSize(sf::Vector2f(200, 10));
    healthBar1.setPosition(100, 30);
    healthBar1.setFillColor(sf::Color::Green);
    healthBar1.setOutlineThickness(2);

    healthBar2.setSize(sf::Vector2f(200, 10));
    healthBar2.setPosition(700, 470);
    healthBar2.setFillColor(sf::Color::Green);
    healthBar2.setOutlineThickness(2);

    healthBar3.setSize(sf::Vector2f(200, 10));
    healthBar3.setPosition(100, 60);
    healthBar3.setFillColor(sf::Color::Green);
    healthBar3.setOutlineThickness(2);

    healthBar4.setSize(sf::Vector2f(200, 10));
    healthBar4.setPosition(700, 500);
    healthBar4.setFillColor(sf::Color::Green);
    healthBar4.setOutlineThickness(2);

    // Store original positions for animations
    originalPos1 = pokemon1_sprite.getPosition();
    originalPos2 = pokemon2_sprite.getPosition();
    originalPos3 = pokemon3_sprite.getPosition();
    originalPos4 = pokemon4_sprite.getPosition();
    
}

void Window::updateHealthBars(float health1Percentage, float health2Percentage,float health3Percentage, float health4Percentage) {
    healthBar1.setSize(sf::Vector2f(200 * health1Percentage, 20));
    healthBar2.setSize(sf::Vector2f(200 * health2Percentage, 20));
    healthBar3.setSize(sf::Vector2f(200 * health3Percentage, 20));
    healthBar4.setSize(sf::Vector2f(200 * health4Percentage, 20));

    
    // Change color based on health
    if (health1Percentage > 0.5f) healthBar1.setFillColor(sf::Color::Green);
    else if (health1Percentage > 0.2f) healthBar1.setFillColor(sf::Color::Yellow);
    else healthBar1.setFillColor(sf::Color::Red);
    
    if (health2Percentage > 0.5f) healthBar2.setFillColor(sf::Color::Green);
    else if (health2Percentage > 0.2f) healthBar2.setFillColor(sf::Color::Yellow);
    else healthBar2.setFillColor(sf::Color::Red);
}

void Window::animateAttack(bool isFirstPokemonAttacking) {
    if (!isAnimating) {
        isAnimating = true;
        animationProgress = 0;
        animationClock.restart();
    }
}

void Window::updateAnimations() {
   
    if (!isAnimating) return;  // Ne rien faire si aucune animation en cours

    float elapsed = attackAnimClock.getElapsedTime().asSeconds();
    float frameDuration = 0.1f;  // Durée de chaque frame d'animation
   
        if (elapsed > frameDuration) {  
            attackAnimClock.restart();  // Redémarrer l’horloge
            currentFrame++;  // Passer à la frame suivante

            int columns = 2;  
            int rows = 7;  
            int frameWidth = attackEffectTexture1.getSize().x / columns;
            int frameHeight = attackEffectTexture1.getSize().y / rows;
            int numFrames = columns * rows;

            if (currentFrame >= numFrames) {  
                currentFrame = 0;  
                isAnimating = false;  
            }

            int x = (currentFrame % columns) * frameWidth;
            int y = (currentFrame / columns) * frameHeight;
            attackEffectSprite1.setTextureRect(sf::IntRect(x, y, frameWidth+10, frameHeight));
            std::cout << "  Frame mise à jour : " << currentFrame << "/" << numFrames 
                    << " | Position : (" << x << ", " << y << ")" << std::endl;
        }

    // ===  Ajout du mouvement Pokémon pendant l’attaque ===
    float attackSpeed = 50.0f;  // Distance de mouvement
    float attackTime = 0.5f;    // Temps total de l'animation

    float attackProgress = animationClock.getElapsedTime().asSeconds() / attackTime;
    sf::Vector2f attackPosition;
    if (attackProgress < 1.0f) {
        float xOffset = sin(attackProgress * 3.14159f) * attackSpeed;
        float yOffset = sin(attackProgress * 3.14159f) * attackSpeed;

        if (isFirstPokemonAttaking) {
            pokemon1_sprite.setPosition(originalPos1.x + xOffset, originalPos1.y - yOffset);
            attackPosition.x=pokemon2_sprite.getPosition().x-70;
            attackPosition.y=pokemon2_sprite.getPosition().y-10;
        }
        else if (isSecondPokemonAttaking) {
            pokemon2_sprite.setPosition(originalPos2.x - xOffset, originalPos2.y + yOffset);
            attackPosition.x=pokemon2_sprite.getPosition().x-60;
            attackPosition.y=pokemon2_sprite.getPosition().y-150;
        }
        else if (isThirdPokemonAttaking) {
            pokemon3_sprite.setPosition(originalPos3.x + xOffset, originalPos3.y - yOffset);
        }
        else if (isFourthPokemonAttaking) {
            pokemon4_sprite.setPosition(originalPos4.x - xOffset, originalPos4.y - yOffset);
        }
        attackEffectSprite1.setPosition(attackPosition);
        attackEffectSprite2.setPosition(attackPosition);
        attackEffectSprite3.setPosition(attackPosition);
        attackEffectSprite4.setPosition(attackPosition);
    }
    else {
        // Fin de l'animation -> Retour aux positions d'origine
        pokemon1_sprite.setPosition(originalPos1);
        pokemon2_sprite.setPosition(originalPos2);
        pokemon3_sprite.setPosition(originalPos3);
        pokemon4_sprite.setPosition(originalPos4);
        
        // Réinitialisation des états d'attaque
        isAnimating = false;
        isFirstPokemonAttaking = false;
        isSecondPokemonAttaking = false;
        isThirdPokemonAttaking = false;
        isFourthPokemonAttaking = false;
    }
}



void Window:: updatemovebutton(Pokemon* pokemon){
    if(pokemon){
        active=pokemon;
        const std::vector<move>&moves =pokemon->getMoves();
        for(int i=0;i<moves.size() && i<4 ;i++){
            moveButtonTexts[i].setString(moves[i].nom);
    }

}
}

// Update the render function
void Window::render() {
    this->window->clear();
    
    // Update animations
    updateAnimations();
    updateSwapAnimation();
    
    // Draw arena
    if (!Arene_texture.loadFromFile("images/Background.jpg")) {
        std::cerr << "Erreur: Impossible de charger le fond." << std::endl;
    }
    Arene_sprite.setTexture(Arene_texture);
    this->window->draw(Arene_sprite);
    window->draw(healthbg1);
    window->draw(healthbg2);
    // Draw health bars
    this->window->draw(healthBarBackground1);
    this->window->draw(healthBarBackground2);
    this->window->draw(healthBar1);
    this->window->draw(healthBar2);
    this->window->draw(healthBar3);
    this->window->draw(healthBar4);
    this->window->draw(healthText1);
    this->window->draw(healthText2);
    this->window->draw(healthText3);
    this->window->draw(healthText4);

    
    // Draw Pokemon sprites
    this->window->draw(pokemon1_sprite);
    this->window->draw(pokemon2_sprite);
    this->window->draw(pokemon3_sprite);
    this->window->draw(pokemon4_sprite);
    
    // Draw move buttons
    for (int i = 0; i < 8 ; i++) {
        window->draw(moveButtons[i]);
        window->draw(moveButtonTexts[i]);
    }
    window->draw(switchButtons);
    window->draw(switchButtonTexts);
    if (isAnimating && !animationFinished) {
        window->draw(attackEffectSprite1);
        //window->draw(attackEffectSprite2);
    }
   
    this->window->display();
}
void Window::handleinput() {
     sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        for (int i = 0; i < 4; i++) {  // Vérifie les boutons des attaques du premier Pokémon
            if (moveButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                isFirstPokemonAttaking = true;
                animateAttack(isFirstPokemonAttaking);

                // Récupérer l'attaque associée
                std::vector<move> moves = pokemon1.getMoves();
                if (i < moves.size()) {
                    setAttackEffectSprite(moves[i].getmovepath());
                }
            }
        }

       
    }
        
    
    
    // Test controls for health bar
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
         // Vérifie les boutons des attaques du premier Pokémon
            std::vector<move> moves = pokemon2.getMoves();
                isSecondPokemonAttaking = true;
                animateAttack(isSecondPokemonAttaking);

                // Récupérer l'attaque associée
        }
    
}
    /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !healthKeyPressed) {
        // 'E' key reduces second Pokemon's health by 10%
        static float health2 = 1.0f;
        health2 = std::max(0.0f, health2 - 0.1f);
        updateHealthBars(1.0f, health2);
        healthKeyPressed = true;
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && 
        !sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        healthKeyPressed = false;
    }
}*/


void Window::processevent() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();

            handleSwitching();
    }
}

/*void Window::updateMoveButton(Pokemon* pokemon) {
    if (pokemon) {
        for (size_t i = 0; i < pokemon->spes.size(); i++) {
            // Mettre à jour le texte et l'état des boutons de mouvement
        }
    }
}*/

void Window::setupSwitchButtons() {
    // Designe button switch à changer 
    
        switchButtons.setSize(sf::Vector2f(150, 40));
        switchButtonTexts.setFont(font);
        switchButtonTexts.setCharacterSize(9);
        switchButtonTexts.setFillColor(sf::Color::Black);
    
    switchButtons.setPosition(50, 550);  // Team 1 switch button
   
    
    switchButtons.setFillColor(sf::Color(200, 200, 200));
    

    
    switchButtonTexts.setString("Switch Pokemon");
   
    
  
    switchButtonTexts.setPosition(60, 560);
    

    // Indices des equipe actives 
    activeTeam1Index = 0;
    activeTeam2Index = 0;
    isSwapping = false;
    swapProgress = 0.0f;

    // revenir au position initial à changer 
    originalPosTeam1[0] = pokemon1_sprite.getPosition();
    originalPosTeam1[1] = pokemon3_sprite.getPosition();
    originalPosTeam2[0] = pokemon2_sprite.getPosition();
    originalPosTeam2[1] = pokemon4_sprite.getPosition();
}

void Window::handleSwitching() {
    // Position curseur 
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

    // Gestion des clicks 
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        // Check if mouse is over team 1's switch button
        if (switchButtons.getGlobalBounds().contains(mousePos.x, mousePos.y) && !isSwapping) {
            animateSwitch(true);  // Start swap animation for team 1
            activeTeam1Index = 1 - activeTeam1Index;  // Toggle between 0 and 1
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&& !isSwapping){
       
            animateSwitch(true);  // Start swap animation for team 2
            activeTeam2Index = 1 - activeTeam2Index;  // Toggle between 0 and 
    
}
}

void Window::animateSwitch(bool isTeam1) {
    if (!isSwapping) {
        isSwapping = true;
        swapProgress = 0.0f;
        animationClock.restart();
    }
}

void Window::updateSwapAnimation() {
    if (isSwapping) {
        float elapsed = animationClock.getElapsedTime().asSeconds();
        swapProgress = elapsed * 2; // 0.5 second animation
        
        if (swapProgress >= 1.0f) {
            // Animation complete, reset positions
            pokemon1_sprite.setPosition(originalPosTeam1[activeTeam1Index]);
            pokemon3_sprite.setPosition(originalPosTeam1[1 - activeTeam1Index]);
            pokemon2_sprite.setPosition(originalPosTeam2[activeTeam2Index]);
            pokemon4_sprite.setPosition(originalPosTeam2[1 - activeTeam2Index]);
            isSwapping = false;
        } else {
            // Animate the swap
            float yOffset = sin(swapProgress * 3.14159f) * 10.0f;
            
            // Team 1 Pokemon
            pokemon1_sprite.setPosition(originalPosTeam1[activeTeam1Index].x,
                                     originalPosTeam1[activeTeam1Index].y - yOffset);
            pokemon3_sprite.setPosition(originalPosTeam1[1 - activeTeam1Index].x,
                                     originalPosTeam1[1 - activeTeam1Index].y + yOffset);
            
            // Team 2 Pokemon
            pokemon2_sprite.setPosition(originalPosTeam2[activeTeam2Index].x,
                                     originalPosTeam2[activeTeam2Index].y - yOffset);
            pokemon4_sprite.setPosition(originalPosTeam2[1 - activeTeam2Index].x,
                                     originalPosTeam2[1 - activeTeam2Index].y + yOffset);
        }
    }
    
}

void Window::setAttackEffectSprite(const std::string& movePath) {
    if (!attackEffectTexture1.loadFromFile(movePath)) {
        std::cerr << "Erreur : Impossible de charger l'effet d'attaque " << movePath << std::endl;
        return;
    }
    attackEffectSprite1.setTexture(attackEffectTexture1);
}