#include <iostream>
#include <vector>
#include <cmath>

#include "Asset.h"
#include "Portfolio.h"

int main() {

    try {

        // ===============================
        // Création des actifs
        // ===============================
        Asset apple("Apple", 150.0, 0.08, 0.20);
        Asset tesla("Tesla", 200.0, 0.12, 0.30);
        Asset microsoft("Microsoft", 250.0, 0.10, 0.25);

        // ===============================
        // Création du portefeuille p1
        // ===============================
        Portfolio p1;

        p1.ajouterPosition(apple, 10);
        p1.ajouterPosition(tesla, 5);

        std::cout << "Portefeuille p1 cree." << std::endl;

        p1.afficherPortefeuille();

        // ===============================
        // Calcul variance
        // ===============================
        std::vector<std::vector<double>> corr = {
            {1.0, 0.3},
            {0.3, 1.0}
        };

        double var = p1.variance(corr);

        std::cout << "Variance p1 : "
            << var << std::endl;

        std::cout << "Ecart-type p1 : "
            << std::sqrt(var)
            << std::endl;

        // ===============================
        // Fusion de portefeuilles
        // ===============================
        Portfolio p2;
        p2.ajouterPosition(apple, 5);
        p2.ajouterPosition(microsoft, 8);

        Portfolio pFusion = p1 + p2;

        std::cout << "\nFusion realisee." << std::endl;

        pFusion.afficherPortefeuille();

        // ===============================
        // Test operator[]
        // ===============================
        std::cout << "Quantite Apple dans pFusion : "
            << pFusion["Apple"].second
            << std::endl;

        // ===============================
        // Test exception operator[]
        // ===============================
        try {
            std::cout << pFusion["Google"].second << std::endl;
        }
        catch (const std::out_of_range& e) {
            std::cout << "Exception capturee (operator[]) : "
                << e.what()
                << std::endl;
        }

        // ===============================
        // Suppression d'un actif
        // ===============================
        pFusion.retirerPosition("Tesla");

        std::cout << "\nTesla supprime." << std::endl;

        pFusion.afficherPortefeuille();

        // ===============================
        // Test exception suppression
        // ===============================
        try {
            pFusion.retirerPosition("Google");
        }
        catch (const std::out_of_range& e) {
            std::cout << "Exception capturee (retirerPosition) : "
                << e.what()
                << std::endl;
        }

        // ===============================
        // Test erreur matrice correlation
        // ===============================
        try {
            std::vector<std::vector<double>> mauvaiseMatrice = {
                {1.0, 0.2, 0.3}
            };

            p1.variance(mauvaiseMatrice);
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Exception capturee (variance) : "
                << e.what()
                << std::endl;
        }

        // ===============================
        //  Test version const operator[]
        // ===============================
        const Portfolio pConst = p1;

        std::cout << "\nTest const operator[] (Apple) : "
            << pConst["Apple"].second
            << std::endl;


        // ===============================
		//  Test Ratio de Sharpe
        // ===============================
        double rf = 0.02;  // 2% taux sans risque

        std::cout << "Ratio de Sharpe p1 : "
            << p1.ratioSharpe(rf, corr)
            << std::endl;


    }
    catch (const std::exception& e) {
        std::cout << "Erreur generale : "
            << e.what()
            << std::endl;
    }

    return 0;
}
