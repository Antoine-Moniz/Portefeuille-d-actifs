#include "Portfolio.h"
#include <iomanip>
#include <cmath>
#include <iostream>


void Portfolio::ajouterPosition(const Asset& asset, double quantite) {
    std::string nom = asset.getNom();

    if (positions.find(nom) != positions.end()) {
        // Si l’actif existe déjà → on additionne la quantité
        positions[nom].second += quantite;
    }
    else {
        positions[nom] = std::make_pair(asset, quantite);
    }
}


double Portfolio::rendementAttendu() const {

    double valeurTotale = 0.0;

    // 1Calcul de la valeur totale du portefeuille
    for (const auto& element : positions) {
        const Asset& asset = element.second.first;
        double quantite = element.second.second;

        valeurTotale += asset.getPrix() * quantite;
    }

    if (valeurTotale == 0.0) {
        return 0.0;
    }

    //  Calcul du rendement pondéré
    double rendement = 0.0;

    for (const auto& element : positions) {
        const Asset& asset = element.second.first;
        double quantite = element.second.second;

        double valeur = asset.getPrix() * quantite;
        double poids = valeur / valeurTotale;

        rendement += poids * asset.getRendementAttendu();
    }

    return rendement;
}

double Portfolio::variance(const std::vector<std::vector<double>>& matriceCorrelation) const {

    size_t n = positions.size();

    // Vérification dimension matrice
    if (matriceCorrelation.size() != n) {
        throw std::invalid_argument("Matrice de correlation mal dimensionnee");
    }

    for (const auto& ligne : matriceCorrelation) {
        if (ligne.size() != n) {
            throw std::invalid_argument("Matrice de correlation mal dimensionnee");
        }
    }

    // Stocker poids et volatilites
    std::vector<double> poids;
    std::vector<double> volatilites;

    double valeurTotale = 0.0;

    for (const auto& element : positions) {
        const Asset& asset = element.second.first;
        double quantite = element.second.second;

        valeurTotale += asset.getPrix() * quantite;
    }

    for (const auto& element : positions) {
        const Asset& asset = element.second.first;
        double quantite = element.second.second;

        double valeur = asset.getPrix() * quantite;
        poids.push_back(valeur / valeurTotale);
        volatilites.push_back(asset.getVolatilite());
    }

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

std::pair<Asset, double>& Portfolio::operator[](const std::string& nom) {

    auto it = positions.find(nom);

    if (it == positions.end()) {
        throw std::out_of_range("Actif introuvable dans le portefeuille");
    }

    return it->second;
}

void Portfolio::retirerPosition(const std::string& nom) {

    auto it = positions.find(nom);

    if (it == positions.end()) {
        throw std::out_of_range("Actif introuvable dans le portefeuille");
    }

    positions.erase(it);
}


const std::pair<Asset, double>& Portfolio::operator[](const std::string& nom) const {

    auto it = positions.find(nom);

    if (it == positions.end()) {
        throw std::out_of_range("Actif introuvable dans le portefeuille");
    }

    return it->second;
}


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

double Portfolio::ratioSharpe(double tauxSansRisque,
    const std::vector<std::vector<double>>& matriceCorrelation) const {

    double rendement = rendementAttendu();
    double volatilite = std::sqrt(variance(matriceCorrelation));

    if (volatilite == 0.0) {
        throw std::invalid_argument("Volatilite nulle, ratio de Sharpe indefini");
    }

    return (rendement - tauxSansRisque) / volatilite;
}
