#ifndef SZIMULACIO_CPP
#define SZIMULACIO_CPP
#include "Szimulacio.h"

void Szimulacio::Szimulal(AutoPalya& ap, std::ostream& os) const{
    for(int i = 0; i < ciklusszam; i++){
        for(int j = ap.GetHossz()-1; j>=0; j--){
            if(ap.Foglalte(j)){
                Jarmu& temp = ap.keres(j);
                temp.megy();
            }
        }
        ap.Iras(os);
    }
}

void Szimulacio::SetCiklus(const char* filename){
    int ciklus=0;
    std::ifstream file(filename);
    if(!file){
        throw BajVan("Nem letezo fajl");
    }else{
        file >> ciklus;
    }
    file.close();
    ciklusszam = ciklus;
}

#endif // SZIMULACIO_CPP
