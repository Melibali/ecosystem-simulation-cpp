#ifndef CASE_H
#define CASE_H

class Animal;

class Case {
public:
    Animal* animal;  
    bool herbe;       
    bool sel;         
    int tempsSel;     

    Case();

    bool estLibre() const;
};

#endif
