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


class Pokemon {
    private:
    std::string nom;
    int hp;
    int hprestant;
    int def;
    std::string type;
    int atk; 
    int vit;
    //std::vector<move> spes ;
    sf::Texture pokemon_texture;
    sf::Sprite pokemon_sprite;
    void init_pokemon();
    
    public:
    Pokemon(std::string nom, std::string type, int hp, int atk, int def, int vit, std::string texturePath);
    //void rajoutspe(move spe){}
    bool mort()const{
        return hprestant<=0;
    }
    sf::Texture& getTexture() {
        if (!pokemon_texture.loadFromFile("Palkia.png")) {
                std::cout << "Error loading texture for " << nom << std::endl;
            }
        
        return pokemon_texture;
    
    }
};

#endif