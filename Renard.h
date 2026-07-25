#ifndef RENARD_H
#define RENARD_H

#include "Animal.h"
class Renard : public Animal {
public:
    Renard(int x, int y, bool sexe);
    bool estMort() const override;
    void agir(Univers& u) override;
};

#endif
