#ifndef KAMION_CPP
#define KAMION_CPP
#include "Kamion.h"
#include "AutoPalya.h"

void Kamion::kiir(int& a, std::ostream& os) const{
    a++;
    os << "KK";
}

void Kamion::megy(){
    int random = rand() % 100 + 1;
    if(random <= this->GetAP().GetAllando() && this->GetSebesseg()>1){
        this->SetSebesseg(this->GetSebesseg()-1);
    }
    else  if(this->GetSebesseg() < this->GetAP().MaxSeb()/2){
        this->SetSebesseg(this->GetSebesseg()+1);
    }
    int a=0, b=0;
    this->GetPozicio(a,b);
    int ujhely=a;
    while(ujhely < this->GetSebesseg() + a && ujhely < this->GetAP().GetHossz() && !this->GetAP().Foglalte(ujhely+1))
    {
        ujhely++;
    }
    if(ujhely>this->GetAP().GetHossz()-1){
        this->GetAP().DeleteJarmu(this->GetAP().keres(a));
    }
    else{
        this->SetPozicio(ujhely);
        this->SetSebesseg(ujhely-a);
    }
}

Jarmu* Kamion::clone() const{
    return new Kamion(*this);
}
#endif // KAMION_CPP
