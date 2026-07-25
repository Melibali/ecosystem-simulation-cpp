#include "Mouton.h"
#include "Univers.h"
#include <cstdlib>

Mouton::Mouton(int x, int y, bool sexe)
    : Animal(x, y, sexe) {}

bool Mouton::estMort() const {
    return mort || faim > 5 || age > 50;
}

void Mouton::agir(Univers& u) {
    if (estImmobile()) {
        setImmobile(false);
        return;
    }
    vieillir();
    if (estMort()) return;

    if (u.getCase(x, y).herbe) {
        u.getCase(x, y).herbe = false;
        faim = 0;
    }
    int dx = rand() % 3 - 1;
    int dy = rand() % 3 - 1;

    int nx = x + dx;
    int ny = y + dy;

    if (u.estDansGrille(nx, ny) && u.getCase(nx, ny).estLibre()) {
        u.deplacerAnimal(this, nx, ny);
    }
    for (int dx2 = -1; dx2 <= 1; dx2++) {
        for (int dy2 = -1; dy2 <= 1; dy2++) {

            if (dx2 == 0 && dy2 == 0) continue;

            int nx2 = x + dx2;
            int ny2 = y + dy2;

            if (!u.estDansGrille(nx2, ny2)) continue;

            Mouton* partenaire = dynamic_cast<Mouton*>(u.getCase(nx2, ny2).animal);
            if (!partenaire) continue;
            if (this->getSexe() == partenaire->getSexe()) continue;
            if (this->estImmobile() || partenaire->estImmobile()) continue;
            if (rand() % 10 != 0) continue;
            int bx, by;
            if (!u.trouverCaseLibreAutour(x, y, bx, by))
                continue;
            Mouton* newM = new Mouton(bx, by, rand() % 2);
            u.ajouterAnimal(newM);
            u.ajouterEvenement(
                u.formaterCoord(bx, by) + "Un mouton est né."
            );
            this->setImmobile(true);
            partenaire->setImmobile(true);
            return;
        }
    }
}
