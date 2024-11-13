#ifndef JARMU_H
#define JARMU_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <new>

class AutoPalya;

class Jarmu {
    int sebesseg;
    int pozi;
    AutoPalya& autop;
public:

    //konstruktor, mely inicializalja az osztaly adattagjait
    Jarmu(int sebesseg, int pozi, AutoPalya& ap)
        : sebesseg(sebesseg), pozi(pozi), autop(ap){}

    //visszaadja a Jarmu sebesseget
    int GetSebesseg() const {return this->sebesseg;}

    //beallitja a jarmu sebesseget a kert egesz ertekre
    void SetSebesseg(int a){this->sebesseg = a;}

    //visszaad egy AutoPalya referenciat, mely tartalmazza az autopalya adatait
    //es a jelen allasat
    AutoPalya& GetAP()const {return this->autop;}

    //virtualis fuggveny mely olyan alosztalyok eseten, melyek nem definialjak felul szamukra
    //beallitja a poziciot a megadott szamra
    virtual void SetPozicio(int poz) {this->pozi = poz;}

    //virtualis fuggveny, mely olyan alosztalyok eseten, melyek nem definialjak felul szamukra
    //visszaadja a az elso referencia parameterbe irva a poziciot a masodik referencia parameterbe
    //pedig -1et ir.
    virtual void GetPozicio(int& poz1, int& poz2) const {poz1 = this->pozi, poz2=-1;}

    //teljesen virtualis fuggveny, melyet minden leszarmazottnak felul kell definialni
    virtual void kiir(int& a, std::ostream& os) const = 0;

    //teljesen virtualis fuggveny, melyet minden leszarmazottnak felul kell definialni
    virtual void megy() = 0;

    //teljesen virtualis fuggveny, melyet minden leszarmazottnak felul kell definialni
    virtual Jarmu* clone() const = 0;

    virtual ~Jarmu(){}
};


#endif // JARMU_H
