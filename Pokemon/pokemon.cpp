#include"Pokemon.hpp"

void Pokemon::initializeMoves() {
    // Initialize moves for each Pokemon
    if (nom == "Palkia") {
        
    std::cout << "Valeur de nom dans initializeMoves() : [" << nom << "]" << std::endl;

    
        std::cout << "Initialisation des attaques pour " << nom << std::endl;
        
        spes.push_back(move("Spacial Rend", 100, 95, "Dragon","attacks/Spacial-Rend.png"));
        std::cout << "Ajout : Spacial Rend, spes.size() = " << spes.size() << std::endl;

        spes.push_back(move("Hydro Pump", 110, 80, "Water","attacks/Hydro-Pump.png"));
        spes.push_back(move("Dragon Claw", 80, 100, "Dragon","attacks/Hydro-Pump.png"));
        spes.push_back(move("Aqua Tail", 90, 90, "Water","attacks/Hydro-Pump.png"));
        
    std::cout << "Nombre total d'attaques après ajout pour " << nom << " : " << spes.size() << std::endl;
    
}   //Dialga
    else if (nom == "Dialga") {
        spes.push_back(move("Roar of Time", 150, 90, "Dragon","attacks/Hydro-Pump.png"));
        spes.push_back(move("Flash Cannon", 80, 100, "Steel","attacks/Hydro-Pump.png"));
        spes.push_back(move("Dragon Breath", 60, 100, "Dragon","attacks/Hydro-Pump.png"));
        spes.push_back(move("Metal Claw", 50, 95, "Steel","attacks/Hydro-Pump.png"));
    }
    //Giratina
    else if (nom == "Giratina") {
        spes.push_back(move("Shadow Force", 120, 90, "Ghost","attacks/Hydro-Pump.png"));
        spes.push_back(move("Dragon Claw", 80, 100, "Dragon","attacks/Hydro-Pump.png"));
        spes.push_back(move("Shadow Ball", 80, 100, "Ghost","attacks/Hydro-Pump.png"));
        spes.push_back(move("Ancient Power", 60, 100, "Rock","attacks/Hydro-Pump.png"));
    }
    //Arceus 
    else if (nom == "Arceus") {
        spes.push_back(move("Judgment", 100, 100, "Normal","attacks/Hydro-Pump.png"));
        spes.push_back(move("Hyper Beam", 150, 90, "Normal","attacks/Hydro-Pump.png"));
        spes.push_back(move("Cosmic Power", 0, 100, "Psychic","attacks/Hydro-Pump.png"));
        spes.push_back(move("Recover", 0, 100, "Normal","attacks/Hydro-Pump.png"));
    }
    //Dracofeu
    else if (nom == "Dracaufeu") {
        spes.push_back(move("Judgment", 100, 100, "Normal","attacks/Hydro-Pump.png"));
        spes.push_back(move("Hyper Beam", 150, 90, "Normal","attacks/Hydro-Pump.png"));
        spes.push_back(move("Cosmic Power", 0, 100, "Psychic","attacks/Hydro-Pump.png"));
        spes.push_back(move("Recover", 0, 100, "Normal","attacks/Hydro-Pump.png"));
    }
    //Tortank
    else if (nom == "Tortank") {
        spes.push_back(move("Judgment", 100, 100, "Normal","attacks/Hydro-Pump.png"));
        spes.push_back(move("Hyper Beam", 150, 90, "Normal","attacks/Hydro-Pump.png"));
        spes.push_back(move("Cosmic Power", 0, 100, "Psychic","attacks/Hydro-Pump.png"));
        spes.push_back(move("Recover", 0, 100, "Normal","attacks/Hydro-Pump.png"));
    }
    //Pikachu 
    else if (nom == "Pikachu") {
        spes.push_back(move("Judgment", 100, 100, "Normal","attacks/Hydro-Pump.png"));
        spes.push_back(move("Hyper Beam", 150, 90, "Normal","attacks/Hydro-Pump.png"));
        spes.push_back(move("Cosmic Power", 0, 100, "Psychic","attacks/Hydro-Pump.png"));
        spes.push_back(move("Recover", 0, 100, "Normal","attacks/Hydro-Pump.png"));
    }
    else if (nom == "Mewtwo") {
        spes.push_back(move("Judgment", 100, 100, "Normal","attacks/Hydro-Pump.png"));
        spes.push_back(move("Hyper Beam", 150, 90, "Normal","attacks/Hydro-Pump.png"));
        spes.push_back(move("Cosmic Power", 0, 100, "Psychic","attacks/Hydro-Pump.png"));
        spes.push_back(move("Recover", 0, 100, "Normal","attacks/Hydro-Pump.png"));
    }
}