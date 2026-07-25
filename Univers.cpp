#include "Univers.h"
#include "Animal.h"
#include "Mouton.h"
#include "Loup.h"
#include "Renard.h"
#include <iostream>
#include <cstdlib>
#define RESET   "\033[0m"
#define RED     "\033[31m"   // loups
#define GREEN   "\033[32m"   // herbe
#define BLUE    "\033[34m"   // moutons
#define PURPLE  "\033[35m"   // renards
#define YELLOW  "\033[33m"   // sel
#define GREY    "\033[90m"   // vide
using namespace std;

Univers::Univers(int t) : taille(t), numTour(0) {
    grille.resize(taille, vector<Case>(taille));
}
Univers::~Univers() {
    for (auto a : animaux) delete a;
    for (auto a : nouveaux) delete a;
    animaux.clear();
    nouveaux.clear();
}
bool Univers::estDansGrille(int x, int y) const {
    return x >= 0 && y >= 0 && x < taille && y < taille;
}
Case& Univers::getCase(int x, int y) {
    return grille[x][y];
}

void Univers::ajouterAnimal(Animal* a) {
    nouveaux.push_back(a);
}

bool Univers::trouverCaseLibreAutour(int x, int y, int& bx, int& by) {
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {

            if (dx == 0 && dy == 0) continue;

            int nx = x + dx;
            int ny = y + dy;

            if (!estDansGrille(nx, ny)) continue;

            if (getCase(nx, ny).estLibre()) {
                bx = nx;
                by = ny;
                return true;
            }
        }
    }
    return false;
}
void Univers::ajouterEvenement(const string& evt) {
    evenements.push_back(evt);
}
int Univers::comptermoutons() const {
    int count = 0;
    for (auto a : animaux)
        if (dynamic_cast<Mouton*>(a)) count++;
    return count;
}
int Univers::compterLoups() const {
    int count = 0;
    for (auto a : animaux)
        if (dynamic_cast<Loup*>(a)) count++;
    return count;
}
int Univers::compterRenards() const {
    int count = 0;
    for (auto a : animaux)
        if (dynamic_cast<Renard*>(a)) count++;
    return count;
}
int Univers::compterHerbe() const {
    int count = 0;
    for (auto& row : grille)
        for (auto& c : row)
            if (c.herbe && c.animal == nullptr)
                count++;
    return count;
}

int Univers::compterSels() const {
    int count = 0;
    for (auto& row : grille)
        for (auto& c : row)
            if (c.sel) count++;
    return count;
}
bool Univers::estMort() const {
    return comptermoutons() == 0 && compterLoups() == 0;
}
void Univers::deplacerAnimal(Animal* a, int nx, int ny) {
    if (!estDansGrille(nx, ny)) return;

    Animal* cible = grille[nx][ny].animal;

    if (cible != nullptr && !cible->estMort())
        return;

    grille[a->getX()][a->getY()].animal = nullptr;
    a->setPosition(nx, ny);
    grille[nx][ny].animal = a;
}

string Univers::formaterCoord(int x, int y) {
    char let = 'A' + x;
    return "[" + string(1, let) + to_string(y + 1) + "] ";
}
void Univers::integrerNouveaux() {
    for (auto a : nouveaux) {
        int ax = a->getX(), ay = a->getY();
        if (grille[ax][ay].animal != nullptr) {
            delete a;
            continue;
        }
        animaux.push_back(a);
        grille[ax][ay].animal = a;
    }
    nouveaux.clear();
}

void Univers::ajouterAnimalAleatoire(char type, bool sexe)
{
    if (animaux.size() + nouveaux.size() >= taille * taille)
        return;

    int x, y;

    do {
        x = rand() % taille;
        y = rand() % taille;
    }
    while (!grille[x][y].estLibre());

    if (type == 'M')
        ajouterAnimal(new Mouton(x, y, sexe));

    else if (type == 'L')
        ajouterAnimal(new Loup(x, y, sexe));

    else if (type == 'R')
        ajouterAnimal(new Renard(x, y, sexe));
}
void Univers::tour() {
    numTour++;
    evenements.clear();

    for (auto a : animaux)
        if (!a->estMort())
            a->agir(*this);

    integrerNouveaux();

    vector<Animal*> survivants;

    for (auto a : animaux) {
        if (a->estMort()) {
            int cx, cy;
            if (a->getCause() == MANGE) {
                cx = a->getMortX();
                cy = a->getMortY();
            } else {
                cx = a->getX();
                cy = a->getY();
            }
            string coord = formaterCoord(cx, cy);

            if (a->getCause() == AUCUNE) {
                if (dynamic_cast<Mouton*>(a)) {
                    if (a->getFaim() > 5) a->tuer(FAIM);
                    else                 a->tuer(VIEILLESSE);
                } else {
                    if (a->getFaim() > 10) a->tuer(FAIM);
                    else                  a->tuer(VIEILLESSE);
                }
            }

            if (dynamic_cast<Mouton*>(a)) {
                if (a->getCause() == MANGE)
                    ajouterEvenement(coord + "Un mouton a servi de repas a un loup.");
                else if (a->getCause() == VIEILLESSE)
                    ajouterEvenement(coord + "Un mouton meurt de vieillesse.");
                else
                    ajouterEvenement(coord + "Un mouton meurt de faim.");
            }
            else if (dynamic_cast<Loup*>(a)) {
                if (a->getCause() == VIEILLESSE)
                    ajouterEvenement(coord + "Un loup meurt de vieillesse.");
                else
                    ajouterEvenement(coord + "Un loup meurt de faim.");
            }

            if (a->getCause() != MANGE) {
                grille[cx][cy].animal = nullptr;
                grille[cx][cy].sel      = true;
                grille[cx][cy].tempsSel = 2;
            }

            delete a;
        }
        else {
            survivants.push_back(a);
        }
    }
    animaux = survivants;
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            if (!grille[i][j].sel) continue;

            grille[i][j].tempsSel--;

            if (grille[i][j].tempsSel <= 0) {
                grille[i][j].herbe = true;
                grille[i][j].sel   = false;
                ajouterEvenement(formaterCoord(i, j) + "De l'herbe repousse !");
            }
        }
    }
}

void Univers::afficher() const {
    cout << "      ";
    for (int j = 0; j < taille; j++)
        cout << j + 1 << "   ";
    cout << "\n";

    for (int i = 0; i < taille; i++) {
        cout << "    ";
        for (int j = 0; j < taille; j++) cout << "+---";
        cout << "+\n";

        char ligne = 'A' + i;
        cout << "  " << ligne << " |";

        for (int j = 0; j < taille; j++) {
            const Case& c = grille[i][j];
            cout << " ";
            if (c.animal != nullptr) {
                if (dynamic_cast<Loup*>(c.animal))
                    cout << RED << "L" << RESET;
                else if (dynamic_cast<Mouton*>(c.animal))
                    cout << BLUE << "M" << RESET;
                else if (dynamic_cast<Renard*>(c.animal))
                    cout << PURPLE << "R" << RESET;
                else
                    cout << "?";
            }
            else if (c.herbe)
                cout << GREEN << "H" << RESET;

            else if (c.sel)
                cout << YELLOW << "S" << RESET;

            else
                cout << GREY << " " << RESET;

            cout << " |";
        }
        cout << "\n";
    }
    cout << "    ";
    for (int j = 0; j < taille; j++) cout << "+---";
    cout << "+\n\n";

    for (const auto& evt : evenements)
        cout << evt << "\n";

    cout << "\nTour " << numTour
         << " | Loups : "   << compterLoups()
         << " | Moutons : " << comptermoutons()
         << " | Renards : " << compterRenards()
         << " | Herbe : "   << compterHerbe()
         << " | Sels : "    << compterSels()
         << "\n------------------------------------------\n";
}
