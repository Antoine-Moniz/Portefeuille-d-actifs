#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <map>
#include <string>
#include <vector>
#include <stdexcept>
#include "Asset.h"

class Portfolio {
private:
    // clé = nom de l’actif
    // valeur = paire (Asset, quantité)
    std::map<std::string, std::pair<Asset, double>> positions;

public:
    // Ajouter une position
    void ajouterPosition(const Asset& asset, double quantite);

    // Supprimer une position
    void retirerPosition(const std::string& nom);

    // Calcul rendement attendu
    double rendementAttendu() const;

    // Calcul variance
    double variance(const std::vector<std::vector<double>>& matriceCorrelation) const;

    // Surcharge opérateur +
    Portfolio operator+(const Portfolio& autre) const;

    // Surcharge opérateur [] (modifiable)
    std::pair<Asset, double>& operator[](const std::string& nom);

    // Surcharge opérateur [] (lecture seule)
    const std::pair<Asset, double>& operator[](const std::string& nom) const;

    // Affichage du portefeuille
    void afficherPortefeuille() const;

    // Ratio de Sharpe
    double ratioSharpe(double tauxSansRisque, const std::vector<std::vector<double>>& matriceCorrelation) const;


};

#endif
