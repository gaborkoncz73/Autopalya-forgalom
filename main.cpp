#include <iostream>
#include <exception>
#include "Jarmu.h"
#include "Auto.h"
#include "Kamion.h"
#include "AutoPalya.h"
#include "AutoPalyaGeneral.h"
#include "Szimulacio.h"
#include <cassert>
#include <iostream>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

/// Saját kivételosztály a teszthez.

void test_Jarmu() {
    AutoPalya ap(100, 120, 0.15, 1, 1);

    // Ctor tesztek
    Jarmu* j1 = new Auto(2, 24, ap);
    Jarmu* j2 = new Kamion(1, 79, 78, ap);

    //GetSebesseg es SetSebesseg teszt
    assert(j1->GetSebesseg() == 2);
    assert(j2->GetSebesseg() == 1);

    j1->SetSebesseg(120);
    j2->SetSebesseg(90);
    assert(j1->GetSebesseg() == 120);
    assert(j2->GetSebesseg() == 90);

    // GetPozicio, SetPozicio teszt
    int poz1, poz2;
    j1->GetPozicio(poz1, poz2);
    assert(poz1 == 24);
    j2->GetPozicio(poz1, poz2);
    assert(poz1 == 79 && poz2 == 78);

    j1->SetPozicio(5);
    j2->SetPozicio(10);
    j1->GetPozicio(poz1, poz2);
    assert(poz1 == 5 && poz2 == -1);
    j2->GetPozicio(poz1, poz2);
    assert(poz1 == 10 && poz2==9);

    //GetAP teszt
    assert(&j1->GetAP() == &ap);

    //clone es kiir teszt
    Jarmu* j3 = j1->clone();
    assert(j3->GetSebesseg() == j1->GetSebesseg());
    int j3poz1, j3poz2;
    j3->GetPozicio(j3poz1,j3poz2);
    j1->GetPozicio(poz1,poz2);
    assert(j3poz1 == poz1 && j3poz2 == poz2);
    assert(&j3->GetAP() == &j1->GetAP());
    int a=0;
    std::ostream& os = std::cout;
    j3->kiir(a,os); // kiir "A"-t
    assert(a == 0);

    Jarmu* j4 = j2->clone();
    assert(j4->GetSebesseg() == j2->GetSebesseg());
    int j4poz1, j4poz2;
    j4->GetPozicio(j4poz1,j4poz2);
    j2->GetPozicio(poz1,poz2);
    assert(j4poz1 == poz1 && j4poz2 == poz2);
    assert(&j4->GetAP() == &j2->GetAP());
    j4->kiir(a,os); // kiir "KK"-t
    assert(a==1);

    delete j1;
    delete j2;
    delete j3;
    delete j4;
    std::cout << std::endl << "A Jarmu (Kamion es Auto) tesztek sikeresen lefutottak." << std::endl;
}

void test_AutoPalya() {
    AutoPalya ap1(100, 120, 0.15, 2, 3);
    AutoPalya ap2(200, 180, 0.2, 3, 4);
    // getter, setter tesztek
    assert(ap1.OsszJarmu() == 5);
    assert(ap1.KamionDB() == 2);
    assert(ap1.AutoDB() == 3);
    ap1.SetOsszJarmu(4);
    assert(ap1.OsszJarmu() == 4);
    assert(ap1.MaxSeb() == 120);
    assert(ap1.GetAllando() == (float)0.15);

    // operator= teszt
    ap1 = ap2;
    assert(ap1.GetHossz() == ap2.GetHossz());
    assert(ap1.KamionDB() == ap2.KamionDB());
    assert(ap1.AutoDB() == ap2.AutoDB());
    assert(ap1.OsszJarmu() == ap2.OsszJarmu());

    AutoPalya ap3 = ap2;
    assert(ap3.GetHossz() == ap2.GetHossz());
    assert(ap3.KamionDB() == ap2.KamionDB());
    assert(ap3.AutoDB() == ap2.AutoDB());
    assert(ap3.OsszJarmu() == ap2.OsszJarmu());

    std::cout << "Az AutoPalya tesztek sikeresen lefutottak." << std::endl;
}

void test_AutoPalyaGeneral() {
    // AutoPalyaGeneral objektum létrehozása és a fő függvényének tesztje
    AutoPalyaGeneral apg(100, 120, 0.15, 2, 3);
    Jarmu** jarmuk = apg.GetJ();
    int osszjarmu = apg.OsszJarmu();
    int ka=0,au=0;
    for (int i = 0; i < osszjarmu; i++) {
        Jarmu* j = jarmuk[i];
        int a,b;
        j->GetPozicio(a,b);
        std::cout << "Jarmu " << i + 1 << ": Sebesseg = " << j->GetSebesseg() << ", Pozicio = " << a;
        if(b != -1){
            std::cout << " " << b <<std::endl;
            ka++;
        }
        else{
            std::cout <<std::endl;
            au++;
        }
    }
    assert(au == 3);
    assert(ka == 2);
    assert(apg.AutoDB() + apg.KamionDB() == apg.OsszJarmu());
    //A konstruktora meghivja a KezdoAllapotGeneralas-t es a tobbi fuggvenye, pedig megegyezik az AutoPalyaeval

    std::cout << "Az AutoPalyaGeneral tesztek sikeresen lefutottak." << std::endl;
}

void test_Szimulacio() {
    // Sziumlacio objektum létrehozása és a főbb függvényeik tesztjei

    //fajlbol fajlba szimulacio es kiiratas
    AutoPalya ap;
    Szimulacio sz;
    sz.SetCiklus("teszt2.txt");
    AutoPalya apFile = ap.FajlbolToltes("teszt2.txt");
    std::ofstream file("teszt.txt");
    sz.Szimulal(apFile,file);

    //fajlbol konzolra
    AutoPalya ap2;
    Szimulacio sz2;
    sz2.SetCiklus("teszt2.txt");
    AutoPalya apFile2 = ap2.FajlbolToltes("teszt2.txt");
    sz2.Szimulal(apFile2,std::cout);

    //Konzolrol fileba
    //Tegyuk fel, hogy ezek lettek beolvasva
    int hossz=100, autodb=15, kamiondb=8, maxsebesseg=6, ciklusok=25;
    float allando = 0.3;
    AutoPalyaGeneral apg(hossz,maxsebesseg,allando,kamiondb,autodb);
    Szimulacio sz3(ciklusok);
    std::ofstream file2("teszt3.txt");
    apg.Iras(file2);
    sz3.Szimulal(apg,file2);

    //konzolrol konzolra
    //Tegyuk fel, hogy ezek lettek beolvasva

    int hossz2=100, autodb2=30, kamiondb2=20, maxsebesseg2=10, ciklusok2=26;
    float allando2 = 0.3;
    AutoPalyaGeneral apg2(hossz2,maxsebesseg2,allando2,kamiondb2,autodb2);
    Szimulacio sz4(ciklusok2);
    apg2.Iras(std::cout);
    sz4.Szimulal(apg2,std::cout);

    std::cout << "A Szimulacio tesztek sikeresen lefutottak." << std::endl;
}

int main() {
    std::srand(std::time(0));
    /*test_Jarmu();
    test_AutoPalya();
    test_AutoPalyaGeneral();
    test_Szimulacio();
    try {
        int nr;
        std::cout << "Irja be a teszt sorszamat: ";
        std::cin >> nr;
        switch (nr) {
            case 1:
                test_Jarmu();
                break;

            case 2:
                test_AutoPalya();
                break;

            case 3:
                test_AutoPalyaGeneral();
                break;

            case 4:
                test_Szimulacio();
                break;

            default:
                std::cout << "Ervenytelen teszteset!" << std::endl;
                break;
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (BajVan& uzenet) {
        std::cerr << uzenet.GetUzi() << std::endl;
    } catch (...) {
        std::cerr << "* Nagy baj van! *" << std::endl;
    }*/
    try{
        int number = 0, hossz=0, autodb=0, kamiondb=0, maxsebesseg=5, ciklusok=0;
        float allando = 0.15;
        char nev[100];
        char hova[100];
        std::cout << "Fajlbol szetetne betoltetni egy kezdoallapotot a megfelelo adatokkal vagy pedig konzolon gepelne be es generaltatna le? Gepelje be a megfelelo sorszamot!" << std::endl;
        std::cout << "\t\t\t[1]fajl\t\t\t\t\t[2]Konzol" <<std::endl;
        std::cin >> number;
        if(number == 1){
            std::cout << "Adja meg a file nevet: ";
            std::cin >> nev;
            std::cout << "Hova szeretne kirajzoltatni a szimulaciot?" << std::endl;
            std::cout << "\t\t\t[1]fajl\t\t\t\t\t[2]Konzol" <<std::endl;
            std::cin >> number;
            AutoPalya ap;
            Szimulacio szim;
            AutoPalya apFile = ap.FajlbolToltes(nev);
            if(number == 1){
                std::cout << "Adja meg a file nevet: ";
                std::cin >> hova;
                szim.SetCiklus(nev);
                std::ofstream file(hova);
                szim.Szimulal(apFile,file);
            }
            else if(number == 2){
                szim.SetCiklus(nev);
                szim.Szimulal(apFile,std::cout);
            }
            else{
                std::cout << "Helyes adatot adjon meg!";
            }
        }
        else if(number == 2){
            std::cout << "Adja meg az adatokat az alabbi sorrendben szokozzel elvalasztva (hossz, kamiondb, autodb, ciklusszam, maxsebesseg, figyelmetlensegi tenyezo) :";
            std::cin >> hossz >> kamiondb >> autodb >> ciklusok >> maxsebesseg >> allando;
            if((kamiondb*2+autodb) > hossz){
        throw BajVan("Mivel a kamion 2 az auto pedig egy helyet hasznal, olyan bemenetet adjon meg, ahol a kamion*2+auto <= mint a hossz!");
            }else if(allando <= float(0) || allando >= float(1)){
                throw BajVan("0 es 1 kozott lehet a figyelmetlensegi tenyezo erteke!");
            }
            std::cout << "Hova szeretne kirajzoltatni a szimulaciot?" << std::endl;
            std::cout << "\t\t\t[1]fajl\t\t\t\t\t[2]Konzol" <<std::endl;
            std::cin >> number;
            AutoPalyaGeneral apg(hossz,maxsebesseg,allando,kamiondb,autodb);
            Szimulacio szim(ciklusok);
            if(number == 1){
                std::cout << "Adja meg a file nevet: ";
                std::cin >> hova;
                std::ofstream file(hova);
                apg.Iras(file);
                szim.Szimulal(apg,file);
            }
            else if(number == 2){
                apg.Iras(std::cout);
                szim.Szimulal(apg,std::cout);
            }
            else{
                std::cout << "Helyes adatot adjon meg!";
            }
        }
        else{
            std::cout << std::endl << "Helyes adatot adjon meg" << std::endl;
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (BajVan& uzenet) {
        std::cerr << uzenet.GetUzi() << std::endl;
    } catch (...) {
        std::cerr << "* Nagy baj van! *" << std::endl;
    }
}


