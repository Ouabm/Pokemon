#include "Graphique.hpp"
#include "Pokemon.hpp"


Window::Window(): pokemon1("Palkia", "Eau", 100, 100, 100, 100, "Palkia.png"),
    pokemon2("Dialga", "Acier", 100, 100, 100, 100, "dialga.png"){
    // Initialisation de la fenêtre
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Combat Pokémon");
    
    
    // Initialisation des éléments de l'interface graphique
    this->init_pokemon_positon();
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
    pokemon2_sprite.setTexture(pokemon2.getTexture());  // Pokémon 2 (Droite)

    pokemon1_sprite.setPosition(100, 300); // Position du Pokémon 1 (Gauche)
    pokemon2_sprite.setPosition(500, 300); // Position du Pokémon 2 (Droite)
}

void Window::setupUI() {
    infoJ1.setSize(sf::Vector2f(300, 100));
    infoJ1.setPosition(50, 350);
    infoJ1.setFillColor(sf::Color(255, 255, 255, 200));

    infoJ2.setSize(sf::Vector2f(300, 100));
    infoJ2.setPosition(450, 50);
    infoJ2.setFillColor(sf::Color(255, 255, 255, 200));

    // Initialiser les boutons de mouvement
    for (int i = 0; i < 4; i++) {
        moveButtons[i].setSize(sf::Vector2f(190, 50));
        moveButtons[i].setPosition(50 + (i % 2) * 200, 480 + (i / 2) * 60);
        moveButtons[i].setFillColor(sf::Color(200, 200, 200));
    }
}

void Window::render() {
    this->window->clear();

    // Dessiner l'arène
    sf::RectangleShape Arene;
    Arene.setSize(sf::Vector2f(700, 300));
    Arene.setPosition(50, 100);
    Arene.setFillColor(sf::Color(100, 200, 100)); // Arène verte
    this->window->draw(Arene);

    // Dessiner les informations des joueurs
    this->window->draw(infoJ1);
    this->window->draw(infoJ2);

    // Dessiner les sprites des Pokémon
    this->window->draw(pokemon1_sprite);
    this->window->draw(pokemon2_sprite);

    // Dessiner les boutons de mouvement
    for (const auto& button : moveButtons) {
        this->window->draw(button);
    }

    this->window->display(); // Afficher tout sur la fenêtre
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
