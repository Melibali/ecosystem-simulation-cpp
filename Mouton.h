#ifndef MOUTON_H
#define MOUTON_H

#include "Animal.h"

class Mouton : public Animal {
public:
    Mouton(int x, int y, bool sexe);

    virtual void agir(Univers& u) override;
    virtual bool estMort() const override;
};

#endif
