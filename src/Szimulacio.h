#ifndef SZIMULACIO_H
#define SZIMULACIO_H
#include "AutoPalya.h"
#include "AutoPalyaGeneral.h"
#include <iostream>

class Szimulacio{
    int ciklusszam;
public:

    //konstruktor, mely inicializalja a ciklusszam adattagjat
    Szimulacio(int ciklusszam=0):ciklusszam(ciklusszam){}

    //beolvassa a megadott file elso int erteket es beallitja ra a ciklusszamot
    void SetCiklus(const char* filename);

    //a megadott ciklusszamszor lefuttatja a szimulaciot vegigmegy az autopalyan
    //es minden Jarmut a sajat mozgasa alapjan mozgat es minden szimulacios ciklus
    //vegen a megadott ostream outputra kiirja az autoplya akkori allapotat
    void Szimulal(AutoPalya& ap, std::ostream& os) const;
};


#endif // SZIMULACIO_H
