#include "Graphique.hpp"
#include "Pokemon.hpp"
#include "math.h"


Window::Window(): pokemon1("Palkia", "Eau", 100, 100, 100, 100, "images/palkia_back.png"),
    pokemon2("Dialga", "Acier", 100, 100, 100, 100, "images/dialga.png"),
    pokemon3("Giratina", "Acier", 100, 100, 100, 100, "images/giratina_back.png"),
    pokemon4("Arceus", "Acier", 100, 100, 100, 100, "images/arceus.png"),isFirstPokemonAttaking(false),isAnimating(false){
    // Initialisation de la fenêtre
    this->window = new sf::RenderWindow(sf::VideoMode(1024, 700), "Combat Pokémon");
    animationProgress=0.0f;    
    
    // Initialisation des éléments de l'interface graphique
    this->init_pokemon_positon();
    this->initializeHealthBars();
    this->setupUI();
}

Window::~Window() {
    delete this->window; // Libération de la mémoire de la fenêtre
}

void Window::init_pokemon_positon() {
    if (!font.loadFromFile("arial/arial.ttf")) {
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
    infoJ2.setPosition(450, 500);
    infoJ2.setFillColor(sf::Color(255, 255, 255, 200));

    // Initialiser les boutons de mouvement
    for (int i = 0; i < 4; i++) {
        moveButtons[i].setSize(sf::Vector2f(190, 50));
        moveButtons[i].setPosition(50 + (i % 2) * 200, 600 + (i / 2) * 60);
        moveButtons[i].setFillColor(sf::Color(200, 200, 200));
    }
}

void Window::initializeHealthBars() {
    // Setup health bar backgrounds
    healthBarBackground1.setSize(sf::Vector2f(200, 20));
    healthBarBackground1.setPosition(50, 20);
    healthBarBackground1.setFillColor(sf::Color(100, 100, 100));

    healthBarBackground2.setSize(sf::Vector2f(200, 20));
    healthBarBackground2.setPosition(700, 450);
    healthBarBackground2.setFillColor(sf::Color(100, 100, 100));

    healthBarBackground3.setSize(sf::Vector2f(200, 20));
    healthBarBackground3.setPosition(50, 50);
    healthBarBackground3.setFillColor(sf::Color(100, 100, 100));

    healthBarBackground4.setSize(sf::Vector2f(200, 20));
    healthBarBackground4.setPosition(700, 490);
    healthBarBackground4.setFillColor(sf::Color(100, 100, 100));


    // Setup health bars
    healthBar1.setSize(sf::Vector2f(200, 20));
    healthBar1.setPosition(50, 20);
    healthBar1.setFillColor(sf::Color::Green);

    healthBar2.setSize(sf::Vector2f(200, 20));
    healthBar2.setPosition(700, 450);
    healthBar2.setFillColor(sf::Color::Green);

    healthBar3.setSize(sf::Vector2f(200, 20));
    healthBar3.setPosition(50, 50);
    healthBar3.setFillColor(sf::Color::Green);

    healthBar4.setSize(sf::Vector2f(200, 20));
    healthBar4.setPosition(700, 490);
    healthBar4.setFillColor(sf::Color::Green);

    // Store original positions for animations
    originalPos1 = pokemon1_sprite.getPosition();
    originalPos2 = pokemon2_sprite.getPosition();
    
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
    if (isAnimating) {
        float elapsed = animationClock.getElapsedTime().asSeconds();
        animationProgress = elapsed * 2; // 0.5 second animation
        
        if (animationProgress >= 1.0f) {
            // Reset positions
            pokemon1_sprite.setPosition(originalPos1);
            pokemon2_sprite.setPosition(originalPos2);
            isAnimating = false;
        } else {
            // Simple attack animation - pokemon moves forward then back
            if (isFirstPokemonAttaking) {
                float xOffset = sin(animationProgress * 3.14159f) * 50.0f;
                pokemon1_sprite.setPosition(originalPos1.x + xOffset, originalPos1.y);
            } else {
                float xOffset = sin(animationProgress * 3.14159f) * -50.0f;
                pokemon2_sprite.setPosition(originalPos2.x + xOffset, originalPos2.y);
            }
        }
    }
}

// Update the render function
void Window::render() {
    this->window->clear();
    
    // Update animations
    updateAnimations();
    
    // Draw arena
    if (!Arene_texture.loadFromFile("images/Background.jpg")) {
        std::cerr << "Erreur: Impossible de charger le fond." << std::endl;
    }
    Arene_sprite.setTexture(Arene_texture);
    this->window->draw(Arene_sprite);
    
    // Draw health bars
    this->window->draw(healthBarBackground1);
    this->window->draw(healthBarBackground2);
    this->window->draw(healthBar1);
    this->window->draw(healthBar2);
    this->window->draw(healthBar3);
    this->window->draw(healthBar4);

    
    // Draw Pokemon sprites
    this->window->draw(pokemon1_sprite);
    this->window->draw(pokemon2_sprite);
    this->window->draw(pokemon3_sprite);
    this->window->draw(pokemon4_sprite);
    
    // Draw move buttons
    for (const auto& button : moveButtons) {
        this->window->draw(button);
    }
    
    this->window->display();
}
void Window::handleinput() {
    // Test controls for animations
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        // 'A' key triggers first Pokemon's attack
        animateAttack(true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        // 'D' key triggers second Pokemon's attack
        animateAttack(true);
    }
    
    // Test controls for health bars
    /*static bool healthKeyPressed = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !healthKeyPressed) {
        // 'Q' key reduces first Pokemon's health by 10%
        static float health1 = 1.0f;
        health1 = std::max(0.0f, health1 - 0.1f);
        updateHealthBars(health1, 1.0f);
        healthKeyPressed = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !healthKeyPressed) {
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
}

void Window::processevent() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();
    }
}

/*void Window::updateMoveButton(Pokemon* pokemon) {
    if (pokemon) {
        for (size_t i = 0; i < pokemon->spes.size(); i++) {
            // Mettre à jour le texte et l'état des boutons de mouvement
        }
    }
}*/

/*void Window::handleinput() {
    // Gérer les clics de souris et les entrées clavier
}*/
