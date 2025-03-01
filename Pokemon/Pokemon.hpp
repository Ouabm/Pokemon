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
    sf::Texture pokemon_texture;
    sf::Sprite pokemon_sprite;

public:
    // ✅ Constructeur par défaut (permet d'initialiser un Pokémon vide)
    Pokemon() : nom(""), type(""), hp(0), hprestant(0), atk(0), def(0), vit(0) {}

    // ✅ Constructeur avec paramètres (CORRIGÉ)
    Pokemon(const std::string& nom, const std::string& type, int hp, int atk, int def, int vit, const std::string& texturePath)
        : nom(nom), type(type), hp(hp), hprestant(hp), atk(atk), def(def), vit(vit) {
        if (!pokemon_texture.loadFromFile(texturePath)) {
            std::cerr << "Erreur : Impossible de charger l'image " << texturePath << std::endl;
        }
        pokemon_sprite.setTexture(pokemon_texture);
    }

    // ✅ Méthode pour charger un Pokémon après son instanciation
    void loadFromData(const std::string& nom, const std::string& type, int hp, int atk, int def, int vit, const std::string& texturePath) {
        this->nom = nom;
        this->type = type;
        this->hp = hp;
        this->hprestant = hp;
        this->atk = atk;
        this->def = def;
        this->vit = vit;

        if (!pokemon_texture.loadFromFile(texturePath)) {
            std::cerr << "Erreur : Impossible de charger l'image " << texturePath << std::endl;
        }
        pokemon_sprite.setTexture(pokemon_texture);
    }

    // Getters
    const std::string& getName() const { return nom; }
    int getHp() const { return hp; }
    int getHpRestant() const { return hprestant; }
    int getAtk() const { return atk; }
    int getDef() const { return def; }
    int getVit() const { return vit; }
    const std::string& getType() const { return type; }
    const sf::Sprite& getSprite() const { return pokemon_sprite; }

    // Setters
    void setHpRestant(int newHp) { hprestant = newHp; }

    // Méthodes de combat
    void takeDamage(int damage) { hprestant = std::max(0, hprestant - damage); }
    bool isDead() const { return hprestant <= 0; }

    // Gestion des attaques
    void addMove(const move& newMove) { if (spes.size() < 4) spes.push_back(newMove); }

    void initializeMoves();
    sf::Texture& getTexture() { return pokemon_texture; }
   
    const std::vector<move>& getMoves() const { return spes; }

};

#endif
