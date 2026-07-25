#include "Loup.h"
#include "Univers.h"
#include "Mouton.h"
#include <cstdlib>

Loup::Loup(int x, int y, bool sexe)
    : Animal(x, y, sexe) {}

bool Loup::estMort() const {
    return mort || faim > 10 || age > 60;
}
void Loup::agir(Univers& u) {

    if (estImmobile()) {
        setImmobile(false);
        return;
    }

    vieillir();
    if (estMort()) return;

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

            Animal* partenaire = u.getCase(nx2, ny2).animal;
            if (!partenaire) continue;

            Loup* l = dynamic_cast<Loup*>(partenaire);
            if (!l) continue;
            if (this->sexe == l->sexe) continue;
            if (this->estImmobile() || l->estImmobile()) continue;
            if (this->toursDepuisRepro < 5 || l->toursDepuisRepro < 5)
                continue;
            if (rand() % 10 != 0) continue;
            int bx, by;
            if (!u.trouverCaseLibreAutour(x, y, bx, by))
                continue;
            Loup* newLoup = new Loup(bx, by, rand() % 2);
            u.ajouterAnimal(newLoup);
            this->setImmobile(true);
            l->setImmobile(true);
            this->toursDepuisRepro = 0;
            l->toursDepuisRepro = 0;

            return; 
        }
    }
}
