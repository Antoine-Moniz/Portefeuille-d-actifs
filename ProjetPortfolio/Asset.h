#ifndef ASSET_H
#define ASSET_H

#include <string>

class Asset {
private:
    std::string nom;
    double prix;
    double rendementAttendu;
    double volatilite;

public:
    // Constructeur par défaut (obligatoire pour std::map)
    Asset();

    // Constructeur avec paramètres
    Asset(const std::string& nom,
        double prix,
        double rendementAttendu,
        double volatilite);

    // Getters
    std::string getNom() const;
    double getPrix() const;
    double getRendementAttendu() const;
    double getVolatilite() const;
};

#endif
