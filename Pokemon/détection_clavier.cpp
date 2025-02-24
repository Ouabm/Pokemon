#include "détection_clavier.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

void select_which_pokemon_to_attack(sf::RenderWindow &window){
    sf::RectangleShape squares[2];
    for (int i = 0; i < 2; i++) {
        squares[i].setSize(sf::Vector2f(100, 100));
        squares[i].setFillColor(sf::Color::White); // Couleur normale
        squares[i].setPosition(100 +150*i,100); // Position espacée
    }
    int selectedIndex = 0; // Index du carré sélectionné
    squares[selectedIndex].setOutlineThickness(5);
    squares[selectedIndex].setOutlineColor(sf::Color::Red); // Le premier est sélectionné

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                // Réinitialise la couleur du carré actuel
                squares[selectedIndex].setOutlineThickness(5);
                squares[selectedIndex].setOutlineColor(sf::Color::White);

                if (event.key.code == sf::Keyboard::Right) {
                    if(selectedIndex%2==0){
                        selectedIndex = (selectedIndex + 1) % 2; // Aller à droite
                    }
                } 
                else if (event.key.code == sf::Keyboard::Left) {
                    if(selectedIndex%2==1){
                        selectedIndex = (selectedIndex - 1 + 4) % 2; // Aller à gauche
                    }
                }
                else if (event.key.code == sf::Keyboard::Enter){
                    if (selectedIndex==0){
                        //attack le pokemon de gauche 
                    }
                    if (selectedIndex==1){
                        //attack le pokemon de droite
                    }
                }
                else if (event.key.code == sf::Keyboard::BackSpace){
                    select_attack(window);
                }

                // Met en évidence le carré sélectionné
                squares[selectedIndex].setOutlineThickness(5);
                squares[selectedIndex].setOutlineColor(sf::Color::Red);
            }
        }

        window.clear();
        for (const auto& square : squares) {
            window.draw(square);
        }
        window.display();
    }
    
}
void select_switch(sf::RenderWindow &window){
    sf::RectangleShape squares[3];
    for (int i = 0; i < 3; i++) {
        squares[i].setSize(sf::Vector2f(100, 100));
        squares[i].setFillColor(sf::Color::White); // Couleur normale
        squares[i].setPosition(100 ,100+i*150); // Position espacée
    }
    int selectedIndex = 0; // Index du carré sélectionné
    squares[selectedIndex].setOutlineThickness(5);
    squares[selectedIndex].setOutlineColor(sf::Color::Red); // Le premier est sélectionné

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                // Réinitialise la couleur du carré actuel
                squares[selectedIndex].setOutlineThickness(5);
                squares[selectedIndex].setOutlineColor(sf::Color::White);

                if (event.key.code == sf::Keyboard::Down) {
                    if(selectedIndex!=2){
                        selectedIndex = (selectedIndex + 1) % 3; // Aller à droite
                    }
                } 
                else if (event.key.code == sf::Keyboard::Up) {
                    if(selectedIndex!=0){
                        selectedIndex = (selectedIndex - 1 + 3) % 3; // Aller à gauche
                    }
                }
                else if (event.key.code == sf::Keyboard::Enter){
                    if (selectedIndex==0){
                        //print un message disant que ce pokemon et deja actif;
                    }
                    if (selectedIndex==1){
                        //echange la position du pokemon 1 et 2;
                    }
                    if (selectedIndex==2){
                        //echange la position du pokemon 1 et 3;
                    }
                }
                else if (event.key.code == sf::Keyboard::BackSpace){
                    select_switch_or_attack(window);
                }
                // Met en évidence le carré sélectionné
                squares[selectedIndex].setOutlineThickness(5);
                squares[selectedIndex].setOutlineColor(sf::Color::Red);
            }
        }

        window.clear();
        for (const auto& square : squares) {
            window.draw(square);
        }
        window.display();
    }
}
void select_attack(sf::RenderWindow &window){
    sf::RectangleShape squares[4];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            squares[2*i+j].setSize(sf::Vector2f(100, 100));
            squares[2*i+j].setFillColor(sf::Color::White); // Couleur normale
            squares[2*i+j].setPosition(150 * j + 100, 150*i + 100); // Position espacée
        }
    }
    int attaque_move;
    int selectedIndex = 0; // Index du carré sélectionné
    squares[selectedIndex].setOutlineThickness(5);
    squares[selectedIndex].setOutlineColor(sf::Color::Red); // Le premier est sélectionné

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                // Réinitialise la couleur du carré actuel
                squares[selectedIndex].setOutlineThickness(5);
                squares[selectedIndex].setOutlineColor(sf::Color::White);

                if (event.key.code == sf::Keyboard::Right) {
                    if(selectedIndex%2==0){
                        selectedIndex = (selectedIndex + 1) % 4; // Aller à droite
                    }
                } 
                else if (event.key.code == sf::Keyboard::Left) {
                    if(selectedIndex%2==1){
                        selectedIndex = (selectedIndex - 1 + 4) % 4; // Aller à gauche
                    }
                }
                else if (event.key.code == sf::Keyboard::Up) {
                    if(selectedIndex>1){
                        selectedIndex = (selectedIndex - 2 + 4) % 4; // Aller à gauche
                    }
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    if(selectedIndex<=1){
                        selectedIndex = (selectedIndex + 2 ) % 4; // Aller à gauche
                    }
                }
                else if (event.key.code == sf::Keyboard::Enter){
                    attaque_move=selectedIndex;
                    select_which_pokemon_to_attack(window);
                }
                else if (event.key.code == sf::Keyboard::BackSpace){
                    select_switch_or_attack(window);
                }

                // Met en évidence le carré sélectionné
                squares[selectedIndex].setOutlineThickness(5);
                squares[selectedIndex].setOutlineColor(sf::Color::Red);
            }
        }

        window.clear();
        for (const auto& square : squares) {
            window.draw(square);
        }
        window.display();
    }
}

void select_switch_or_attack(sf::RenderWindow &window){

    // Création de 2 carrés
    sf::RectangleShape squares[2];
    for (int i = 0; i < 2; i++) {
        squares[i].setSize(sf::Vector2f(100, 100));
        squares[i].setFillColor(sf::Color::White); // Couleur normale
        squares[i].setPosition(100 +150*i,100); // Position espacée
    }
    int selectedIndex = 0; // Index du carré sélectionné
    squares[selectedIndex].setOutlineThickness(5);
    squares[selectedIndex].setOutlineColor(sf::Color::Red); // Le premier est sélectionné

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                // Réinitialise la couleur du carré actuel
                squares[selectedIndex].setOutlineThickness(5);
                squares[selectedIndex].setOutlineColor(sf::Color::White);

                if (event.key.code == sf::Keyboard::Right) {
                    if(selectedIndex%2==0){
                        selectedIndex = (selectedIndex + 1) % 2; // Aller à droite
                    }
                } 
                else if (event.key.code == sf::Keyboard::Left) {
                    if(selectedIndex%2==1){
                        selectedIndex = (selectedIndex - 1 + 4) % 2; // Aller à gauche
                    }
                }
                else if (event.key.code == sf::Keyboard::Enter){
                    if (selectedIndex==0){
                        select_attack(window);
                    }
                    if (selectedIndex==1){
                        select_switch(window);
                    }
                }
                // Met en évidence le carré sélectionné
                squares[selectedIndex].setOutlineThickness(5);
                squares[selectedIndex].setOutlineColor(sf::Color::Red);
            }
        }

        window.clear();
        for (const auto& square : squares) {
            window.draw(square);
        }
        window.display();
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sélection de carré");
    select_switch_or_attack(window);

    return 0;
}