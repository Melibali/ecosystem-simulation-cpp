#include "Renard.h"
#include "Univers.h"
#include "Mouton.h"
#include "Loup.h"
#include <cstdlib>

Renard::Renard(int x, int y, bool sexe)
    : Animal(x, y, sexe) {}

bool Renard::estMort() const {
    return mort || faim > 8 || age > 50;
}

void Renard::agir(Univers& u) {

    if (estImmobile()) {
        setImmobile(false);
        return;
    }

    vieillir();
    faim++;

    if (estMort()) return;

    int x = getX();
    int y = getY();

    //FUITE DES LOUPS
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {

            if (dx == 0 && dy == 0) continue;

            int nx = x + dx;
            int ny = y + dy;

            if (!u.estDansGrille(nx, ny)) continue;

            if (dynamic_cast<Loup*>(u.getCase(nx, ny).animal)) {

                int fx = x + (rand() % 5 - 2);
                int fy = y + (rand() % 5 - 2);

                if (u.estDansGrille(fx, fy) && u.getCase(fx, fy).estLibre()) {
                    u.deplacerAnimal(this, fx, fy);
                    return;
                }
            }
        }
    }

    //CHASSE DES MOUTONS
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {

            if (dx == 0 && dy == 0) continue;
            int nx = x + dx;
            int ny = y + dy;
            if (!u.estDansGrille(nx, ny)) continue;
            Mouton* m = dynamic_cast<Mouton*>(u.getCase(nx, ny).animal);
            if (m) {
                m->tuer(MANGE);
                faim = 0;
                u.deplacerAnimal(this, nx, ny);
                return;
            }
        }
    }

    //DÉPLACEMENT ALÉATOIRE
    int dx = rand() % 3 - 1;
    int dy = rand() % 3 - 1;
    int nx = x + dx;
    int ny = y + dy;

    if (u.estDansGrille(nx, ny) && u.getCase(nx, ny).estLibre()) {
        u.deplacerAnimal(this, nx, ny);
    }
    //REPRODUCTION
    for (int dx2 = -1; dx2 <= 1; dx2++) {
        for (int dy2 = -1; dy2 <= 1; dy2++) {

            if (dx2 == 0 && dy2 == 0) continue;

            int nx2 = x + dx2;
            int ny2 = y + dy2;

            if (!u.estDansGrille(nx2, ny2)) continue;

            Renard* r = dynamic_cast<Renard*>(u.getCase(nx2, ny2).animal);
            if (!r) continue;

            if (this->sexe == r->sexe) continue;
            if (this->estImmobile() || r->estImmobile()) continue;

            if (rand() % 10 != 0) continue;

            int bx, by;
            if (!u.trouverCaseLibreAutour(x, y, bx, by))
                continue;

            Renard* newRenard = new Renard(bx, by, rand() % 2);
            u.ajouterAnimal(newRenard);

            this->setImmobile(true);
            r->setImmobile(true);

            return;
        }
    }
}
