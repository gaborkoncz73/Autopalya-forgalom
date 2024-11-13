#ifndef KAMION_H
#define KAMION_H
#include "Jarmu.h"

class Kamion : public Jarmu {
    int pozi2;
public:

    //konstruktor mely meghivja az ososztaly konstruktorat + beallitja a sajat
    //extra adattagjat az inicializalo listajaban
    Kamion(int sebesseg, int poz1, int poz2,  AutoPalya& ap)
        : Jarmu(sebesseg, poz1, ap), pozi2(poz2) {}

    //feluldefinialja a Jarmu osztaly SetPozicio virtualis fuggvenyet
    //a kapott parameter az egyik pozicioja a kamionnak hiszen o ket helyet foglal
    //a kapott poziciot beallitja a Jarmu setpozicio setterevel es a masodik pozicionak
    //pedig az elso mellett kell lennie igy annal eggyel kisebbe allitja a
    //sajat plusz adattagjat
    void SetPozicio(int poz) {Jarmu::SetPozicio(poz); this->pozi2 = poz-1;}

    //feluldefinialja a Jarmu osztaly GetPozicio fuggvenyet
    //meghivja a Jarmu osztaly GetPoziciojat a két referencia parameterre
    //igy az elso pozicio a helyen lesz a masodikra, pedig -1et ad a Jarmuben
    //definialt fuggveny ezert itt a masodik parametert beallitja a sajat pozi2 adattagjara
    void GetPozicio(int& poz1, int& poz2) const override {Jarmu::GetPozicio(poz1,poz2), poz2 = this->pozi2;}

    //a kiiratas soran ahol kamion van ott biztosan "KK" elsz kiirva hiszen ketto
    //egymast koveto helyet foglal, ezert ez a fgv feluldefinialja a virtualist
    //es kiir ketto K-t,de mivel kettot irt ki, az az autopalyan ketto pozicio, ezert
    //novelni kell a ciklus valtozot is 1-gyel (igy 2-vel no a ciklussal egyutt)
    void kiir(int& a, std::ostream& os) const override;

    //feluldefinialja a megy fuggvenyt es a sajat mozgasat reprezentalja
    void megy() override;

    //Jarmu mutatot ad vissza, mely egy ujonnan foglalt Kamion objektumra mutat
    Jarmu* clone() const override;
};


#endif // KAMION_H
