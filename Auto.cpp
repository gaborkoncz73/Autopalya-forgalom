#ifndef AUTO_CPP
#define AUTO_CPP
#include "Auto.h"
#include "AutoPalya.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

Jarmu* Auto::clone() const{
    return (new Auto(*this));
}

void Auto::megy(){
    int random = rand() % 100 + 1;
    if(random <=this->GetAP().GetAllando() && this->GetSebesseg()>1){
        this->SetSebesseg(this->GetSebesseg()-1);
    }
    else if(this->GetSebesseg() < this->GetAP().MaxSeb()){
        this->SetSebesseg(this->GetSebesseg()+1);
    }
    int a=0,b=0;
    this->GetPozicio(a,b);
    int ujhely = this->GetSebesseg()+a;
    if(ujhely > this->GetAP().GetHossz()-1){
        this->GetAP().DeleteJarmu(this->GetAP().keres(a));
    }
    else{
        if(!this->GetAP().Foglalte(ujhely)){
            this->SetPozicio(ujhely);
        }else{
            while(ujhely>a && this->GetAP().Foglalte(ujhely))
            {
                ujhely--;
                this->SetSebesseg(this->GetSebesseg()-1);
            }
            if(ujhely > a){
                this->SetPozicio(ujhely);
            }
        }
    }
}

void Auto::kiir(int& a, std::ostream& os) const{
    os << "A";
}

#endif // AUTO_CPP
