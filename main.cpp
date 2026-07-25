#include "Univers.h"
#include "Mouton.h"
#include "Loup.h"
#include "Renard.h"
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <iostream>

using namespace std;

int main() {

    srand(time(0));

    Univers u(10);
    for (int i = 0; i < 9; i++) {
        u.ajouterAnimalAleatoire('M', rand() % 2);
    }
    for (int i = 0; i < 3; i++) {
        u.ajouterAnimalAleatoire('L', rand() % 2);
    }
    for (int i = 0; i < 2; i++) {
        u.ajouterAnimalAleatoire('R', rand() % 2);
    }
    u.integrerNouveaux();
    u.afficher();
    for (int i = 1; i <= 50; i++) {
        cout << "TOUR : " << i << endl;
        u.tour();
        u.afficher();
        cin.get();
   
    }
    return 0;
}