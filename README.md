## Introduction
Un simulateur d'écosystème capable de modéliser les interactions entre différentes espèces dans un environnement donné. Ce projet permet aux utilisateurs de personnaliser les paramètres de la simulation pour observer diverses dynamiques écologiques.

## Fonctionnalités
- Simule les interactions entre proies et prédateurs dans un écosystème.
- Paramètres de simulation personnalisables.
- Génère des sorties qui peuvent être analysées pour la dynamique des populations.

## Installation
Pour installer et exécuter le simulateur d'écosystème, suivez ces étapes :

1. Clonez le dépôt sur votre machine locale :
    ```sh
    git clone https://github.com/inessa-kk/ecosystem-simulator.git
    ```

2. Naviguez dans le répertoire du projet :
    ```sh
    cd ecosystem-simulator
    ```

3. Compilez le projet en utilisant le Makefile fourni :
    ```sh
    make
    ```

4. Exécutez le simulateur :
    ```sh
    ./ecosys
    ```

## Utilisation
1. Avant d'exécuté le simulateur, vous pouvez configurer les paramètres de simulation présents au début du fichier ecosys.c .
2. Le programme générera des fichiers de sortie (`Evol_Pop.txt`, `fichier.txt`) contenant des données sur la dynamique des populations au fil du temps.

## Structure du projet
- `src/`: Contient les fichiers source.
  - `ecosys.c`: Logique de simulation principale.
  - `main_ecosys.c`, `main_test2.c`, `main_tests.c`: Fichiers principaux pour différents tests et flux d'exécution.
- `include/`: Contient les fichiers d'en-tête.
  - `ecosys.h`: Fichier d'en-tête définissant les structures et prototypes de fonctions utilisés dans la simulation.
- `Makefile`: Script de construction pour compiler le projet.
- `Evol_Pop.txt`: Fichier de sortie contenant l'évolution de la population.
- `fichier.txt`: Fichier de données supplémentaire utilisé par la simulation.
- `ecosys.pdf`: Graphe d'évolution des populations de proies et de prédateurs.




