#ifndef AUTOPALYA_H
#define AUTOPALYA_H
#include "Jarmu.h"
#include <string>
#include <iostream>

class BajVan {
    std::string szoveg;
public:
    BajVan(const std::string& s) : szoveg(s) {}
    std::string GetUzi(){return szoveg;}
};


class AutoPalya {
protected:
    Jarmu** jarmuk;
    int hossz;
    const int maxsebesseg;
    const float allando;
    int kamiondb;
    int autodb;
    int osszjarmu;
public:

    //Ctor: meghivja a jarmuk ctorat es inicializalja az adattagokat
    AutoPalya(int hossz=0, int maxseb=0, float all=0, int kamiondb=0, int autodb=0)
        : jarmuk(new Jarmu*[kamiondb+autodb]{}), hossz(hossz), maxsebesseg(maxseb), allando(all), kamiondb(kamiondb), autodb(autodb), osszjarmu(autodb+kamiondb){
        }

    //masolo ctor
    AutoPalya(const AutoPalya& other)
        : jarmuk(new Jarmu*[other.kamiondb+other.autodb]{}),hossz(other.hossz), maxsebesseg(other.maxsebesseg), allando(other.allando), kamiondb(other.kamiondb), autodb(other.autodb), osszjarmu(other.osszjarmu) {}

    //visszaadja a jarmuk osszesseget
    int OsszJarmu() const {return this->osszjarmu;}

    //visszaadja a kamionok szamat
    int KamionDB() const {return this->kamiondb;}

    //visszaadja az autok szamat
    int AutoDB() const {return this->autodb;}

    //beallitja az osszjarmuk szamat
    void SetOsszJarmu(int oj){this->osszjarmu = oj;}

    //visszaadja a max sebesseget
    const int MaxSeb() const {return this->maxsebesseg;}

    //visszaadja a figyelmetlensegi allandot
    const float GetAllando() const {return this->allando;}

    //visszaadja az autopalya hosszat
    int GetHossz() const {return this->hossz;}

    //visszaadja a heterogen kollekciot
    Jarmu** GetJ() const {return this->jarmuk;}

    //visszaadja a kollekcio i. elemet
    Jarmu& GetJarmu(int i) const {return *jarmuk[i];}

    //beallitja a kollekciot j-re
    void SetJarmu(Jarmu** j) {jarmuk = j;}

    //kiirja a megadott outputra az autopalya jelenlegi allapotat
    void Iras(std::ostream& os);

    //beolvassa a megadott fajlbol az adatokat, letrehoz egy AutoPalya objektumot
    //inicializalja, majd beletolti a megadott autopalya akkori helyzetet
    AutoPalya FajlbolToltes(const char* filename);

    //kitorli a kollekciobol a J elemet es nullptr-re allitja
    void DeleteJarmu(Jarmu& J);

    //visszad egy olyat letezo poziciot, ahol nincs meg semmilyen jarmu
    int RandomPozi() const;

    //megnezi, hogy az adott pozicion van-e valami es visszaadja a logikai erteket
    bool Foglalte(int pozi) const;

    //megkeresi, hogy melyik Jarmu van az a. pozicion es visszaadja referenciakent
    Jarmu& keres(int a) const;

    //az AutoPalya ertekado operatora
    AutoPalya& operator=(const AutoPalya& rhs);

    //destruktor, mely a megmaradt jarmuveket es a kollekciot felszabaditja
    virtual ~AutoPalya();
};


#endif // AUTOPALYA_H
