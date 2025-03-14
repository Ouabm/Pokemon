#include "Graphique.hpp"
#include "Pokemon.hpp"
#include "math.h"



Window::Window(): pokemon1(Pokemondb.getPokemonByName("Palkia")),
    pokemon2(Pokemondb.getPokemonByName("Dialga")),
    pokemon3(Pokemondb.getPokemonByName("Arceus")),
    pokemon4(Pokemondb.getPokemonByName("Giratina")),debut(false),isAnimating(false),isFirstPokemonAttaking(false),isSecondPokemonAttaking(false),isThirdPokemonAttaking(false),isFourthPokemonAttaking(false){
    // Initialisation de la fenêtre
   
    
    std::cout << "Pokemon1 : [" << pokemon1.getType() << "]" << std::endl;
    animationProgress=0.0f;    
    isTargetingMode=false;
    isDamageAnimating = false;
    damageAnimationDuration = 0.01f;
    
    
    // Initialisation des éléments de l'interface graphique
    this->init_pokemon_positon();
    
     this->pokemon1.initializeMoves();
     this->pokemon2.initializeMoves();
     this->pokemon3.initializeMoves();
     this->pokemon4.initializeMoves();
    
    
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

void Window::playMusic(const std::string& filename) {
    if (music.getStatus() == sf::Music::Playing) {
        music.stop();  // Arrêter la musique actuelle avant de changer
    }

    if (!music.openFromFile(filename)) {
        std::cerr << "Erreur : Impossible de charger la musique " << filename << std::endl;
        return;
    }

    music.setLoop(true);
    music.setVolume(50);
    music.play();
}
void Window::init_music(){
   playMusic("audio/Music.ogg");
}

void Window::init() {
    updatemovebutton(&pokemon1);
    updatemovebutton(&pokemon3);
    updatemovebutton(&pokemon2);
    updatemovebutton(&pokemon4);
}
void Window::init_pokemon_positon() {
    if (!font.loadFromFile("font/prstartk.ttf")) {
        std::cout << "Font loaded successfully " << std::endl;
    }

    // Création des objets Pokémon avec le constructeur
    // Appliquer la texture aux sprites
    pokemon1_sprite.setTexture(pokemon1.getTextureback());  // Pokémon 1 (Gauche)
    pokemon2_sprite.setTexture(pokemon2.getTexturefront());
    pokemon3_sprite.setTexture(pokemon3.getTextureback());
    pokemon4_sprite.setTexture(pokemon4.getTexturefront());  // Pokémon 2 (Droite)

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
//     std::vector<move> special1 =pokemon1.getMoves();
//     std::vector<move> special2 =pokemon2.getMoves();
//     std::vector<move> special3 =pokemon3.getMoves();
//     std::vector<move> special4 =pokemon4.getMoves();
//     std::cout << "setupUI() : Nombre d'attaques dans special1 : " << special1.size() << std::endl;
//     std::cout << "setupUI() : Nombre d'attaques dans special2 : " << special2.size() << std::endl;

// if (special1.size() >= 4 && special2.size() >= 4) { 
//     moveButtonTexts[0].setString(special1[0].getmovename());
//     moveButtonTexts[1].setString(special1[1].getmovename());
//     moveButtonTexts[2].setString(special1[2].getmovename());
//     moveButtonTexts[3].setString(special1[3].getmovename());
//     moveButtonTexts[4].setString(special2[0].getmovename());
//     moveButtonTexts[5].setString(special2[1].getmovename());
//     moveButtonTexts[6].setString(special2[2].getmovename());
//     moveButtonTexts[7].setString(special2[3].getmovename());
// }



//Target 
   targetIndicator.setRadius(25);
    targetIndicator.setFillColor(sf::Color(255, 0, 0, 80));  // Semi-transparent red
    targetIndicator.setOutlineColor(sf::Color::Red);
    targetIndicator.setOutlineThickness(5);
    targetIndicator.setOrigin(25, 25);  //
    // Default targets
    currentTargetTeam1 = 0;
    currentTargetTeam2 = 0;
    
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

    healthBar3.setSize(sf::Vector2f(200, 5));
    healthBar3.setPosition(100, 60);
    healthBar3.setFillColor(sf::Color::Green);
    healthBar3.setOutlineThickness(2);

    healthBar4.setSize(sf::Vector2f(200, 5));
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
   
       if (!isAnimating) return;

    float elapsed = attackAnimClock.getElapsedTime().asSeconds();
    float frameDuration = 0.04f;
   
    if (elapsed > frameDuration) {  
        attackAnimClock.restart();
        currentFrame++;

        int columns = 2;  
        int rows = 7;  
        int frameWidth = attackEffectTexture1.getSize().x / columns;
        int frameHeight = attackEffectTexture1.getSize().y / rows;
        int numFrames = columns * rows-1;

        if (currentFrame >= numFrames) {  
            currentFrame = 0;  
            isAnimating = false;
            
            // Reset Pokemon colors when attack animation ends
            pokemon1_sprite.setColor(sf::Color::White);
            pokemon2_sprite.setColor(sf::Color::White);
            pokemon3_sprite.setColor(sf::Color::White);
            pokemon4_sprite.setColor(sf::Color::White);
        }

        int x = (currentFrame % columns) * frameWidth;
        int y = (currentFrame / columns) * frameHeight;
        attackEffectSprite1.setTextureRect(sf::IntRect(x, y, frameWidth+10, frameHeight));
        std::cout << "  Frame mise à jour : " << currentFrame << "/" << numFrames 
                    << " | Position : (" << x << ", " << y << ")" << std::endl;
    }

    // ===  Attack movement animation === animateAttack(isSecondPokemonAttaking);

    float attackSpeed = 50.0f;
    float attackTime = 0.5f;

    float attackProgress = animationClock.getElapsedTime().asSeconds() / attackTime;
    sf::Vector2f attackPosition;
    
    if (attackProgress < 1.0f) {
        float xOffset = sin(attackProgress * 3.14159f) * attackSpeed;
        float yOffset = sin(attackProgress * 3.14159f) * attackSpeed;

        // Set the target Pokemon red during the attack
      if (isFirstPokemonAttaking || isThirdPokemonAttaking) {
            sf::Sprite& attackerSprite = isFirstPokemonAttaking ? pokemon1_sprite : pokemon3_sprite;
            sf::Sprite& targetSprite = (currentTargetTeam1 == 0) ? pokemon2_sprite : pokemon4_sprite;
            
            // Attacker movement
            attackerSprite.setPosition(
                (isFirstPokemonAttaking ? originalPos1 : originalPos3).x + xOffset, 
                (isFirstPokemonAttaking ? originalPos1 : originalPos3).y - yOffset
            );
            
            // Target effects
            targetSprite.setColor(sf::Color(255, 0, 0, 255));  // Target turns red
            targetSprite.setPosition(
                (currentTargetTeam1 == 0 ? originalPos2 : originalPos4).x - 8, 
                (currentTargetTeam1 == 0 ? originalPos2 : originalPos4).y + 8
            );
            
            // Position attack effect sprite
            attackPosition.x = targetSprite.getPosition().x - 70;
            attackPosition.y = targetSprite.getPosition().y - 10;
        }
        // When Team 2 is attacking
        else if (isSecondPokemonAttaking || isFourthPokemonAttaking) {
            sf::Sprite& attackerSprite = isSecondPokemonAttaking ? pokemon2_sprite : pokemon4_sprite;
            sf::Sprite& targetSprite = (currentTargetTeam2 == 0) ? pokemon1_sprite : pokemon3_sprite;
            
            // Attacker movement
            attackerSprite.setPosition(
                (isSecondPokemonAttaking ? originalPos2 : originalPos4).x - xOffset, 
                (isSecondPokemonAttaking ? originalPos2 : originalPos4).y + yOffset
            );
            
            // Target effects
            targetSprite.setColor(sf::Color(255, 0, 0, 255));  // Target turns red
            targetSprite.setPosition(
                (currentTargetTeam2 == 0 ? originalPos1 : originalPos3).x - 8, 
                (currentTargetTeam2 == 0 ? originalPos1 : originalPos3).y + 8
            );
            
            // Position attack effect sprite
            attackPosition.x = targetSprite.getPosition().x + 40;
            attackPosition.y = targetSprite.getPosition().y + 100;
        }
        
        attackEffectSprite1.setPosition(attackPosition);
        attackEffectSprite2.setPosition(attackPosition);
        attackEffectSprite3.setPosition(attackPosition);
        attackEffectSprite4.setPosition(attackPosition);
    }
    else {
        // Reset all colors and positions when animation ends
        pokemon1_sprite.setColor(sf::Color::White);
        pokemon2_sprite.setColor(sf::Color::White);
        pokemon3_sprite.setColor(sf::Color::White);
        pokemon4_sprite.setColor(sf::Color::White);
        
        // Return to original positions
        pokemon1_sprite.setPosition(originalPos1);
        pokemon2_sprite.setPosition(originalPos2);
        pokemon3_sprite.setPosition(originalPos3);
        pokemon4_sprite.setPosition(originalPos4);
        
        // Reset animation states
        
        isAnimating = false;
        isFirstPokemonAttaking = false;
        isSecondPokemonAttaking = false;
        isThirdPokemonAttaking = false;
        isFourthPokemonAttaking = false;
        
        currentFrame=0;
    }
    
}




void Window:: updatemovebutton(Pokemon* pokemon){
    if(pokemon){
        active=pokemon;
        const std::vector<move>&moves =pokemon->getMoves();
        for(size_t i=0;i<moves.size() && i<4 ;i++){
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
    window->draw(switchButtons2);
    window->draw(switchButtonTexts2);
     
    if (isAnimating && !animationFinished) {
        window->draw(attackEffectSprite1);
        //window->draw(attackEffectSprite2);
    }
    renderTargetIndicator();
    
   
   
    this->window->display();
}
void Window::handleinput() {
    sf::Vector2f mousePos = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
    
    // // Targeting mode toggle
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
    //     isTargetingMode = !isTargetingMode;  // Toggle targeting mode on/off
        
    //     // When entering targeting mode, set default attackers
    //     if (isTargetingMode) {
    //         // Determine which team is currently selecting a target
    //         if (activeTeam1Index == 0) {
    //             // Pokemon 1 is active for team 1
    //             isFirstPokemonAttaking = true;
    //             isThirdPokemonAttaking = false;
    //         } else {
    //             // Pokemon 3 is active for team 1
    //             isFirstPokemonAttaking = false;
    //             isThirdPokemonAttaking = true;
    //         }
            
    //         // Reset other attackers
    //         isSecondPokemonAttaking = false;
    //         isFourthPokemonAttaking = false;
    //     }
    // }
    
    
    // Target cycling (only when in targeting mode)
   /*if (isTargetingMode) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
            // Cycle targets based on which team is attacking
            if (isFirstPokemonAttaking || isThirdPokemonAttaking) {
                cycleTargets(true);//ici l'index tema 1 repasse a 0 
            } else if (isSecondPokemonAttaking || isFourthPokemonAttaking) {
                cycleTargets(false);//ici index team2 passe a 0
            }
        }
        
        // Exit targeting mode with Escape key
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
            isTargetingMode = false;
        }
    }*/
    
    // Attack buttons (only process when not in targeting mode or animation)
    if (!isTargetingMode && !isAnimating) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            for (size_t i = 0; i < 4; i++) {
                if (moveButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    moveButtons[i].setOutlineThickness(5);
                    moveButtons[i].setOutlineColor(sf::Color::Red);
                    
                    // // Set the attacker based on active team 1 index
                    // if (activeTeam1Index == 0) {
                    //     isFirstPokemonAttaking = true;
                    //     isThirdPokemonAttaking = false;
                    // } else {
                    //     isFirstPokemonAttaking = false;
                    //     isThirdPokemonAttaking = true;
                    // }
                    
                    // Start the attack animation
                    //animateAttack(isFirstPokemonAttaking);
                    
                    // Get the attack move
                    /*std::vector<move> moves = activeTeam1Index == 0 ? pokemon1.getMoves() : pokemon3.getMoves();
                    if (i < moves.size()) {
                        setAttackEffectSprite(moves[i].getmovepath());
                    }*/
                }
            }
        } else {
            for (size_t i = 0; i < 4; i++) {
                moveButtons[i].setOutlineThickness(0);
            }
        }
        /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
        isTargetingMode = !isTargetingMode;  // Toggle targeting mode on/off
        
        // When entering targeting mode, set default attackers
        if (isTargetingMode) {
            // Determine which team is currently selecting a target
            if (activeTeam1Index == 0) {
                // Pokemon 1 is active for team 1
                isSecondPokemonAttaking = true;
                isFourthPokemonAttaking = false;
            } else {
                // Pokemon 3 is active for team 1
                isSecondPokemonAttaking = false;
                isFourthPokemonAttaking = true;
            }
            
            // Reset other attackers
            isFirstPokemonAttaking = false;
            isThirdPokemonAttaking = false;
        }
    }*/
        // Handle Team 2 attacks with keyboard (ZQSD keys)
        // Similar logic for team 2 attacks as shown in your original code...
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        std::vector<move> moves = activeTeam2Index == 0 ? pokemon2.getMoves() : pokemon4.getMoves();
         // Vérifie les boutons des attaques du premier Pokémon
           
            moveButtons[4].setOutlineThickness(5);
            moveButtons[4].setOutlineColor(sf::Color::Red);
            // moveButtons[4].setScale(1.1f,1.f);
            // moveButtonTexts[4].setScale(1.1f,1.1f);
            //  if (activeTeam2Index == 0) {
            //             isSecondPokemonAttaking = true;
            //             isFourthPokemonAttaking = false;
            //         } else {
            //             isSecondPokemonAttaking = false;
            //             isFourthPokemonAttaking = true;
            //         }
                //animateAttack(isSecondPokemonAttaking);
                //setAttackEffectSprite(moves[0].getmovepath());
               

            
                
               
    }
    else {
        moveButtons[4].setOutlineThickness(0);
        // moveButtons[4].setScale(1.f,1.f);
        // moveButtonTexts[4].setScale(1.f,1.f);

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {

        std::vector<move> moves = activeTeam2Index == 0 ? pokemon2.getMoves() : pokemon4.getMoves();
         
            moveButtons[5].setOutlineThickness(5);
            moveButtons[5].setOutlineColor(sf::Color::Red);
            // moveButtons[4].setScale(1.1f,1.f);
            // // moveButtonTexts[4].setScale(1.1f,1.1f);
            //  if (activeTeam2Index == 0) {
            //             isSecondPokemonAttaking = true;
            //             isFourthPokemonAttaking = false;
            //         } else {
            //             isSecondPokemonAttaking = false;
            //             isFourthPokemonAttaking = true;
            //         }
                //animateAttack(isSecondPokemonAttaking);
                //setAttackEffectSprite(moves[1].getmovepath());
                //isSecondPokemonAttaking = true;
               

            
        }
    else {
        moveButtons[5].setOutlineThickness(0);
        // moveButtons[4].setScale(1.f,1.f);
        // moveButtonTexts[4].setScale(1.f,1.f);

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        std::vector<move> moves = activeTeam2Index == 0 ? pokemon2.getMoves() : pokemon4.getMoves();
       
            moveButtons[6].setOutlineThickness(5);
            moveButtons[6].setOutlineColor(sf::Color::Red);
            // moveButtons[4].setScale(1.1f,1.f);
            // moveButtonTexts[4].setScale(1.1f,1.1f);
            //  if (activeTeam2Index == 0) {
            //             isSecondPokemonAttaking = true;
            //             isFourthPokemonAttaking = false;
            //         } else {
            //             isSecondPokemonAttaking = false;
            //             isFourthPokemonAttaking = true;
            //         }
                //animateAttack(isSecondPokemonAttaking);
                //setAttackEffectSprite(moves[2].getmovepath());
                //isSecondPokemonAttaking = true;
                
            
        }
    else {
        moveButtons[6].setOutlineThickness(0);
        // moveButtons[4].setScale(1.f,1.f);
        // moveButtonTexts[4].setScale(1.f,1.f);

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        std::vector<move> moves = activeTeam2Index == 0 ? pokemon2.getMoves() : pokemon4.getMoves();
         //
            moveButtons[7].setOutlineThickness(5);
            moveButtons[7].setOutlineColor(sf::Color::Red);
            // moveButtons[4].setScale(1.1f,1.f);
            // moveButtonTexts[4].setScale(1.1f,1.1f);
            //  if (activeTeam2Index == 0) {
            //             isSecondPokemonAttaking = true;
            //             isFourthPokemonAttaking = false;
            //         } else {
            //             isSecondPokemonAttaking = false;
            //             isFourthPokemonAttaking = true;
            //         }
                //animateAttack(isSecondPokemonAttaking);
                //setAttackEffectSprite(moves[3].getmovepath());
                //isSecondPokemonAttaking = true;
               
            
        }
    else {
        moveButtons[7].setOutlineThickness(0);
        // moveButtons[4].setScale(1.f,1.f);
        // moveButtonTexts[4].setScale(1.f,1.f);

    }

    }
}

    /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
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
        if (event.type == sf::Event::Closed){
            window->close();
            
        }
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

        switchButtons2.setSize(sf::Vector2f(150, 40));
        switchButtonTexts2.setFont(font);
        switchButtonTexts2.setCharacterSize(9);
        switchButtonTexts2.setFillColor(sf::Color::Black);
    
    switchButtons.setPosition(50, 550);  // Team 1 switch button
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
    originalPosTeam1[0] = pokemon1_sprite.getPosition();
    originalPosTeam1[1] = pokemon3_sprite.getPosition();
    originalPosTeam2[0] = pokemon2_sprite.getPosition();
    originalPosTeam2[1] = pokemon4_sprite.getPosition();
}

void Window::handleSwitching() {
    // Position curseur 
    sf::Vector2f mousePos = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

    // Gestion des clicks 
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        // Check if mouse is over team 1's switch button
        if (switchButtons.getGlobalBounds().contains(mousePos.x, mousePos.y) && !isSwapping) {
            switchButtons.setScale(1.1f,1.1f);
            switchButtonTexts.setScale(1.1f,1.1f);
            animateSwitch(true);  // Start swap animation for team 1
            activeTeam1Index = 1 - activeTeam1Index;  // Toggle between 0 and 1
            updateMoveButtons(); 
        }
        
    }
    else{
            switchButtons.setScale(1.f,1.f);
            switchButtonTexts.setScale(1.f,1.f);
        }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)&&  !isSwapping){
            switchButtons2.setScale(1.1f,1.1f);
            switchButtonTexts2.setScale(1.1f,1.1f);
            activeTeam2Index = 1 - activeTeam2Index;
            animateSwitch(false);  // Start swap animation for team 2
            updateMoveButtons(); 
           
            

            // Toggle between 0 and 
    
    }

    else{
            switchButtons2.setScale(1.f,1.f);
            switchButtonTexts2.setScale(1.f,1.f);
           
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
            pokemon1_sprite.setPosition(originalPosTeam1[0]);
            pokemon3_sprite.setPosition(originalPosTeam1[1]);
            pokemon2_sprite.setPosition(originalPosTeam2[0]);
            pokemon4_sprite.setPosition(originalPosTeam2[1]);
            isSwapping = false;
            // Animate the swap
            float yOffset = sin(swapProgress * 3.14159f) * 10.0f;
            
            
            // Team 1 Pokemon
            pokemon1_sprite.setPosition(originalPosTeam1[0].x,
                                     originalPosTeam1[0].y + yOffset);
            pokemon3_sprite.setPosition(originalPosTeam1[1].x,
                                     originalPosTeam1[1].y + yOffset);
            
            // Team 2 Pokemon
            pokemon2_sprite.setPosition(originalPosTeam2[0].x,
                                     originalPosTeam2[0].y - yOffset);
            pokemon4_sprite.setPosition(originalPosTeam2[1].x,
                                     originalPosTeam2[1].y + yOffset);
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

//On definie le cercle pour les targets 
void Window::setupTargetingSystem() {
    // Setup target indicator
    targetIndicator.setRadius(15);
    targetIndicator.setFillColor(sf::Color::Transparent);
    targetIndicator.setOutlineColor(sf::Color::Red);
    targetIndicator.setOutlineThickness(3);
    targetIndicator.setOrigin(15, 15);  // Center the circle
    
    // Default targets
    currentTargetTeam1 = 1;  // Default to pokemon2
    currentTargetTeam2 = 1;  // Default to pokemon1
}

// Method to render the target indicator

// Method to cycle through targets
void Window::cycleTargets(bool isTeam1) {
    if (isTeam1) {
        currentTargetTeam1 = 1 - currentTargetTeam1;  // ici c'est gauche qui attack 
    } else {
        currentTargetTeam2 = 1 - currentTargetTeam2;  // ici c'est droit qui attack 
    }
}

// Get the currently targeted Pokemon
Pokemon* Window::getCurrentTarget(bool isTeam1) {
    if (isTeam1) {
        return (currentTargetTeam1 == 0) ? &pokemon2 : &pokemon4; //si c'est tema1 et qu'il target 
    } else {
        return (currentTargetTeam2 == 0) ? &pokemon1 : &pokemon3;
    }
}

// void Window::confirmTargetAndAttack() {
//     // Set the appropriate attack flag based on which Pokemon is attacking
//     if (selectedAttackingPokemon == &pokemon1) {
//         isFirstPokemonAttaking = true;
//     } else if (selectedAttackingPokemon == &pokemon2) {
//         isSecondPokemonAttaking = true;
//     } else if (selectedAttackingPokemon == &pokemon3) {
//         isThirdPokemonAttaking = true;
//     } else if (selectedAttackingPokemon == &pokemon4) {
//         isFourthPokemonAttaking = true;
//     }
    
//     // Start the attack animation
//     animateAttack(isFirstPokemonAttaking || isThirdPokemonAttaking);
//     animateAttack(isSecondPokemonAttaking || isFourthPokemonAttaking);
    
//     // Get the appropriate moves vector
//     std::vector<move> moves;
//     if (selectedAttackingPokemon == &pokemon1) {
//         moves = pokemon1.getMoves();
//     } else if (selectedAttackingPokemon == &pokemon2) {
//         moves = pokemon2.getMoves();
//     } else if (selectedAttackingPokemon == &pokemon3) {
//         moves = pokemon3.getMoves();
//     } else if (selectedAttackingPokemon == &pokemon4) {
//         moves = pokemon4.getMoves();
//     }
    
//     // Set the attack effect sprite
//     if (selectedAttackIndex < moves.size()) {
//         setAttackEffectSprite(moves[selectedAttackIndex].getmovepath());
//     }
    
//     // Exit targeting mode
//     isTargetingMode = false;
// }
void Window::renderTargetIndicator() {
    if (!isTargetingMode) return;
    
    // Position the indicator on the current target
    sf::Vector2f targetPos;
    
    // If team 1 is targeting
    if (isFirstPokemonAttaking || isThirdPokemonAttaking) {
        if (currentTargetTeam1 == 0) {
            // Targeting pokemon2
            targetPos = pokemon2_sprite.getPosition();
            targetPos.x += pokemon2_sprite.getGlobalBounds().width / 2;
            targetPos.y += pokemon2_sprite.getGlobalBounds().height / 2;
        } 
        else {
            // Targeting pokemon4
            targetPos = pokemon4_sprite.getPosition();
            targetPos.x += pokemon4_sprite.getGlobalBounds().width / 2;
            targetPos.y += pokemon4_sprite.getGlobalBounds().height / 2;
        }
    } 
    // If team 2 is targeting
    else if (isSecondPokemonAttaking || isFourthPokemonAttaking) {
        if (currentTargetTeam2 == 0) {
            // Targeting pokemon1
            targetPos = pokemon1_sprite.getPosition();
            targetPos.x += pokemon1_sprite.getGlobalBounds().width / 2;
            targetPos.y += pokemon1_sprite.getGlobalBounds().height / 2;
        } else {
            // Targeting pokemon3
            targetPos = pokemon3_sprite.getPosition();
            targetPos.x += pokemon3_sprite.getGlobalBounds().width / 2;
            targetPos.y += pokemon3_sprite.getGlobalBounds().height / 2;
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
void Window::updateMoveButtons() {
    // Get the currently active Pokemon for each team
    Pokemon* activePokemon1 = (activeTeam1Index == 0) ? &pokemon1 : &pokemon3;
    Pokemon* activePokemon2 = (activeTeam2Index == 0) ? &pokemon2 : &pokemon4;

    // Get their moves
    std::vector<move> moves1 = activePokemon1->getMoves();
    std::vector<move> moves2 = activePokemon2->getMoves();

    // Debug output to check what's happening
    std::cout << "Updating move buttons. Team 1 active: " 
              << activePokemon1->getName() 
              << " with " << moves1.size() << " moves" << std::endl;
    std::cout << "Updating move buttons. Team 2 active: " 
              << activePokemon2->getName() 
              << " with " << moves2.size() << " moves" << std::endl;

    // Make sure we have moves to display
    if (moves1.size() >= 4 && moves2.size() >= 4) {
        // Update Team 1 move buttons (0-3)
        for (int i = 0; i < 4; i++) {
            moveButtonTexts[i].setString(moves1[i].getmovename());
            std::cout << "Team 1 move " << i << ": " << moves1[i].getmovename() << std::endl;
        }
        
        // Update Team 2 move buttons (4-7)
        for (int i = 0; i < 4; i++) {
            moveButtonTexts[i+4].setString(moves2[i].getmovename());
            std::cout << "Team 2 move " << i << ": " << moves2[i].getmovename() << std::endl;
        }
    } else {
        std::cerr << "Error: Not enough moves for one or both Pokemon" << std::endl;
    }
}
void Window::showPokemonSelection() {
    sf::RenderWindow selectionWindow(sf::VideoMode(1024, 700), "Sélection des Pokémon");
    playMusic("audio/selection.ogg");
    // Charger l'image de fond
    sf::Texture background;
    if (!background.loadFromFile("images/selection_background.jpg")) {
        std::cerr << "Error: Unable to load background image" << std::endl;
    }
    sf::Sprite background_sprite(background);

    // Charger la police
    if (!font.loadFromFile("font/prstartk.ttf")) {
        std::cerr << "Erreur de chargement de la police !" << std::endl;
    }

    // Charger les textures des Pokémon
    std::vector<sf::Texture> pokemonTextures(allPokemon.size());
    std::vector<sf::Sprite> pokemonSprites(allPokemon.size());

    for (size_t i = 0; i < allPokemon.size(); i++) {
        if (!pokemonTextures[i].loadFromFile("images/" + allPokemon[i].getName() + ".png")) {
            std::cerr << "Erreur de chargement de l'image pour " << allPokemon[i].getName() << std::endl;
        }
        pokemonSprites[i].setTexture(pokemonTextures[i]);
        pokemonSprites[i].setScale(0.7f, 0.7f); // Ajuster la taille
    }

    size_t selectedIndexJ1 = 0, selectedIndexJ2 = 0;
    bool j1Confirmed = false, j2Confirmed = false;
    std::vector<int> teamJ1, teamJ2;

    while (selectionWindow.isOpen()) {
        sf::Event event;
        while (selectionWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                selectionWindow.close();

            if (event.type == sf::Event::KeyPressed) {
                // Sélection du Joueur 1
                if (!j1Confirmed) {
                    if (event.key.code == sf::Keyboard::Left)
                        selectedIndexJ1 = (selectedIndexJ1 - 1 + allPokemon.size()) % allPokemon.size();
                    if (event.key.code == sf::Keyboard::Right)
                        selectedIndexJ1 = (selectedIndexJ1 + 1) % allPokemon.size();
                    if (event.key.code == sf::Keyboard::Enter) {
                        if (teamJ1.size() < 2 && std::find(teamJ1.begin(), teamJ1.end(), selectedIndexJ1) == teamJ1.end()) {
                            teamJ1.push_back(selectedIndexJ1);
                        }
                        if (teamJ1.size() == 2) j1Confirmed = true;
                    }
                }
                
                // Sélection du Joueur 2
                else if (!j2Confirmed) {
                    if (event.key.code == sf::Keyboard::A)
                        selectedIndexJ2 = (selectedIndexJ2 - 1 + allPokemon.size()) % allPokemon.size();
                    if (event.key.code == sf::Keyboard::D)
                        selectedIndexJ2 = (selectedIndexJ2 + 1) % allPokemon.size();
                    if (event.key.code == sf::Keyboard::Space) {
                        if (teamJ2.size() < 2 && std::find(teamJ2.begin(), teamJ2.end(), selectedIndexJ2) == teamJ2.end()) {
                            teamJ2.push_back(selectedIndexJ2);
                        }
                        if (teamJ2.size() == 2) j2Confirmed = true;
                    }
                }

                // Démarrer le combat
                if (j1Confirmed && j2Confirmed) {
                    this->pokemon1 = allPokemon[teamJ1[0]];
                    this->pokemon3 = allPokemon[teamJ1[1]];
                    this->pokemon2 = allPokemon[teamJ2[0]];
                    this->pokemon4 = allPokemon[teamJ2[1]];
                   
                    selectionWindow.close();
                    init_music();
                    this->window = new sf::RenderWindow(sf::VideoMode(1024, 700), "Combat Pokémon");
                    this->debut=true;
                }
            }
        }

        selectionWindow.clear();
        selectionWindow.draw(background_sprite);

        // Affichage des Pokémon
        for (size_t i = 0; i < allPokemon.size(); i++) {
            int row = i / 5;
            int col = i % 5;
            pokemonSprites[i].setPosition(50 + col * 180, 50 + row * 150);
            selectionWindow.draw(pokemonSprites[i]);

            // Encadrer les Pokémon sélectionnés
            if(std::find(teamJ1.begin(), teamJ1.end(), i) != teamJ1.end() ||
            std::find(teamJ2.begin(), teamJ2.end(), i) != teamJ2.end() ||
            (!j1Confirmed && i == selectedIndexJ1) ||
            (!j2Confirmed && i == selectedIndexJ2)){
                sf::RectangleShape highlight(sf::Vector2f(120, 120));
                highlight.setPosition(50 + col * 180, 50 + row * 150);
                highlight.setOutlineThickness(5);
                highlight.setOutlineColor(
                    std::find(teamJ1.begin(), teamJ1.end(), i) != teamJ1.end() ? sf::Color::Blue : sf::Color::Red);
                highlight.setFillColor(sf::Color::Transparent);
                selectionWindow.draw(highlight);
            }
        }
    
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
    


        selectionWindow.display();
    }
}
void Window::showMainMenu() {
    sf::RenderWindow menuWindow(sf::VideoMode(1024, 640), "Menu Principal");
    playMusic("audio/Title.ogg");
    // Charger la police
    if (!font.loadFromFile("font/prstartk.ttf")) {
        std::cerr << "Erreur de chargement de la police !" << std::endl;
    }

    //Fond 
     
     if (!backgroundm.loadFromFile("images/Menu.jpg")) {
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

    while (menuWindow.isOpen()) {
        sf::Event event;
        while (menuWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                menuWindow.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = menuWindow.mapPixelToCoords(sf::Mouse::getPosition(menuWindow));

                // Vérifier si "Start" est cliqué
                if (startButton.getGlobalBounds().contains(mousePos)) {
                    menuWindow.close();
                    showPokemonSelection(); // Lancer la sélection de Pokémon
                }

                // Vérifier si "Help" est cliqué
                if (helpButton.getGlobalBounds().contains(mousePos)) {
                    sf::RenderWindow helpWindow(sf::VideoMode(600, 400), "Instructions");
                    sf::Text instructions("Choisissez 2 Pokemon chacun et combattez !\nUtilisez les attaques pour battre votre adversaire.", font, 7);
                    instructions.setFillColor(sf::Color::White);
                    instructions.setPosition(50, 100);

                    while (helpWindow.isOpen()) {
                        sf::Event helpEvent;
                        while (helpWindow.pollEvent(helpEvent)) {
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

void Window::showEndGameMenu(int winningTeam) {
    sf::RenderWindow endGameWindow(sf::VideoMode(1024, 640), "Fin du jeu");

    // Charger la police
    if (!font.loadFromFile("font/prstartk.ttf")) {
        std::cerr << "Erreur de chargement de la police !" << std::endl;
    }

    if (!backgroundfin.loadFromFile("images/end_game.jpg")) {
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

    while (endGameWindow.isOpen()) {
        sf::Event event;
        window->close();
        while (endGameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                endGameWindow.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = endGameWindow.mapPixelToCoords(sf::Mouse::getPosition(endGameWindow));

                if (replayButton.getGlobalBounds().contains(mousePos)) {
                    endGameWindow.close();
                    showMainMenu();  // Retour au menu principal
                }

                if (quitButton.getGlobalBounds().contains(mousePos)) {
                    endGameWindow.close();
                    exit(0);  // Quitte totalement le jeu
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
