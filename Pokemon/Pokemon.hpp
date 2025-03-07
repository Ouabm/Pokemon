#ifndef POKEMON_HPP
#define POKEMON_HPP

#include <string>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "move.hpp"

class Pokemon {
private:
    std::string nom;
    std::string type;
    int hp;
    int hprestant;
    int atk;
    int def;
    int vit;
    std::vector<move> spes;
    sf::Texture pokemon_texture_back;
    sf::Sprite pokemon_sprite_back;
    sf::Texture pokemon_texture_front;
    sf::Sprite pokemon_sprite_front;

public:
    // sConstructeur par défaut (permet d'initialiser un Pokémon vide)
    Pokemon() : nom(""), type(""), hp(0), hprestant(0), atk(0), def(0), vit(0) {}

    // Constructeur avec paramètres (CORRIGÉ)
    Pokemon(const std::string& nom, const std::string& type, int hp, int atk, int def, int vit, const std::string& texturePathfront , const std::string& texturePathback)
        : nom(nom), type(type), hp(hp), hprestant(hp), atk(atk), def(def), vit(vit){
        if (!pokemon_texture_back.loadFromFile(texturePathback)) {
            std::cerr << "Erreur : Impossible de charger l'image " << texturePathback << std::endl;
        }
        pokemon_sprite_back.setTexture(pokemon_texture_back);

        if (!pokemon_texture_front.loadFromFile(texturePathfront)) {
            std::cerr << "Erreur : Impossible de charger l'image " << texturePathfront << std::endl;
        }
        pokemon_sprite_front.setTexture(pokemon_texture_front);


    }


    sf::Texture frontTexture;
    sf::Texture backTexture;
    // Getters
    const std::string& getName() const { return nom; }
    int getHp() const { return hp; }
    int getHpRestant() const { return hprestant; }
    int getAtk() const { return atk; }
    int getDef() const { return def; }
    int getVit() const { return vit; }
    const std::string& getType() const { return type; }
    const sf::Sprite& getSprite_back() const { return pokemon_sprite_back; }
    const sf::Sprite& getSprite_front() const { return pokemon_sprite_front; }

    // Setters
    void setHpRestant(int newHp) { hprestant = newHp; }

    // Méthodes de combat
    void takeDamage(int damage) { hprestant = std::max(0, hprestant - damage); }
    bool isDead() const { return hprestant <= 0; }

    // Gestion des attaques
    void addMove(const move& newMove) { if (spes.size() < 4) spes.push_back(newMove); }

    void initializeMoves();

    void loadTextures(const std::string& frontTexturePath, const std::string& backTexturePath) {
        if (!frontTexture.loadFromFile(frontTexturePath)) {
            std::cerr << "Error: Unable to load front texture for " << nom << std::endl;
        }
        if (!backTexture.loadFromFile(backTexturePath)) {
            std::cerr << "Error: Unable to load back texture for " << nom << std::endl;
        }
    }
    sf::Texture& getTexturefront() {
        return pokemon_texture_front;
    }
    sf::Texture& getTextureback() {
        return pokemon_texture_back;
        }
        
    const std::vector<move>& getMoves() const { return spes; }

};

#endif
