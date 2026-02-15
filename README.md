# Projet C++ – Portefeuille d’Actifs

## Description

Ce projet implémente un modèle simplifié de portefeuille d’actifs financiers en C++.  
Il permet de gérer des positions et de calculer les principaux indicateurs financiers d’un portefeuille : rendement attendu, variance, volatilité et ratio de Sharpe.

Le projet repose sur une approche orientée objet avec deux classes principales :

- `Asset` : représente un actif financier (nom, prix, rendement attendu, volatilité)
- `Portfolio` : représente un portefeuille composé de plusieurs actifs et de leurs quantités

Ce projet a été réalisé dans le cadre d’un mini-projet académique en C++.

---

## Fonctionnalités

Le programme permet :

- Ajouter une position dans le portefeuille
- Supprimer une position
- Calculer le rendement attendu pondéré
- Calculer la variance à partir d’une matrice de corrélation
- Calculer la volatilité du portefeuille
- Calculer le ratio de Sharpe
- Fusionner deux portefeuilles (`operator+`)
- Accéder à une position par son nom (`operator[]`)
- Gérer les erreurs via des exceptions
- Afficher le contenu détaillé du portefeuille (valeur, poids, rendement)

---

## Modélisation financière

### Rendement attendu

E(R_p) = somme des (w_i * E(R_i))

où :

w_i = (P_i × q_i) / somme des (P_j × q_j)

- P_i : prix de l’actif
- q_i : quantité détenue

---

### Variance

Var(R_p) = somme double des (w_i * w_j * sigma_i * sigma_j * rho_ij)

où :

- sigma_i : volatilité de l’actif i
- rho_ij : corrélation entre i et j

---

### Ratio de Sharpe

Sharpe = (E(R_p) − r_f) / sigma_p

où :

- r_f : taux sans risque
- sigma_p : volatilité du portefeuille

Le ratio de Sharpe mesure la performance ajustée du risque.

---

## Structure du projet

.
├── Asset.h  
├── Asset.cpp  
├── Portfolio.h  
├── Portfolio.cpp  
├── main.cpp  

---

## Compilation

Avec g++ :

g++ main.cpp Asset.cpp Portfolio.cpp -o portefeuille  
./portefeuille  

Sous Visual Studio :

- Ouvrir la solution
- Générer
- Exécuter

---

## Gestion des erreurs

Le projet utilise :

- std::out_of_range pour les accès invalides à un actif
- std::invalid_argument pour les matrices mal dimensionnées
- Vérification contre division par zéro pour le ratio de Sharpe

Cela garantit la robustesse du programme.

---

## Perspectives d’amélioration

Le projet peut être étendu vers :

- Optimisation moyenne-variance (Markowitz)
- Intégration de données historiques
- Lecture depuis fichiers CSV
- Ajout de contraintes d’investissement
- Calcul d’indicateurs supplémentaires (Sortino, tracking error)
- Extension vers une gestion dynamique multi-période

---



