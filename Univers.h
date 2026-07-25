#ifndef UNIVERS_H
#define UNIVERS_H

#include <vector>
#include <string>
#include "Case.h"
class Animal;
class Mouton;
class Loup;
class Renard;
class Univers {
public:
    Univers(int t);
    ~Univers();
    bool estDansGrille(int x, int y) const;
    Case& getCase(int x, int y);
    void ajouterAnimal(Animal* a);
    void ajouterEvenement(const std::string& evt);
    int comptermoutons() const;
    int compterLoups() const;
    int compterHerbe() const;
    int compterSels() const;
    int compterRenards() const;
    bool estMort() const;
    void deplacerAnimal(Animal* a, int nx, int ny);
    std::string formaterCoord(int x, int y);
    void integrerNouveaux();
    void tour();
    void afficher() const;
    bool trouverCaseLibreAutour(int x, int y, int& bx, int& by);
    void ajouterAnimalAleatoire(char type, bool sexe);
private:
    int taille;
    int numTour;
    std::vector<std::vector<Case>> grille;
    std::vector<Animal*> animaux;
    std::vector<Animal*> nouveaux;
    std::vector<std::string> evenements;
};

#endif
