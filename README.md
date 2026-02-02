# Gestion de Catalogue de Trajets (C++)

Ce projet est une application console développée en C++ permettant de gérer un catalogue de trajets de transport. Il supporte la création de trajets simples, de trajets composés (plusieurs étapes), ainsi que la sauvegarde et le chargement de données.

## Fonctionnalités

Le programme propose un menu interactif avec les options suivantes :

1. **Ajout de Trajet Simple** : Défini par une ville de départ, une ville d'arrivée et un moyen de transport.
2. **Ajout de Trajet Composé** : Un trajet constitué de plusieurs segments successifs (étapes).
3. **Affichage du Catalogue** : Liste tous les trajets enregistrés avec leurs détails.
4. **Recherche de Trajets** : Recherche directe entre une ville A et une ville B.
5. **Sauvegarde / Chargement** : Persistance des données du catalogue dans un fichier.

---

##  Architecture Technique

Le projet repose sur une structure orientée objet utilisant le polymorphisme :

### Classes Principales

* **`Trajet`** (Classe de base) : Définit l'interface commune (Ville de départ/arrivée, méthode `Afficher`).
* **`TrajetSimple`** : Hérite de `Trajet`. Ajoute la notion de moyen de transport.
* **`TrajetCompose`** : Hérite de `Trajet`. Contient une collection de trajets simples formant un itinéraire complexe.
* **`Catalogue`** : Gère la collection globale des trajets et les opérations de recherche/IO.
* **`TADListeTrajet`** : Une structure de données personnalisée (liste chaînée) pour stocker les objets `Trajet` de manière dynamique.

### Gestion de la mémoire

* Allocation dynamique des chaînes de caractères (`char*`) pour une gestion précise de la mémoire.
* Implémentation des **constructeurs de copie**, **destructeurs** et **surcharges d'opérateurs d'affectation** pour respecter la "Règle des Trois".

---

##  Installation et Compilation

Un fichier `makefile` est fourni pour faciliter la compilation sous Linux/macOS (ou via MinGW sur Windows).

1. **Compiler le projet** :
```bash
make

```


Cela générera l'exécutable nommé `trajets`.
2. **Nettoyer les fichiers objets** :
```bash
make clean

```



---

##  Utilisation

Lancez l'application avec la commande suivante :

```bash
./trajets

```

### Exemple de saisie

Lors de l'ajout d'un trajet composé, le programme vous demandera le nombre d'étapes. Assurez-vous que la ville d'arrivée de l'étape  correspond à la ville de départ de l'étape .

---

## Structure des fichiers

* `Trajet.h / .cpp` : Classe mère.
* `TrajetSimple.h / .cpp` : Spécialisation pour les trajets directs.
* `TrajetCompose.h / .cpp` : Spécialisation pour les trajets multi-étapes.
* `TADListeTrajet.h / .cpp` : Structure de liste chaînée utilitaire.
* `Catalogue.h / .cpp` : Cœur logique de l'application.
* `main.cpp` : Point d'entrée et gestion de l'interface utilisateur.

---

> **Note :** Ce projet a été réalisé dans le cadre d'un apprentissage sur la programmation orientée objet, le polymorphisme et la gestion manuelle de la mémoire en C++.

---

**Souhaitez-vous que je développe une section spécifique sur le format des fichiers de sauvegarde ou sur l'algorithme de recherche ?**
