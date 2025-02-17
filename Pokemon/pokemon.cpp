#include"Pokemon.hpp"



Pokemon::Pokemon(std::string nom, std::string type, int hp, int atk, int def, int vit, std::string texturePath){
    // Chargement de la texture à partir du fichier spécifié par texturePath
    if (!pokemon_texture.loadFromFile(texturePath)) {
        std::cout << "Erreur de chargement de la texture pour " << nom << std::endl;
    }

}

void Pokemon::init_pokemon(){
    this->nom="Palkia";
    this->hp=100;
    this->atk=100;
    this->def=100;
    this->type="Dragon";
    this->vit=100;
    

}