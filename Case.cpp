#include "Case.h"

Case::Case()
    : animal(nullptr), herbe(true), sel(false), tempsSel(0) {}

bool Case::estLibre() const {
    return animal == nullptr;
}
