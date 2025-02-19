#ifndef POKEMON_HPP
#define POKEMON_HPP
#include<string>
#include <iostream>
#include<vector>
#include<ctime>
#include<sstream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include"move.hpp"



class Pokemon {
private:
    std::string nom;
    int hp;
    int hprestant;
    int def;
    std::string type;
    int atk; 
    int vit;
    std::vector<move> spes;
    sf::Texture pokemon_texture;
    sf::Sprite pokemon_sprite;
     sf::IntRect frameRect;      // Rectangle defining current frame
    int currentFrame;           // Current frame index
    float animationTimer;       // Timer for animation
    float frameDuration;        // Duration of each frame
    int frameCount;             // Total number of frames
    bool isAnimating;           // Animation state
    sf::Clock animClock;     
   

public:
    Pokemon(std::string nom, std::string type, int hp, int atk, int def, int vit, std::string texturePath);
    
    // Getters
    std::string getNom() const { return nom; }
    int getHp() const { return hp; }
    int getHpRestant() const { return hprestant; }
    int getDef() const { return def; }
    std::string getType() const { return type; }
    int getAtk() const { return atk; }
    int getVit() const { return vit; }
    const std::vector<move>& getMoves() const { return spes; }
    
    // Setters
    void setHpRestant(int newHp) { hprestant = newHp; }
    
    // Battle methods
    void takeDamage(int damage) {
        hprestant = std::max(0, hprestant - damage);
    }
    
    void addMove(const move& newMove) {
        if (spes.size() < 4) {
            spes.push_back(newMove);
        }
    }
    
    bool isDead() const { return hprestant <= 0; }
    
    sf::Texture& getTexture();
    const sf::Sprite& getSprite() const { return pokemon_sprite; }
    void initializeMoves();
};

#endif