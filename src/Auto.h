#ifndef AUTO_H
#define AUTO_H
#include "Jarmu.h"


class Auto : public Jarmu {
public:

    //auto explicit konstruktora, mely meghivja az ososztaly konstruktorat
    Auto(int sebesseg, int pozi, AutoPalya& ap)
        : Jarmu(sebesseg, pozi, ap) {}

    //feluldefinialja a Jarmu megy virtualis fuggvenyet es az auto mozgasat reprezentalja
    void megy() override;

    //az autopalya allapotanak kiirasakor feluldefinialja a Jarmu kiir fuggvenyet
    //es kiir egy A betut, mert ott auto van
    void kiir(int& a, std::ostream& os) const override;

    //visszaad egy Jarmu pointert, mely egy dinamikusan foglalt Auto operatorra mutat
    Jarmu* clone() const override;


};


#endif // AUTO_H
