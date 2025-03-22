#pragma once
#include "Move.hpp"

// Définition des mouvements
inline const Move Flamethrower("Flamethrower", Type::Fire, 90, 100,0);
inline const Move Fire_Blast("Fire Blast",Type::Fire,110,85,0);
inline const Move Fusion_Flare("Fusion Flare",Type::Fire,100,100,0);
inline const Move Fly("Fly", Type::Flying, 90, 95,1);
inline const Move DragonClaw("Dragon Claw", Type::Dragon, 80, 95,1);
inline const Move Slash("Slash", Type::Normal, 70, 100,1);
inline const Move Judgment("Judgment",Type::Normal,100,100,0);
inline const Move Earth_Power("Earth Power",Type::Ground,90,100,0);
inline const Move Gunk_Shot("Gunk Shot",Type::Poison,120,80,1);
inline const Move Psychics("Psychics",Type::Psychic,90,100,0);
inline const Move Thunderbolt("Thunderbolt",Type::Electric,90,100,0);
inline const Move Thunder("Thunder",Type::Electric,110,70,0);
inline const Move Ice_Beam("Ice Beam",Type::Ice,90,100,0);
inline const Move Sludge_Bomb("Sludge Bomb",Type::Poison,90,100,0);
inline const Move Bug_Buzz("Bug Buzz",Type::Bug,90,100,0);
inline const Move Dragon_Pulse("Dragon Pulse",Type::Dragon,85,100,0);
inline const Move Draco_Meteor("Draco Meteor",Type::Dragon,130,70,0);
inline const Move Moonblast("Moonblast",Type::Fairy,95,100,0);
inline const Move Flash_Cannon("Flash Cannon",Type::Steel,80,100,0);
inline const Move Energy_Ball("Energy Ball",Type::Grass,90,100,0);
inline const Move Fiery_Wrath("Fiery Wrath",Type::Dark,90,100,0);
inline const Move Scald("Scald",Type::Water,80,100,0);
inline const Move Origin_Pulse("Origin Pulse",Type::Water,110,85,0);  
inline const Move Shadow_Ball("Shadow Ball",Type::Ghost,80,100,0);
inline const Move Aura_Sphere("Aura Sphere",Type::Fighting,80,100,0);
inline const Move Aeroblast("Aeroblast",Type::Flying,100,95,0);
inline const Move Hurricane("Hurricane",Type::Flying,110,70,0);
inline const Move Liquidation("Liquidation",Type::Water,85,100,1);
inline const Move Iron_Head("Iron Head",Type::Steel,80,100,1);
inline const Move Iron_Tail("Iron Tail",Type::Steel,100,75,1);
inline const Move Stone_Edge("Stone Edge",Type::Rock,100,90,1);
inline const Move Power_Gem("Power_Gem",Type::Rock,80,100,0);
inline const Move Psyblade("Psyblade",Type::Psychic,80,100,1);
inline const Move Poison_Jab("Poison Jab",Type::Poison,80,100,1);
inline const Move Ice_Spinner("Ice Spinner",Type::Ice,80,100,1);
inline const Move Lands_Wrath("Land's Wrath",Type::Ground,90,100,1);
inline const Move Precipice_Blades("Precipice Blades",Type::Ground,120,85,1);
inline const Move Leaf_Blade("Leaf Blade",Type::Grass,90,100,1);
inline const Move Poltergeist("Poltergeist",Type::Ghost,110,90,1);
inline const Move Sacred_Fire("Sacred Fire",Type::Fire,100,95,1);
inline const Move Fire_Punch("Fire Punch",Type::Fire,75,100,1);
inline const Move Focus_Blast("Focus Blast",Type::Fighting,120,70,0);
inline const Move Sacred_Sword("Sacred Sword",Type::Fighting,90,100,1);
inline const Move Play_Rough("Play Rough",Type::Fairy,90,90,1);
inline const Move Fusion_Bolt("Fusion Bolt",Type::Electric,100,100,1);
inline const Move Wild_Charge("Wild Charge",Type::Electric,90,100,1);
inline const Move Foul_Play("Foul Play",Type::Dark,95,100,1);
inline const Move Lunge("Lunge",Type::Bug,80,100,1);
// Déclaration des mouvements

// Normal
extern const Move judgment;
extern const Move slash;

// Plante
extern const Move energyBall;
extern const Move leafBlade;

// Feu
extern const Move flameThrower;
extern const Move fireBlast;
extern const Move fusionFlare;
extern const Move sacredFire;
extern const Move firePunch;

// Eau
extern const Move scald;
extern const Move originPulse;
extern const Move liquidation;

// Électrique
extern const Move thunderBolt;
extern const Move thunder;
extern const Move wildCharge;
extern const Move fusionBolt;

// Glace
extern const Move iceBeam;
extern const Move iceSpinner;

// Combat
extern const Move auraSphere;
extern const Move sacredSword;
extern const Move focusBlast;

// Poison
extern const Move sludgeBomb;
extern const Move poisonJab;
extern const Move gunkShot;

// Sol
extern const Move earthPower;
extern const Move landsWrath;
extern const Move precipiceBlades;

// Vol
extern const Move hurricane;
extern const Move aeroBlast;
extern const Move fly;

// Psy
extern const Move psychic;
extern const Move psyBlade;

// Insecte
extern const Move bugBuzz;
extern const Move lunge;

// Roche
extern const Move powerGem;
extern const Move stoneEdge;

// Spectre
extern const Move shadowBall;
extern const Move poltergeist;

// Dragon
extern const Move dracoMeteor;
extern const Move dragonPulse;
extern const Move dragonClaw;

// Ténèbres
extern const Move fieryWrath;
extern const Move foulPlay;

// Acier
extern const Move flashCannon;
extern const Move ironHead;
extern const Move ironTail;

// Fée
extern const Move moonBlast;
extern const Move playRough;


// ------------------------------------------------------------------------------------------------------------------------------------------------------------
// Pourquoi "extern const" est bien utilisé ici :

// 1. Déclaration sans définition dans l'en-tête (header) :
//     "extern const" permet de déclarer une constante sans la définir dans le fichier d'en-tête.
//     Cela signifie que les objets Move (comme judgment, slash, etc.) sont définis ailleurs dans le code source.
//     Cette approche permet de séparer les déclarations (interface) des définitions (implémentation), 
//     ce qui est une bonne pratique pour une meilleure organisation et un code plus lisible.


// 2. Partage de constantes entre différents fichiers :
//     Ces objets Move peuvent être utilisés dans plusieurs fichiers source différents. Grâce à "extern const", 
//     la même instance de chaque mouvement peut être partagée entre tous ces fichiers sans dupliquer leur définition.
//     Cela permet d'éviter des redéfinitions et des conflits, et garantit que les mouvements restent cohérents dans tout le programme.


// 3. Garantir l'immuabilité des objets :
//     L'utilisation de "const" garantit que les valeurs des objets Move ne seront pas modifiées après leur initialisation.
//     Cela améliore la sécurité du code en s'assurant que les mouvements définis dans le jeu (comme les dégâts, les types, etc.) ne changent pas par erreur.
//     Cela optimise aussi le programme car les objets constants peuvent être plus facilement optimisés par le compilateur.


// 4. Meilleure gestion de la mémoire :
//     Étant donné que ces objets sont déclarés une seule fois (dans un fichier source), 
//     cela permet d'éviter la duplication des données et de réduire la consommation mémoire.
//     Ainsi, un objet Move n'est pas copié dans chaque fichier qui l'inclut, mais il est utilisé via une référence constante.

// ------------------------------------------------------------------------------------------------------------------------------------------------------------



