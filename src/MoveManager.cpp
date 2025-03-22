#include "MoveManager.hpp"

// Définition des mouvements

// Normal
const Move judgment("Judgment", Type::Normal, 100, 100, false);
const Move slash("Slash", Type::Normal, 70, 100, true);

// Plante
const Move energyBall("Energy Ball", Type::Grass, 90, 100, false);
const Move leafBlade("Leaf Blade", Type::Grass, 90, 100, true);

// Feu
const Move flameThrower("Flamethrower", Type::Fire, 90, 100, false);
const Move fireBlast("Fire Blast", Type::Fire, 110, 85, false);
const Move fusionFlare("Fusion Flare", Type::Fire, 100, 100, false);
const Move sacredFire("Sacred Fire", Type::Fire, 100, 95, true);
const Move firePunch("Fire Punch", Type::Fire, 75, 100, true);

// Eau
const Move scald("Scald", Type::Water, 80, 100, false);
const Move originPulse("Origin Pulse", Type::Water, 110, 85, false);
const Move liquidation("Liquidation", Type::Water, 85, 100, true);

// Électrique
const Move thunderBolt("Thunderbolt", Type::Electric, 90, 100, false);
const Move thunder("Thunder", Type::Electric, 110, 70, false);
const Move wildCharge("Wild Charge", Type::Electric, 90, 100, true);
const Move fusionBolt("Fusion Bolt", Type::Electric, 100, 100, true);

// Glace
const Move iceBeam("Ice Beam", Type::Ice, 90, 100, false);
const Move iceSpinner("Ice Spinner", Type::Ice, 80, 100, true);

// Combat
const Move auraSphere("Aura Sphere", Type::Fighting, 80, 100, false);
const Move sacredSword("Sacred Sword", Type::Fighting, 90, 100, true);
const Move focusBlast("Focus Blast", Type::Fighting, 120, 70, true);

// Poison
const Move sludgeBomb("Sludge Bomb", Type::Poison, 90, 100, false);
const Move poisonJab("Poison Jab", Type::Poison, 80, 100, true);
const Move gunkShot("Gunk Shot", Type::Poison, 120, 80, true);

// Sol
const Move earthPower("Earth Power", Type::Ground, 90, 100, false);
const Move landsWrath("Land's Wrath", Type::Ground, 90, 100, true);
const Move precipiceBlades("Precipice Blades", Type::Ground, 120, 85, true);

// Vol
const Move hurricane("Hurricane", Type::Flying, 110, 70, false);
const Move aeroBlast("Aeroblast", Type::Flying, 100, 95, false);
const Move fly("Fly", Type::Flying, 90, 95, true);

// Psy
const Move psychic("Psychic", Type::Psychic, 90, 100, false);
const Move psyBlade("Psyblade", Type::Psychic, 80, 100, true);

// Insecte
const Move bugBuzz("Bug Buzz", Type::Bug, 90, 100, false);
const Move lunge("Lunge", Type::Bug, 80, 100, true);

// Roche
const Move powerGem("Power Gem", Type::Rock, 80, 100, false);
const Move stoneEdge("Stone Edge", Type::Rock, 100, 90, true);

// Spectre
const Move shadowBall("Shadow Ball", Type::Ghost, 80, 100, false);
const Move poltergeist("Poltergeist", Type::Ghost, 110, 90, true);

// Dragon
const Move dracoMeteor("Draco Meteor", Type::Dragon, 130, 70, false);
const Move dragonPulse("Dragon Pulse", Type::Dragon, 85, 100, false);
const Move dragonClaw("Dragon Claw", Type::Dragon, 80, 95, true);

// Ténèbres
const Move fieryWrath("Fiery Wrath", Type::Dark, 90, 100, false);
const Move foulPlay("Foul Play", Type::Dark, 95, 100, true);

// Acier
const Move flashCannon("Flash Cannon", Type::Steel, 80, 100, false);
const Move ironHead("Iron Head", Type::Steel, 80, 100, true);
const Move ironTail("Iron Tail", Type::Steel, 100, 75, true);

// Fée
const Move moonBlast("Moonblast", Type::Fairy, 95, 100, false);
const Move playRough("Play Rough", Type::Fairy, 90, 90, true);
