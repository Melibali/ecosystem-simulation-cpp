#ifndef LOUP_H
#define LOUP_H
#include "Animal.h"

class Loup : public Animal {
public:
    Loup(int x, int y, bool sexe);
    virtual void agir(Univers& u) override;
    virtual bool estMort() const override;
};

#endif
