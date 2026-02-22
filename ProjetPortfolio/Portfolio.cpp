#include "Portfolio.h"
#include <iomanip>
#include <cmath>
#include <iostream>


// ===============================
// AJOUTER UNE POSITION
// ===============================
void Portfolio::ajouterPosition(const Asset& asset, double quantite) {
    std::string nom = asset.getNom(); // Récupération du nom de l’actif

    if (positions.find(nom) != positions.end()) {
        // Si l’actif existe déjà → on additionne la quantité existante
        positions[nom].second += quantite;
    }
    else {
        // Sinon → on crée une nouvelle entrée dans la map
        positions[nom] = std::make_pair(asset, quantite);
    }
}


// ===============================
// CALCUL DU RENDEMENT ATTENDU
// ===============================
double Portfolio::rendementAttendu() const {

    double valeurTotale = 0.0;

    // 1) Calcul de la valeur totale du portefeuille
    for (const auto& element : positions) {
        const Asset& asset = element.second.first;   // Actif
        double quantite = element.second.second;    // Quantité détenue

        valeurTotale += asset.getPrix() * quantite; // Valeur de la position
    }

    // Si portefeuille vide → rendement nul
    if (valeurTotale == 0.0) {
        return 0.0;
    }

    // 2) Calcul du rendement pondéré
    double rendement = 0.0;

    for (const auto& element : positions) {
        const Asset& asset = element.second.first;
        double quantite = element.second.second;

        double valeur = asset.getPrix() * quantite; // Valeur position
        double poids = valeur / valeurTotale;       // Poids dans le portefeuille

        rendement += poids * asset.getRendementAttendu(); // Somme pondérée
    }

    return rendement;
}


// ===============================
// CALCUL DE LA VARIANCE DU PORTEFEUILLE
// ===============================
double Portfolio::variance(const std::vector<std::vector<double>>& matriceCorrelation) const {

    size_t n = positions.size(); // Nombre d’actifs

    // Vérification dimension matrice de corrélation
    if (matriceCorrelation.size() != n) {
        throw std::invalid_argument("Matrice de correlation mal dimensionnee");
    }

    for (const auto& ligne : matriceCorrelation) {
        if (ligne.size() != n) {
            throw std::invalid_argument("Matrice de correlation mal dimensionnee");
        }
    }

    // Stocker poids et volatilités
    std::vector<double> poids;
    std::vector<double> volatilites;

    double valeurTotale = 0.0;

    // 1) Calcul valeur totale
    for (const auto& element : positions) {
        const Asset& asset = element.second.first;
        double quantite = element.second.second;

        valeurTotale += asset.getPrix() * quantite;
    }

    // 2) Remplir vecteurs poids et volatilités
    for (const auto& element : positions) {
        const Asset& asset = element.second.first;
        double quantite = element.second.second;

        double valeur = asset.getPrix() * quantite;
        poids.push_back(valeur / valeurTotale);      // Poids
        volatilites.push_back(asset.getVolatilite()); // Volatilité individuelle
    }

    // 3) Calcul variance portefeuille :
    // Somme(i,j) wi * wj * sigma_i * sigma_j * corr_ij
    double variance = 0.0;

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            variance += poids[i] * poids[j] *
                volatilites[i] * volatilites[j] *
                matriceCorrelation[i][j];
        }
    }

    return variance;
}


// ===============================
// OPÉRATEUR + (FUSION DE DEUX PORTEFEUILLES)
// ===============================
Portfolio Portfolio::operator+(const Portfolio& autre) const {

    Portfolio resultat;

    // Ajouter les positions du premier portefeuille (this)
    for (const auto& element : positions) {
        const Asset& asset = element.second.first;
        double quantite = element.second.second;

        resultat.ajouterPosition(asset, quantite);
    }

    // Ajouter les positions du deuxième portefeuille
    for (const auto& element : autre.positions) {
        const Asset& asset = element.second.first;
        double quantite = element.second.second;

        resultat.ajouterPosition(asset, quantite);
    }

    return resultat;
}


// ===============================
// OPÉRATEUR [] NON CONST
// ===============================
std::pair<Asset, double>& Portfolio::operator[](const std::string& nom) {

    auto it = positions.find(nom);

    if (it == positions.end()) {
        throw std::out_of_range("Actif introuvable dans le portefeuille");
    }

    return it->second; // Retour référence modifiable
}


// ===============================
// RETIRER UNE POSITION
// ===============================
void Portfolio::retirerPosition(const std::string& nom) {

    auto it = positions.find(nom);

    if (it == positions.end()) {
        throw std::out_of_range("Actif introuvable dans le portefeuille");
    }

    positions.erase(it); // Suppression de la position
}


// ===============================
// OPÉRATEUR [] CONST
// ===============================
const std::pair<Asset, double>& Portfolio::operator[](const std::string& nom) const {

    auto it = positions.find(nom);

    if (it == positions.end()) {
        throw std::out_of_range("Actif introuvable dans le portefeuille");
    }

    return it->second; // Retour référence non modifiable
}


// ===============================
// AFFICHAGE DU PORTEFEUILLE
// ===============================
void Portfolio::afficherPortefeuille() const {

    if (positions.empty()) {
        std::cout << "Portefeuille vide." << std::endl;
        return;
    }

    double valeurTotale = 0.0;

    // Calcul valeur totale
    for (const auto& element : positions) {
        const Asset& asset = element.second.first;
        double quantite = element.second.second;
        valeurTotale += asset.getPrix() * quantite;
    }

    std::cout << "\n===== Contenu du portefeuille =====" << std::endl;

    // Affichage détaillé
    for (const auto& element : positions) {

        const Asset& asset = element.second.first;
        double quantite = element.second.second;

        double valeur = asset.getPrix() * quantite;
        double poids = (valeur / valeurTotale) * 100.0;

        std::cout << "Actif : " << asset.getNom()
            << " | Quantite : " << quantite
            << " | Prix : " << asset.getPrix()
            << " | Valeur : " << valeur
            << " | Poids : "
            << std::fixed << std::setprecision(2)
            << poids << " %"
            << std::endl;
    }

    std::cout << "-----------------------------------" << std::endl;
    std::cout << "Valeur totale : " << valeurTotale << std::endl;
    std::cout << "Rendement attendu : "
        << rendementAttendu() << std::endl;
    std::cout << "===================================\n" << std::endl;
}


// ===============================
// CALCUL DU RATIO DE SHARPE
// ===============================
double Portfolio::ratioSharpe(double tauxSansRisque,
    const std::vector<std::vector<double>>& matriceCorrelation) const {

    double rendement = rendementAttendu(); // Rendement portefeuille
    double volatilite = std::sqrt(variance(matriceCorrelation)); // Écart-type

    if (volatilite == 0.0) {
        throw std::invalid_argument("Volatilite nulle, ratio de Sharpe indefini");
    }

    // Formule : (Rp - Rf) / sigma_p
    return (rendement - tauxSansRisque) / volatilite;
}