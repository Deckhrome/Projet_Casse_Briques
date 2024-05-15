# Casse Briques

Ce projet est réalisé par Johan VERDON et Jean-Raphaël JULIEN. Il consiste à réaliser un casse-briques en C++.

## Lancement du projet

Pour lancer le jeu, il faut compiler avec la commande `make` puis exécuter le jeu avec la commande `./bin/main`.

## Implémentation des fonctionnalités

Nous avons implémenté différentes fonctionnalités :

- **Briques rectangulaires** : Les briques sont de forme rectangulaire et peuvent être détruites par la balle.
- **Paddle contrôlé avec souris ou clavier** : Le paddle peut être contrôlé soit à l'aide de la souris, soit du clavier.
- **Gestion d'un menu avec différents niveaux** : Un menu permet de sélectionner différents niveaux.
- **Niveaux gérés avec des fichiers** : Les niveaux sont définis dans des fichiers et peuvent être modifiés en écrivant dans ces fichiers.
- **Large variété de bonus** : Nous avons implémenté 7 types de bonus différents, définis dans le fichier `bonus.hpp`.

## Fonctionnalités détaillées

### Briques

Les briques sont des objets rectangulaires qui peuvent être détruits par la balle. Chaque brique a une durabilité qui diminue lorsqu'elle est touchée par la balle. Lorsque la durabilité atteint zéro, la brique est détruite.

### Paddle

Le paddle est contrôlé par le joueur et peut être déplacé à l'aide de la souris ou du clavier. Le paddle est utilisé pour renvoyer la balle vers les briques.

### Menu

Le menu du jeu permet de sélectionner différents niveaux. Les niveaux sont définis dans des fichiers et peuvent être modifiés pour créer de nouveaux défis.

### Niveaux

Les niveaux sont définis dans des fichiers texte, ce qui permet de les modifier facilement. Chaque fichier de niveau spécifie la disposition des briques, ainsi que les bonus disponibles.

### Bonus

Les bonus sont des objets spéciaux qui apparaissent lorsque certaines briques sont détruites. Il existe 7 types de bonus différents :

1. **Augmentation de la taille du paddle** : Augmente la largeur du paddle.
2. **Duplication de la balle** : Ajoute une balle supplémentaire.
3. **Réduction de la taille de la balle** : Diminue la taille de la balle.
4. **Augmentation de la vie** : Ajoute une vie supplémentaire.
5. **Augmentation du score** : Augmente le ratio de points gagnés.
6. **Augmentation de la vitesse de la balle** : Accélère la balle.
7. **Réduction de la taille du paddle** : Réduit la largeur du paddle.

## Structure du projet

Le projet est structuré en plusieurs fichiers et dossiers :

- **src/** : Contient les fichiers source C++ du projet.
- **include/** : Contient les fichiers d'en-tête (headers) du projet.
- **bin/** : Contient les exécutables compilés.
- **assets/** : Contient les ressources du jeu (niveaux, images, sons, etc.).
- **Makefile** : Fichier de construction permettant de compiler le projet avec la commande `make`.

## Instructions de compilation

Pour compiler le projet, utilisez la commande suivante :

```bash
make
```

Cette commande génère l'exécutable principal dans le dossier `bin/`.

## Instructions d'exécution

Pour exécuter le jeu, utilisez la commande suivante :

```bash
./bin/main
```

## Dépendances

Le projet nécessite les bibliothèques suivantes :

- **SDL2** : Bibliothèque pour la gestion des graphiques et des entrées.
- **SDL2_image** : Bibliothèque pour la gestion des images.
- **SDL2_ttf** : Bibliothèque pour la gestion des polices de caractères.

Assurez-vous que ces bibliothèques sont installées sur votre système avant de compiler le projet.

## Auteurs

Ce projet a été réalisé par :

- Johan VERDON
- Jean-Raphaël JULIEN

## Remerciements

Nous remercions notre professeur et les assistants pédagogiques pour leur soutien tout au long de ce projet.

---

Merci de votre attention et amusez-vous bien avec notre casse-briques !