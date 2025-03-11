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
     // Charizard
    else if (nom == "Charizard") {
        spes.push_back(move("Flamethrower", 90, 100, "Fire", "attacks/Fire-Punch.png"));
        spes.push_back(move("Dragon Claw", 80, 100, "Dragon", "attacks/Dragon-Claw.png"));
        spes.push_back(move("Air Slash", 75, 95, "Flying", "attacks/Aerial-Ace.png"));
        spes.push_back(move("Solar Beam", 120, 100, "Grass", "attacks/Cut.png"));
    }
    // Mewtwo
    else if (nom == "Mewtwo") {
        spes.push_back(move("Psystrike", 100, 100, "Psychic", "attacks/Psystrike.png"));
        spes.push_back(move("Shadow Ball", 80, 100, "Ghost", "attacks/Shadow-Ball.png"));
        spes.push_back(move("Aura Sphere", 80, 100, "Fighting", "attacks/Ancient-Power.png"));
        spes.push_back(move("Giga-impact",70 , 100, "Fighting", "attacks/Giga-Impact.png"));
    }
    // Reshiram
    else if (nom == "Reshiram") {
        spes.push_back(move("Blue Flare", 130, 85, "Fire", "attacks/Sacred-Fire.png"));
        spes.push_back(move("Dragon Claw", 85, 100, "Dragon", "attacks/Dragon-Claw.png"));
        spes.push_back(move("Fusion Flare", 100, 100, "Fire", "attacks/Fire-Punch.png"));
        spes.push_back(move("Srone Edge", 100, 80, "Rock", "attacks/Srone-Edge.png"));
    }
    // Zekrom
    else if (nom == "Zekrom") {
        spes.push_back(move("Bolt Strike", 130, 85, "Electric", "attacks/Cut.png"));
        spes.push_back(move("Dragon Claw", 80, 100, "Dragon", "attacks/Dragon-Claw.png"));
        spes.push_back(move("Fusion Bolt", 100, 100, "Electric", "attacks/Speed-Attack-Back.png"));
        spes.push_back(move("Srone Edge", 100, 80, "Rock", "attacks/Srone-Edge.png"));
    }
    // Rayquaza
    else if (nom == "Rayquaza") {
        spes.push_back(move("Dragon Ascent", 120, 100, "Flying", "attacks/Dragon-Ascent.png"));
        spes.push_back(move("Dragon Claw", 80, 100, "Dragon", "attacks/Dragon-Claw.png"));
        spes.push_back(move("Extreme Speed", 80, 100, "Normal", "attacks/Extreme-Speed.png"));
        spes.push_back(move("Hyper Beam", 150, 90, "Normal", "attacks/Hyper-Beam.png"));
    }
    // Lugia
    else if (nom == "Lugia") {
        spes.push_back(move("Aeroblast", 100, 95, "Flying", "attacks/Aeroblast.png"));
        spes.push_back(move("Psychic", 90, 100, "Psychic", "attacks/Psychic.png"));
        spes.push_back(move("Hydro Pump", 110, 80, "Water", "attacks/Hydro-Pump.png"));
        spes.push_back(move("Recover", 0, 100, "Normal", "attacks/Recover.png"));
    }
    // Zapdos
    else if (nom == "Zapdos") {
        spes.push_back(move("Thunderbolt", 90, 100, "Electric", "attacks/Thunderbolt.png"));
        spes.push_back(move("Drill Peck", 80, 100, "Flying", "attacks/Drill-Peck.png"));
        spes.push_back(move("Heat Wave", 95, 90, "Fire", "attacks/Heat-Wave.png"));
        spes.push_back(move("Roost", 0, 100, "Flying", "attacks/Roost.png"));
    }
    // Moltres
    else if (nom == "Moltres") {
        spes.push_back(move("Fire Blast", 110, 85, "Fire", "attacks/Fire-Blast.png"));
        spes.push_back(move("Air Slash", 75, 95, "Flying", "attacks/Air-Slash.png"));
        spes.push_back(move("Solar Beam", 120, 100, "Grass", "attacks/Solar-Beam.png"));
        spes.push_back(move("Roost", 0, 100, "Flying", "attacks/Roost.png"));
    }
    // Raikou
    else if (nom == "Raikou") {
        spes.push_back(move("Thunderbolt", 90, 100, "Electric", "attacks/Thunderbolt.png"));
        spes.push_back(move("Shadow Ball", 80, 100, "Ghost", "attacks/Shadow-Ball.png"));
        spes.push_back(move("Extreme Speed", 80, 100, "Normal", "attacks/Extreme-Speed.png"));
        spes.push_back(move("Calm Mind", 0, 100, "Psychic", "attacks/Calm-Mind.png"));
    }
    // Entei
    else if (nom == "Entei") {
        spes.push_back(move("Sacred Fire", 100, 95, "Fire", "attacks/Sacred-Fire.png"));
        spes.push_back(move("Stone Edge", 100, 80, "Rock", "attacks/Stone-Edge.png"));
        spes.push_back(move("Extreme Speed", 80, 100, "Normal", "attacks/Extreme-Speed.png"));
        spes.push_back(move("Iron Head", 80, 100, "Steel", "attacks/Iron-Head.png"));
    }
    // Suicune
    else if (nom == "Suicune") {
        spes.push_back(move("Hydro Pump", 110, 80, "Water", "attacks/Hydro-Pump.png"));
        spes.push_back(move("Ice Beam", 90, 100, "Ice", "attacks/Ice-Beam.png"));
        spes.push_back(move("Calm Mind", 0, 100, "Psychic", "attacks/Calm-Mind.png"));
        spes.push_back(move("Mirror Coat", 0, 100, "Psychic", "attacks/Mirror-Coat.png"));
    }
    // Kyogre
    else if (nom == "Kyogre") {
        spes.push_back(move("Water Spout", 150, 100, "Water", "attacks/Water-Spout.png"));
        spes.push_back(move("Thunder", 110, 70, "Electric", "attacks/Thunder.png"));
        spes.push_back(move("Ice Beam", 90, 100, "Ice", "attacks/Ice-Beam.png"));
        spes.push_back(move("Calm Mind", 0, 100, "Psychic", "attacks/Calm-Mind.png"));
    }
    // Groudon
    else if (nom == "Groudon") {
        spes.push_back(move("Precipice Blades", 120, 85, "Ground", "attacks/Precipice-Blades.png"));
        spes.push_back(move("Fire Punch", 75, 100, "Fire", "attacks/Fire-Punch.png"));
        spes.push_back(move("Stone Edge", 100, 80, "Rock", "attacks/Stone-Edge.png"));
        spes.push_back(move("Solar Beam", 120, 100, "Grass", "attacks/Solar-Beam.png"));
    }
    // Ho-Oh
    else if (nom == "Ho-Oh") {
        spes.push_back(move("Sacred Fire", 100, 95, "Fire", "attacks/Sacred-Fire.png"));
        spes.push_back(move("Brave Bird", 120, 100, "Flying", "attacks/Brave-Bird.png"));
        spes.push_back(move("Earthquake", 100, 100, "Ground", "attacks/Earthquake.png"));
        spes.push_back(move("Recover", 0, 100, "Normal", "attacks/Recover.png"));
    }
    // Articuno
    else if (nom == "Articuno") {
        spes.push_back(move("Blizzard", 110, 70, "Ice", "attacks/Blizzard.png"));
        spes.push_back(move("Ice Beam", 90, 100, "Ice", "attacks/Ice-Beam.png"));
        spes.push_back(move("Hurricane", 110, 70, "Flying", "attacks/Hurricane.png"));
        spes.push_back(move("Roost", 0, 100, "Flying", "attacks/Roost.png"));
    }
    // Blastoise
    else if (nom == "Blastoise") {
        spes.push_back(move("Hydro Pump", 110, 80, "Water", "attacks/Hydro-Pump.png"));
        spes.push_back(move("Ice Beam", 90, 100, "Ice", "attacks/Ice-Beam.png"));
        spes.push_back(move("Flash Cannon", 80, 100, "Steel", "attacks/Flash-Cannon.png"));
        spes.push_back(move("Earthquake", 100, 100, "Ground", "attacks/Earthquake.png"));
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