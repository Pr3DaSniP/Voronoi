# Voronoi discret

![Langage](https://img.shields.io/badge/Language-CPP-blue)
![Librairie](https://img.shields.io/badge/Librairie-OpenCV-green)

## Description

Ce projet vise à mettre en oeuvre l'algorithme de [Voronoi](https://fr.wikipedia.org/wiki/Diagramme_de_Voronoi) pour mettre en oeuvre une approximation d'image en C++ avec la librairie OpenCV.

## Installation

Dans les paramètres du projet :

C/C++ > Général > Autres répertoires include : Ajouter le chemin vers le dossier include de la bibliothèque OpenCV

Éditeur de liens > Général > Répertoires de bibliothèques supplémentaires : Ajouter le chemin vers le dossier lib de la bibliothèque OpenCV

Éditeur de liens > Entrée > Dépendances supplémentaires : Ajouter les librairies suivantes :

- opencv_world460d.lib
- opencv_world460.lib

---

### Diagramme de Voronoi discret avec algorithmes de force brute

#### Distance euclidienne

La distance euclidienne est la distance entre deux points dans un espace euclidien, elle est définie par la formule suivante :

```math
d = \sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2}
```

<br />

![Distance euclidienne](Voronoi/output/Voronoi%20Discret%20Euclidienne.jpg)

#### Distance de Manhattan

La distance de Manhattan est la distance entre deux points dans un espace euclidien, elle est définie par la formule suivante :

```math
d = |x_2 - x_1| + |y_2 - y_1|
```

<br />

![Distance de Manhattan](Voronoi/output/Voronoi%20Discret%20distance.jpg)

#### Distance infinie

La distance infinie est la distance entre deux points dans un espace euclidien, elle est définie par la formule suivante :

```math
d = max(|x_2 - x_1|, |y_2 - y_1|)
```

<br />

![Distance infinie](Voronoi/output/Voronoi%20Discret%20distanceInf.jpg)

---

### Diagramme de Voronoi discret avec l'algorithme séquentiel

On calcule la transformation de distances (TD) sur une image initial (0, infini) en balayant l’image deux fois de la façon suivante:

- avec le masque avant: de gauche à droite et de haut en bas,
- avec le masque arrière: de droite à gauche et de bas en haut

![Diagramme de Voronoi discret avec l'algorithme séquentiel](Voronoi/output/Voronoi%20Discret%20Sequentiel.jpg)

---

L'algorithme de Voronoi permet d'approximer une image avec des formes géométriques simples.

Image de départ : <br />
![Image de départ](Voronoi/img.jpg)

Image approximée (en gris): <br />
| 0.5% | 2% | 10% |
|:----:|:--:|:---:|
| ![0.5%](Voronoi/output/0.5_Approximation%20Gris.jpg) | ![2%](Voronoi/output/2_Approximation%20Gris.jpg) | ![10%](Voronoi/output/10_Approximation%20Gris.jpg) |

Image approximée (en couleur): <br />
| 0.5% | 2% | 10% |
|:----:|:--:|:---:|
| ![0.5%](Voronoi/output/0.5_Approximation%20RBG.jpg) | ![2%](Voronoi/output/2_Approximation%20RBG.jpg) | ![10%](Voronoi/output/10_Approximation%20RBG.jpg) |
