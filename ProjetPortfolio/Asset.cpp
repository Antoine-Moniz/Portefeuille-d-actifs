#include "Asset.h"

// Constructeur par défaut
Asset::Asset()
    : nom(""),
    prix(0.0),
    rendementAttendu(0.0),
    volatilite(0.0)
{
}

// Constructeur avec paramètres
Asset::Asset(const std::string& nom,
    double prix,
    double rendementAttendu,
    double volatilite)
    : nom(nom),
    prix(prix),
    rendementAttendu(rendementAttendu),
    volatilite(volatilite)
{
}

// Getters
std::string Asset::getNom() const {
    return nom;
}

double Asset::getPrix() const {
    return prix;
}

double Asset::getRendementAttendu() const {
    return rendementAttendu;
}

double Asset::getVolatilite() const {
    return volatilite;
}
