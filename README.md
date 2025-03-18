# Projet Pokémon Battle Simulator

Ce projet est un simulateur de combat Pokémon en C++ utilisant la bibliothèque SFML pour la gestion des graphiques et des sons. Le projet permet à deux joueurs de s'affronter en choisissant des Pokémon et en utilisant des attaques pour vaincre l'équipe adverse.

## Structure du projet

Le projet est composé des fichiers suivants :

### Fichiers principaux

- *Game_master.cpp / Game_master.hpp** : Gère la logique du combat, y compris la sélection des attaques, les calculs de dégâts, et la gestion des tours.
- *Graphique.cpp / Graphique.hpp** : Gère l'interface graphique, y compris l'affichage des Pokémon, des barres de vie, des boutons d'attaque, et des animations.
- *Pokemon.cpp / Pokemon.hpp** : Définit la classe de base `Pokemon` et ses sous-classes pour différents types de Pokémon. Chaque Pokémon a des statistiques et des attaques spécifiques.
- *PokemonDB.cpp / PokemonDB.hpp** : Gère une base de données de Pokémon, permettant de charger des Pokémon spécifiques par leur nom.

### Autres fichiers

- **move.hpp** : Définit la classe `move` qui représente les attaques des Pokémon.
- **main.cpp** : Point d'entrée du programme, initialise la fenêtre SFML et lance le jeu.

## Compilation et exécution

### Prérequis

- **SFML** : Assurez-vous d'avoir installé la bibliothèque SFML sur votre système. Vous pouvez la télécharger depuis [le site officiel de SFML](https://www.sfml-dev.org/download.php).
- **Compilateur C++** : Ce projet nécessite un compilateur C++ compatible avec C++11 ou supérieur (comme `g++` ou `clang`).

### Compilation

Pour compiler le projet, utilisez la commande suivante :

```bash
make

```

## Execution
Pour l'excution , utilisez la commande suivante :

```bash
./jeu

```

## Fonctionnalités
Sélection de Pokémon : Les joueurs peuvent choisir deux Pokémon chacun parmi une liste prédéfinie.

Combat tour par tour : Les joueurs sélectionnent des attaques pour leurs Pokémon, et le jeu calcule les dégâts en fonction des types et des statistiques.

  - *Animations : Des animations sont présentes pour les attaques et les changements de Pokémon.

  - *Gestion des types : Les attaques ont des types qui influencent leur efficacité contre certains types de Pokémon.

  - *Interface graphique : Une interface utilisateur graphique est fournie pour sélectionner les attaques et voir l'état du combat.

## Explication des fichiers
Game_master.cpp / Game_master.hpp

  - GameMaster : Classe principale qui gère la logique du combat. Elle gère les tours, les attaques, les dégâts, et vérifie si un Pokémon est K.O.

  - BattleState : Énumération qui représente les différents états du combat (attente d'entrée, exécution du tour, animation, etc.).

  - TurnAction : Structure qui représente une action de tour (attaque, cible, priorité).

## Graphique.cpp / Graphique.hpp

 - Window : Classe qui gère l'interface graphique. Elle affiche les Pokémon, les barres de vie, les boutons d'attaque, et gère les animations.

  - Animation : Gère les animations des attaques et des changements de Pokémon.

  - Targeting System : Système de sélection de cible pour les attaques.

## Pokemon.cpp / Pokemon.hpp
  - Pokemon : Classe de base pour les Pokémon. Chaque Pokémon a un nom, un type, des statistiques (HP, attaque, défense, vitesse), et une liste d'attaques.

  - Sous-classes : Chaque type de Pokémon (eau, feu, électrique, etc.) a une sous-classe qui initialise ses attaques spécifiques.

## PokemonDB.cpp / PokemonDB.hpp
  - PokemonDB : Classe qui gère une base de données de Pokémon. Elle permet de charger des Pokémon par leur nom et de récupérer leurs informations.

## Améliorations possibles

  - Ajouter plus de Pokémon et d'attaques.

  - Implémenter des effets de statut (paralysie, poison, etc.).

  - Ajouter un mode solo contre l'IA.

 -  Améliorer les animations et les effets visuels.