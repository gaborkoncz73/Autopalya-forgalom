#ifndef AUTOPALYAGENERAL_H
#define AUTOPALYAGENERAL_H
#include "AutoPalya.h"
#include "Kamion.h"
#include "Auto.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

class AutoPalyaGeneral : public AutoPalya{
public:

    //konstruktor, mely meghivja az ososztaly konstruktorat es meghivja a
    //KezdoAllapotGeneralas fuggvenyt
    AutoPalyaGeneral(int hossz, int maxseb, float all, int kamiondb, int autodb)
        : AutoPalya(hossz, maxseb, all, kamiondb, autodb) {KezdoAllapotGeneralas();}

    //a konstruktor altal inicializalt autopalya adatait felhasznalva generalja le
    //az autopalya kezdeti allapotat, ugy hogy eloszor elhelyezi a kamionokat
    //random helyekre es random sebesseggel (a felteteleknek megfelelo), majd ezutan
    //az autokkal is elvegzi ezeket
    void KezdoAllapotGeneralas();
};


#endif // AUTOPALYAGENERAL_H
