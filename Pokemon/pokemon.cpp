#include"Pokemon.hpp"



void Pokemon::initializeMoves() {
    // Initialize moves for each Pokemon
    if (nom == "Palkia") {
        
    std::cout << "Valeur de nom dans initializeMoves() : [" << nom << "]" << std::endl;

    
        std::cout << "Initialisation des attaques pour " << nom << std::endl;
        
        spes.push_back(move("Spacial Rend", 100, 95, "Dragon","attacks/Spacial-Rend.png"));
        std::cout << "Ajout : Spacial Rend, spes.size() = " << spes.size() << std::endl;

        spes.push_back(move("Hydro Pump", 110, 80, "Water","attacks/Hydro-Pump.png"));
        spes.push_back(move("Dragon Claw", 80, 100, "Dragon","attacks/Dragon-Claw.png"));
        spes.push_back(move("Aqua Tail", 90, 90, "Water","attacks/Waterfall.png"));
        
    std::cout << "Nombre total d'attaques après ajout pour " << nom << " : " << spes.size() << std::endl;
    
}   //Dialga
    else if (nom == "Dialga") {
        spes.push_back(move("Roar of Time", 150, 90, "Dragon","attacks/Sacred-Fire.png"));
        spes.push_back(move("Flash Cannon", 80, 100, "Steel","attacks/Flash-Cannon.png"));
        spes.push_back(move("Dragon Breath", 60, 100, "Dragon","attacks/Energy-Ball.png"));
        spes.push_back(move("Metal Claw", 50, 95, "Steel","attacks/Mud-Sport.png"));
    }
    //Giratina
    else if (nom == "Giratina") {
        spes.push_back(move("Shadow Force", 120, 90, "Ghost","attacks/Shadow-Force.png"));
        spes.push_back(move("Dragon Claw", 80, 100, "Dragon","attacks/Dragon-Claw.png"));
        spes.push_back(move("Shadow Ball", 80, 100, "Ghost","attacks/image.png"));
        spes.push_back(move("Ancient Power", 60, 100, "Rock","attacks/Ancient-Power.png"));
    }
    //Arceus 
    else if (nom == "Arceus") {
        spes.push_back(move("Judgment", 100, 100, "Normal","attacks/Hydro-Pump.png"));
        spes.push_back(move("Hyper Beam", 150, 90, "Normal","attacks/Hydro-Pump.png"));
        spes.push_back(move("Cosmic Power", 0, 100, "Psychic","attacks/Hydro-Pump.png"));
        spes.push_back(move("Recover", 0, 100, "Normal","attacks/Hydro-Pump.png"));
    }
    //Dracofeu
    else if (nom == "Charizard") {
        spes.push_back(move("fire", 100, 100, "Normal","attacks/Fire.png"));
        spes.push_back(move("Hyper Beam", 150, 90, "Normal","attacks/Hydro-Pump.png"));
        spes.push_back(move("Cosmic Power", 0, 100, "Psychic","attacks/Hydro-Pump.png"));
        spes.push_back(move("Recover", 0, 100, "Normal","attacks/Hydro-Pump.png"));
    }
    else if (nom == "Mewtwo") {
        spes.push_back(move("Psystrike", 140, 100, "Psychic","attacks/Psychic.png"));
        spes.push_back(move("Shadow Ball", 80, 100, "Ghost","attacks/Shadow-Ball.png"));
        spes.push_back(move("Hyper Beam", 150, 90, "Normal","attacks/Hyper-Beam.png"));
        spes.push_back(move("Recover", 0, 100, "Normal","attacks/Recover.png"));
    }
    else if (nom == "Reshiram") {
        spes.push_back(move("Dragon Ascent", 120, 100, "Dragon",
        "attacks/Dragon-Ascent.png"));
        spes.push_back(move("Fire Blast", 120, 100, "Fire","attacks/Fire-Blast.png"));
        spes.push_back(move("Hyper Beam", 150, 90, "Normal","attacks/Hyper-Beam.png"));
        spes.push_back(move("Recover", 0, 100, "Normal","attacks/Recover.png"));
        }
    else if(nom=="Zekrom"){
        spes.push_back(move("Dragon Ascent", 120, 100, "Dragon","attacks/Dragon-Ascent.png"));
        spes.push_back(move("Thunderbolt", 120, 100, "Electric","attacks/Thunderbolt.png"));
        spes.push_back(move("Hyper Beam", 150, 90, "Normal","attacks/Hyper-Beam.png"));
        spes.push_back(move("Recover", 0, 100, "Normal","attacks/Recover.png"));
        }
    else if(nom=="Rayquaza"){
        spes.push_back(move("Dragon Ascent", 120, 100, "Dragon","attacks/Dragon-Ascent.png"));
        spes.push_back(move("Hyper Beam", 150, 90, "Normal","attacks/Hyper-Beam.png"));
        spes.push_back(move("Recover", 0, 100, "Normal","attacks/Recover.png"));
        spes.push_back(move("Outrage", 120, 100, "Dragon","attacks/Outrage.png"));
        }
    else if(nom=="Lugia"){
        spes.push_back(move("Aeroblast", 120, 100, "Flying","attacks/Aeroblast.png"));
        spes.push_back(move("Hyper Beam", 150, 90, "Normal","attacks/Hyper-Beam.png"));
        spes.push_back(move("Recover", 0, 100, "Normal","attacks/Recover.png"));
        spes.push_back(move("Aurora Beam", 120, 100, "Icing","attacks/Aurora-Beam.png"));
        
    }
    else if (nom=="Pikachu"){
        spes.push_back(move("Thunderbolt", 120, 100, "Electric","attacks/Thunderbolt.png"));
        spes.push_back(move("Hyper Beam", 150, 90, "Normal","attacks/Hyper-Beam.png"));
        spes.push_back(move("Recover", 0, 100, "Normal","attacks/Recover.png"));
        spes.push_back(move("Quick Attack", 120, 100, "Normal","attacks/Quick-Attack.png"));
    
    }

    
    

    
}

// void Pokemon::startDamageAnimation() {
//         isDamageAnimating = true;
//         damageAnimationTimer = 0.0f;
//         originalColor = pokemon_sprite.getColor();
//         originalPosition = pokemon_sprite.getPosition();
//         damageAnimClock.restart();
//     }

// void Pokemon::updateDamageAnimation() {
//         if (!isDamageAnimating) return;

//         float elapsed = damageAnimClock.getElapsedTime().asSeconds();
        
//         // Flash red and shake for 0.6 seconds
//         if (elapsed < DAMAGE_ANIMATION_DURATION) {
//             // Flash between red and normal color
//             float flashSpeed = 8.0f; // Adjust for faster/slower flashing
//             bool shouldBeRed = static_cast<int>(elapsed * flashSpeed) % 2 == 0;
            
//             if (shouldBeRed) {
//                 pokemon_sprite.setColor(sf::Color(255, 100, 100, 255)); // Red tint
//             } else {
//                 pokemon_sprite.setColor(originalColor);
//             }
            
//             // Shake effect
//             float shakeAmount = 5.0f; // Adjust for more/less shake
//             float shakeX = originalPosition.x + (std::rand() % static_cast<int>(shakeAmount * 2) - shakeAmount);
//             float shakeY = originalPosition.y + (std::rand() % static_cast<int>(shakeAmount * 2) - shakeAmount);
//             pokemon_sprite.setPosition(shakeX, shakeY);
//         } else {
//             // Reset everything when animation is done
//             isDamageAnimating = false;
//             pokemon_sprite.setColor(originalColor);
//             pokemon_sprite.setPosition(originalPosition);
//         }
//     }