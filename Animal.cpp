#include "Animal.h"

Animal::Animal(int x, int y, bool sexe)
    : x(x), y(y), sexe(sexe), age(0), faim(0),
      immobile(false), mort(false), cause(AUCUNE) {
    toursDepuisRepro = 0;
}

void Animal::setPosition(int nx, int ny) {
    x = nx;
    y = ny;
}

void Animal::vieillir() {
    age++;
    faim++;
    toursDepuisRepro++;
}

void Animal::setImmobile(bool b) {
    immobile = b;
}

void Animal::tuer(CauseMort c) {
    mort = true;
    cause = c;
    mortX = x;
    mortY = y;
}

