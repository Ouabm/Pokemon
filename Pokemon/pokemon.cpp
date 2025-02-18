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