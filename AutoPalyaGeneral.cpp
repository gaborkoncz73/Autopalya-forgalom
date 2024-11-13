#ifndef AUTOPALYAGENERAL_CPP
#define AUTOPALYAGENERAL_CPP
#include "AutoPalyaGeneral.h"

void AutoPalyaGeneral::KezdoAllapotGeneralas(){
    int k = 0;
    while(k<kamiondb){
        int poz = RandomPozi();
        int seb = (rand() % (maxsebesseg))/2 + 1;
        if(!Foglalte(poz-1) && poz != 0){
            jarmuk[k] = new Kamion(seb, poz, poz-1, *this);
            k++;
        }
    }
    while(k<autodb+kamiondb){
        int poz = RandomPozi();
        int seb = rand() % maxsebesseg +1;
        jarmuk[k] = new Auto(seb,poz,*this);
        k++;
    }
}





#endif // AUTOPALYAGENERAL_CPP
