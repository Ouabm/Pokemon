# Simulateur de combat Pokémon

 Un simulateur de combat Pokémon en C++ utilisant la bibliothèque SFML pour gérer les graphiques et les sons. Ce projet permet à deux joueurs de s'affronter en sélectionnant des Pokémon et en utilisant des attaques pour vaincre l'équipe adverse.

 ---

 ## I - Prérequis

 ### 1.1 Dépendances
 Avant de commencer, vous devez installer les bibliothèques suivantes :

 - **[ SFML ]( https://www.sfml-dev.org/download.php )** : Une bibliothèque multimédia qui permet de gérer les fenêtres, les graphiques, les entrées/sorties et les sons.
 - **Compilateur C++** : Ce projet nécessite un compilateur C++ compatible avec C++11 ou supérieur (comme `g++` ou `clang` ).

 ### 1.2 Installation

 1. **Téléchargez et installez SFML** à partir du [ site officiel de SFML ]( https://www.sfml-dev.org/download.php ).
 2. **Clonez ce dépôt** sur votre machine :
 ```bash
 git clone https://github.com/Ouabm/Pokemon.git
 cd Pokémon
```

 ## II - Structure du Projet

 Le projet est organisé de la manière suivante :

 ### Dossier `include`
 ```texte brut
 include/
 │
 ├── states/
 │ ├── BattleState.hpp # Gère la logique du combat et les actions.
 │ ├── EndState.hpp # Gère la fin du jeu, résultats et options.
 │ ├── MenuState.hpp # Gère le menu principal (début, règles, etc.).
 │ └── SelectionState.hpp # Ouvrez l'écran de sélection des Pokémon.
 │
 ├── DamageCalculator.hpp # Calcule les dégâts des attaques selon les types et stats. 
 ├── ElementUI.hpp # Gère l'interface utilisateur pour les éléments graphiques.
 ├── GameParameters.hpp # Contient les paramètres du jeu (nombre de Pokémon, règles).
 ├── GameState.hpp # Déclarer la classe `GameState` représentant l'état du jeu.
 ├── GameStateManager.hpp # Gère les transitions entre les états du jeu.
 ├── Move.hpp # Déclarez la classe `Move` pour les attaques des Pokémon.
 ├── MoveManager.hpp # Gère la logique des attaques et leurs effets.
 ├── Pokemon.hpp # Définit la classe de base `Pokemon` avec ses attributs.
 ├── PokemonManager.hpp # Gère la création et la gestion des Pokémon.
 ├── RessourceManager.hpp # Gère les ressources du jeu (images, fils, etc.).
 └── Type.hpp # Déclarez les types de Pokémon et leurs interactions.
 ```

 ### Dossier `src`
```texte brut
 src/
 │
 ├── states/
 │ ├── BattleState.cpp # Implémentation de la logique du combat.
 │ ├── EndState.cpp # Implémentation de la fin du jeu et options.
 │ ├── MenuState.cpp # Implémentation du menu principal.
 │ └── SelectionState.cpp # Implémentation de l'écran de sélection des Pokémon.
 │
 ├── ElementUI.cpp # Implémentation de la gestion de l'interface utilisateur.
 ├── GameStateManager.cpp # Implémentation de la gestion des transitions d'état.
 ├── main.cpp # Point d'entrée du programme, initialisez la fenêtre SFML et lancez le jeu.
 ├── MoveManager.cpp # Implémentation de la gestion des attaques.
 ├── PokemonManager.cpp # Implémentation de la gestion des Pokémon.
 ├── RessourceManager.cpp # Implémentation de la gestion des ressources.
 └── Type.cpp # Implémentation des types de Pokémon et leurs interactions.
 ```

## III - Déroulement d'une Partie

### 1. **Menu Principal**
- Le joueur arrive sur un **menu principal** qui propose trois options :
  - **Start** : Démarre une nouvelle partie.
  - **Help** : Affiche des instructions sur la manière de jouer.
  - **Quit** : Quitte le jeu.
  
### 2. **Sélection des Pokémon**
- Si le joueur sélectionne **Start**, il arrive dans une **fenêtre de sélection des Pokémon**.
- Le joueur peut choisir ses Pokémon :
  - Le joueur **Bleu** utilise les touches **ZQSD** pour se déplacer et **Espace** pour valider son choix.
  - Le joueur **Rouge** utilise les **flèches directionnelles** et **Entrée** pour valider son choix.
- Une fois les Pokémon sélectionnés, le jeu passe à la **fenêtre de combat**.

### 3. **Fenêtre de Combat**
- La fenêtre de combat affiche les Pokémon des deux équipes ainsi que leurs barres de vie.
- En dessous, il y a un menu où chaque joueur peut choisir les **quatre mouvements** du Pokémon sélectionné. Chaque équipe dispose d'une interface rectangulaire pour faire ses choix :
  - Le joueur **Bleu** utilise la touche **Tab** pour changer de Pokémon et **Espace** pour choisir un mouvement.
  - Le joueur **Rouge** utilise la touche **P** pour changer de Pokémon et **Entrée** pour choisir un mouvement.
- Une fois qu'un mouvement est choisi, chaque joueur valide son choix :
  - **Espace** pour le joueur **Bleu**.
  - **Entrée** pour le joueur **Rouge**.

### 4. **Sélection de la Cible**
- Après avoir choisi le mouvement, une **cible** apparaît à l'écran pour que le joueur choisisse le Pokémon adverse qu'il souhaite attaquer.
  - Le joueur **Bleu** utilise **Tab** pour valider sa cible.
  - Le joueur **Rouge** utilise **Entrée** pour valider sa cible.

### 5. **Exécution du Tour**
- Une fois la cible sélectionnée, le tour commence :
  - Les **dégâts** sont appliqués à chaque Pokémon en fonction des attaques et de leurs statistiques.
- Le tour recommence après chaque action jusqu'à ce qu'une équipe perde ses **deux Pokémon**.

### 6. **Fin de Partie**
- La partie se termine lorsque **une équipe n'a plus de Pokémon en vie**. Un écran de fin affiche les résultats et permet au joueur de retourner au **menu principal** s'il appuie sur **Rejouer** ou quitter le jeu s'il appuie sur **Quit**.






 ## Fonctionnalités
 Sélection de Pokémon : Les joueurs peuvent choisir deux Pokémon chacun parmi une liste prédéfinie.

 Combat tour par tour : Les joueurs sélectionnent des attaques pour leurs Pokémon, et le jeu calcule les dégâts en fonction des types et des statistiques.

 - *Animations : Des animations sont présentes pour les attaques et les changements de Pokémon.

 - *Gestion des types : Les attaques ont des types qui influencent leur efficacité contre certains types de Pokémon.

 - *Interface graphique : Une interface utilisateur graphique est fournie pour sélectionner les attaques et voir l'état du combat.

 ## Explication des fichiers
 Game_master.cpp / Game_master.hpp

 - GameMaster : Classe principale qui gère la logique du combat. Elle gère les tours, les attaques, les dégâts, et vérifie si un Pokémon est KO

 - BattleState : Énumération qui représente les différents états du combat (attente d'entrée, exécution du tour, animation, etc.).

 - TurnAction : Structure qui représente une action de tour (attaque, cible, priorité).

 ## Graphique.cpp / Graphique.hpp

 - Fenêtre : Classe qui gère l'interface graphique. Elle affiche les Pokémon, les barres de vie, les boutons d'attaque et gère les animations.

 - Animation : Gère les animations des attaques et des changements de Pokémon.

 - Targeting System : Système de sélection de cible pour les attaques.

 ## Pokemon.cpp / Pokemon.hpp
 - Pokémon : Classe de base pour les Pokémon. Chaque Pokémon a un nom, un type, des statistiques (HP, attaque, défense, vitesse) et une liste d'attaques.

 - Sous-classes : Chaque type de Pokémon (eau, feu, électrique, etc.) a une sous-classe qui initialise ses attaques spécifiques.

 ## PokemonDB.cpp / PokemonDB.hpp
 - PokemonDB : Classe qui gère une base de données de Pokémon. Elle permet de charger des Pokémon par leur nom et de récupérer leurs informations.

 ## Améliorations possibles

 - Ajouter plus de Pokémon et d'attaques.

 - Implémenter des effets de statut (paralysie, poison, etc.).

 - Ajouter un mode solo contre l'IA.

 - Améliorer les animations et les effets visuels. 