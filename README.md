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
 ```bash
sudo apt-get install libsfml-dev
```
 2. **Clonez ce dépôt** sur votre machine :
 ```bash
 git clone https://github.com/Ouabm/Pokemon.git
 cd Pokémon
```
 ### 1.3 Compilation 
 Pour compiler et executer le code effectuer les lignes de code ci-dessous : 
 ```bash
 make
./pokemon
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


 ## Améliorations possibles

 - Ajouter plus de Pokémon et d'attaques.

 - Implémenter des effets de statut (paralysie, poison, etc.).

 - Ajouter un mode solo contre l'IA.

 - Améliorer les animations et les effets visuels. 