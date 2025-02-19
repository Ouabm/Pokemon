#include"Pokemon.hpp"




Pokemon::Pokemon(std::string nom, std::string type, int hp, int atk, int def, int vit, std::string texturePath){
    
     // Load texture once during construction
    if (!pokemon_texture.loadFromFile(texturePath)) {
        std::cout << "Error loading texture for " << nom << std::endl;
    }
    
    // Setup sprite with the loaded texture
    pokemon_sprite.setTexture(pokemon_texture);

}
sf::Texture& Pokemon::getTexture() {
    return pokemon_texture;
}
void Pokemon::initializeMoves() {
    if (nom == "Palkia") {
        spes.push_back(move("Spacial Rend", 100, 95, "Dragon"));
        spes.push_back(move("Hydro Pump", 110, 80, "Water"));
        spes.push_back(move("Dragon Claw", 80, 100, "Dragon"));
        spes.push_back(move("Aqua Tail", 90, 90, "Water"));
    }
    else if (nom == "Dialga") {
        spes.push_back(move("Roar of Time", 150, 90, "Dragon"));
        spes.push_back(move("Flash Cannon", 80, 100, "Steel"));
        spes.push_back(move("Dragon Breath", 60, 100, "Dragon"));
        spes.push_back(move("Metal Claw", 50, 95, "Steel"));
    }
    else if (nom == "Giratina") {
        spes.push_back(move("Shadow Force", 120, 90, "Ghost"));
        spes.push_back(move("Dragon Claw", 80, 100, "Dragon"));
        spes.push_back(move("Shadow Ball", 80, 100, "Ghost"));
        spes.push_back(move("Ancient Power", 60, 100, "Rock"));
    }
    else if (nom == "Arceus") {
        spes.push_back(move("Judgment", 100, 100, "Normal"));
        spes.push_back(move("Hyper Beam", 150, 90, "Normal"));
        spes.push_back(move("Cosmic Power", 0, 100, "Psychic"));
        spes.push_back(move("Recover", 0, 100, "Normal"));
    }
}