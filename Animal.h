#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>

enum CauseMort { AUCUNE, MANGE, FAIM, VIEILLESSE };

class Univers;

class Animal {
protected:
    int x, y;
    bool sexe;     // 0 = femelle, 1 = mâle
    int age;
    int faim;
    bool immobile;
    bool mort;
    CauseMort cause;
    int mortX, mortY;
public:
    Animal(int x, int y, bool sexe);
    virtual ~Animal() {}

    int getX() const { return x; }
    int getY() const { return y; }
    bool getSexe() const { return sexe; }
    int getAge() const { return age; }
    int getFaim() const { return faim; }
    virtual bool estMort() const = 0;
    bool estImmobile() const { return immobile; }
    CauseMort getCause() const { return cause; }

    void setPosition(int nx, int ny);
    void vieillir();
    void setImmobile(bool b);
    void tuer(CauseMort c);

    virtual void agir(Univers& u) = 0;
    int toursDepuisRepro;

    int getMortX() const { return mortX; }
    int getMortY() const { return mortY; }

};

#endif
