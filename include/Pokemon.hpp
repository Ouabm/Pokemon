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
    
    sf::Texture pokemon_texture_back;
    sf::Sprite pokemon_sprite_back;
    sf::Texture pokemon_texture_front;
    sf::Sprite pokemon_sprite_front;

public:
    // Constructeur par défaut (permet d'initialiser un Pokémon vide)
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


    virtual void initializeMoves() = 0;  // Fonction virtuelle pure pour l'héritage
    virtual ~Pokemon() {}
    void resetMoves();  
    sf::Texture frontTexture;
    std::vector<move*> spes;
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
        
    const std::vector<move*>& getMoves() const { return spes; }


    

};

class WaterPokemon : public Pokemon {
public:
    WaterPokemon(std::string n, int h, int atk, int def, int spd, std::string front, std::string back)
        : Pokemon(n, "Eau", h, atk, def, spd, front, back) {}

    void initializeMoves() override {
        spes.push_back(new move("Hydro Pump", 110, 80, "Water", "assets/attacks/Hydro-Pump.png"));
        spes.push_back(new move("Aqua Tail", 90, 90, "Water", "assets/attacks/Waterfall.png"));
        spes.push_back(new move("Ice Beam", 90, 100, "Ice", "assets/attacks/Surf-Transparent.png"));
        spes.push_back(new move("Calm Mind", 0, 100, "Psychic", "assets/attacks/Psychic.png"));

    }
};

class FirePokemon : public Pokemon {
public:
    FirePokemon(std::string n, int h, int atk, int def, int spd, std::string front, std::string back)
        : Pokemon(n, "Feu", h, atk, def, spd, front, back) {}

    void initializeMoves() override {
        spes.push_back(new move("Flamethrower", 90, 100, "Fire", "assets/attacks/Fire-Punch.png"));
        spes.push_back(new move("Dragon Claw", 80, 100, "Dragon", "assets/attacks/Dragon-Claw.png"));
        spes.push_back(new move("Air Slash", 75, 95, "Flying", "assets/attacks/Iron-Head.png"));
        spes.push_back(new move("Solar Beam", 120, 100, "Grass", "assets/attacks/Cut.png"));
    }
};

class PsyPokemon : public Pokemon {
public:
    PsyPokemon(std::string n, int h, int atk, int def, int spd, std::string front, std::string back)
        : Pokemon(n, "Psy", h, atk, def, spd, front, back) {}

    void initializeMoves() override {
        spes.push_back(new move("Psystrike", 100, 100, "Psychic", "assets/attacks/Psystrike.png"));
        spes.push_back(new move("Shadow Ball", 80, 100, "Ghost", "assets/attacks/Shadow-Ball.png"));
        spes.push_back(new move("Aura Sphere", 80, 100, "Fighting", "assets/attacks/Ancient-Power.png"));
        spes.push_back(new move("Giga-impact",70 , 100, "Fighting", "assets/attacks/Giga-Impact.png"));
    }
};

class electriquePokemon : public Pokemon {
public:
    electriquePokemon(std::string n, int h, int atk, int def, int spd, std::string front, std::string back)
        : Pokemon(n, "electrique", h, atk, def, spd, front, back) {}

    void initializeMoves() override {
        spes.push_back(new move("Thunderbolt", 90, 100, "Electric", "assets/attacks/Flash-Cannon.png"));
        spes.push_back(new move("Drill Peck", 80, 100, "Flying", "assets/attacks/Iron-Head.png"));
        spes.push_back(new move("Heat Wave", 95, 90, "Fire", "assets/attacks/Blast-Burn.png"));
        spes.push_back(new move("Roost", 0, 100, "Flying", "assets/attacks/Iron-Head.png"));
    }
};

class SpectrePokemon : public Pokemon {
public:
    SpectrePokemon(std::string n, int h, int atk, int def, int spd, std::string front, std::string back)
        : Pokemon(n, "Spectre", h, atk, def, spd, front, back) {}

    void initializeMoves() override {
        spes.push_back(new move("Shadow Force", 120, 90, "Ghost","assets/attacks/Shadow-Force.png"));
        spes.push_back(new move("Dragon Claw", 80, 100, "Dragon","assets/attacks/Dragon-Claw.png"));
        spes.push_back(new move("Shadow Ball", 80, 100, "Ghost","assets/attacks/image.png"));
        spes.push_back(new move("Ancient Power", 60, 100, "Rock","assets/attacks/Ancient-Power.png"));
    }
};

class WaterDragonPokemon : public Pokemon {
public:
    WaterDragonPokemon(std::string n, int h, int atk, int def, int spd, std::string front, std::string back)
        : Pokemon(n, "Water", h, atk, def, spd, front, back) {}

    void initializeMoves() override {
        spes.push_back(new move("Spacial Rend", 100, 95, "Dragon","assets/attacks/Spacial-Rend.png"));
        std::cout << "Ajout : Spacial Rend, spes.size() = " << spes.size() << std::endl;

        spes.push_back(new move("Hydro Pump", 110, 80, "Water","assets/attacks/Hydro-Pump.png"));
        spes.push_back(new move("Dragon Claw", 80, 100, "Dragon","assets/attacks/Dragon-Claw.png"));
        spes.push_back(new move("Aqua Tail", 90, 90, "Water","assets/attacks/Waterfall.png"));
    }
};

class FireDragonPokemon : public Pokemon {
public:
    FireDragonPokemon(std::string n, int h, int atk, int def, int spd, std::string front, std::string back)
        : Pokemon(n, "Feu", h, atk, def, spd, front, back) {}

    void initializeMoves() override {
        spes.push_back(new move("Blue Flare", 130, 85, "Fire", "assets/attacks/Sacred-Fire.png"));
        spes.push_back(new move("Dragon Claw", 85, 100, "Dragon", "assets/attacks/Dragon-Claw.png"));
        spes.push_back(new move("Fusion Flare", 100, 100, "Fire", "assets/attacks/Fire-Blast.png"));
        spes.push_back(new move("Srone Edge", 100, 80, "Rock", "assets/attacks/Ancient-Power.png"));
    }
};

class electriqueDragonPokemon : public Pokemon {
public:
    electriqueDragonPokemon(std::string n, int h, int atk, int def, int spd, std::string front, std::string back)
        : Pokemon(n, "electrique", h, atk, def, spd, front, back) {}

    void initializeMoves() override {
        spes.push_back(new move("Bolt Strike", 130, 85, "Electric", "assets/attacks/Flash-Cannon.png"));
        spes.push_back(new move("Dragon Claw", 80, 100, "Dragon", "assets/attacks/Dragon-Claw.png"));
        spes.push_back(new move("Fusion Bolt", 100, 100, "Electric", "assets/attacks/Flash-Cannon.png"));
        spes.push_back(new move("Srone Edge", 100, 80, "Rock", "assets/attacks/Ancient-Power.png"));
    }
};

class SteelPokemon : public Pokemon {
public:
    SteelPokemon(std::string n, int h, int atk, int def, int spd, std::string front, std::string back)
        : Pokemon(n, "Steel", h, atk, def, spd, front, back) {}

    void initializeMoves() override {
        spes.push_back(new move("Roar of Time", 150, 90, "Dragon","assets/attacks/Sacred-Fire.png"));
        spes.push_back(new move("Flash Cannon", 80, 100, "Steel","assets/attacks/Flash-Cannon.png"));
        spes.push_back(new move("Dragon Breath", 60, 100, "Dragon","assets/attacks/Energy-Ball.png"));
        spes.push_back(new move("Metal Claw", 50, 95, "Steel","assets/attacks/Mud-Sport.png"));
    }
};

class Arceus : public Pokemon {
public:
    Arceus(std::string n, int h, int atk, int def, int spd, std::string front, std::string back)
        : Pokemon(n, "Normal", h, atk, def, spd, front, back) {}

    void initializeMoves() override {
        spes.push_back(new move("Judgment", 100, 100, "Normal","assets/attacks/Fissure.png"));
        spes.push_back(new move("Hyper Beam", 150, 90, "Normal","assets/attacks/Giga-impact.png"));
        spes.push_back(new move("Cosmic Power", 100, 100, "Psychic","assets/attacks/.png"));
        spes.push_back(new move("LeafStorm", 100, 100, "Normal","assets/attacks/Leaf-Storm.png"));
    }
};

class DragonPokemon : public Pokemon {
public:
    DragonPokemon(std::string n, int h, int atk, int def, int spd, std::string front, std::string back)
        : Pokemon(n, "Normal", h, atk, def, spd, front, back) {}

    void initializeMoves() override {
        spes.push_back(new move("Dragon Ascent", 120, 100, "Flying", "assets/attacks/Iron-Head.png"));
        spes.push_back(new move("Dragon Claw", 80, 100, "Dragon", "assets/attacks/Dragon-Claw.png"));
        spes.push_back(new move("Extreme Speed", 80, 100, "Normal", "assets/attacks/Extreme-Speed.png"));
        spes.push_back(new move("Hyper Beam", 150, 90, "Normal", "assets/attacks/Hyper-Beam.png"));
    }
};

class EarthPokemon : public Pokemon {
public:
    EarthPokemon(std::string n, int h, int atk, int def, int spd, std::string front, std::string back)
        : Pokemon(n, "Normal", h, atk, def, spd, front, back) {}

    void initializeMoves() override {
        spes.push_back(new move("Precipice Blades", 120, 85, "Ground", "assets/attacks/Rock-Tomb.png"));
        spes.push_back(new move("Fire Punch", 75, 100, "Fire", "assets/attacks/Fire-Punch.png"));
        spes.push_back(new move("Stone Edge", 100, 80, "Rock", "assets/attacks/Ancient-Power.png"));
        spes.push_back(new move("Solar Beam", 120, 100, "Grass", "assets/attacks/Cut.png"));
    }
};



#endif
