#pragma once
#include "Move.hpp"

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



