#ifndef AUTOPALYA_CPP
#define AUTOPALYA_CPP
#include "AutoPalya.h"
#include "Auto.h"
#include "Kamion.h"
void AutoPalya::Iras(std::ostream& os){
    for(int i = 0; i < hossz; i++)
    {
        if(Foglalte(i)){
            Jarmu& j = keres(i);
            j.kiir(i,os);
        }else{
            os << "_";
        }
    }
    os << std::endl;
}


Jarmu& AutoPalya::keres(int a) const{
    int b=-1,c=-1,i=-1;
    while(i<hossz && a != b && c != a)
    {
        i++;
        if(jarmuk[i]!=nullptr){
            jarmuk[i]->GetPozicio(b,c);
        }
    }
    return *jarmuk[i];
}

int AutoPalya::RandomPozi() const{
    int poz;
    bool flag = true;
    while(flag){
        poz = rand() % hossz;
        if(!Foglalte(poz))
        {
            flag = false;
        }
    }
    return poz;
}

bool AutoPalya::Foglalte(int poz) const{
    for(int i = 0; i < autodb+kamiondb; i++){
        int a = 0, b = 0;
        if(jarmuk[i] != nullptr){
            jarmuk[i]->GetPozicio(a,b);
            if(poz == a || poz == b)
                return true;
        }
    }
    return false;
}

void AutoPalya::DeleteJarmu(Jarmu& J){
    int i = 0;
    while(jarmuk[i] != &J){
        i++;
    }
    delete jarmuk[i];
    jarmuk[i] = nullptr;
}

AutoPalya AutoPalya::FajlbolToltes(const char* filename){
    std::ifstream file(filename);
    if(!file){
        throw BajVan("Nem letezo fajl");
    }
    int hossz=0, maxsebesseg=0, autodb=0, kamiondb=0;
    float allando=0;

    file >> hossz;
    file >> hossz;
    file >> autodb;
    file >> kamiondb;
    file >> maxsebesseg;
    file >> allando;
    if((kamiondb*2+autodb) > hossz){
        throw BajVan("Mivel a kamion 2 az auto pedig egy helyet hasznal, olyan bemenetet adjon meg, ahol a kamion*2+auto <= mint a hossz!");
    }else if(float(0)>= allando || float(1)<= allando){
        throw BajVan("0 es 1 kozott lehet a figyelmetlensegi tenyezo erteke!");
    }
    AutoPalya ap(hossz,maxsebesseg,allando,kamiondb,autodb);
    int* sebessegek = new int[autodb+kamiondb];
    for(int i = 0; i < autodb+kamiondb;i++){
        file >> sebessegek[i];
    }
    file.ignore(100, '\n');
    char sor[hossz];
    file.getline(sor,sizeof(sor));
    int tmp=0;
    for(int i = 0; i<hossz;i++){
        if(sor[i] == 'A'){
            if(sebessegek[tmp] > maxsebesseg){
                delete[] sebessegek;
                throw BajVan("Egyik auto sebessege nagyobb mint a szamara megengedett!");
            }
            tmp++;
        }else if(sor[i] == 'K'){
            i++;
            if(sebessegek[tmp] > maxsebesseg/2){
                delete[] sebessegek;
                throw BajVan("Az egyik kamion sebessege nagyobb mint a szamara megengedett!");
            }
            tmp++;
        }
    }
    tmp=0;
    Jarmu** jarmuktmp = new Jarmu*[kamiondb + autodb];
    for (int i = 0; i < kamiondb + autodb; i++) {
        jarmuktmp[i] = nullptr;
    }
    for(int i = 0; i < hossz; i++){
        if(sor[i] == 'A'){
            jarmuktmp[tmp] = new Auto(sebessegek[tmp],i,ap);
            tmp++;
        }
        else if(sor[i] == 'K'){
            i++;
            jarmuktmp[tmp] = new Kamion(sebessegek[tmp],i,i-1,ap);
            tmp++;
        }
    }
    delete[] ap.jarmuk;
    ap.SetJarmu(jarmuktmp);
    delete[] sebessegek;
    file.close();
    return ap;
}

AutoPalya& AutoPalya::operator=(const AutoPalya& rhs) {
  if (this == &rhs) {
    return *this;
  }
  for (int i = 0; i < osszjarmu; i++) {
    delete jarmuk[i];
  }
  delete[] jarmuk;
  hossz = rhs.GetHossz();
  kamiondb = rhs.KamionDB();
  autodb = rhs.AutoDB();
  osszjarmu = rhs.OsszJarmu();
  jarmuk = new Jarmu*[rhs.OsszJarmu()];
  for (int i = 0; i < rhs.OsszJarmu(); i++) {
    if (rhs.jarmuk[i]) {
      jarmuk[i] = rhs.jarmuk[i]->clone();
    } else {
      jarmuk[i] = nullptr;
    }
  }

  return *this;
}

AutoPalya::~AutoPalya() {
    for (int i = 0; i < osszjarmu; i++) {
        if(jarmuk[i] != nullptr){
            delete jarmuk[i];
            jarmuk[i] = nullptr;
        }
    }
    if(jarmuk != nullptr){
        delete[] jarmuk;
        jarmuk = nullptr;
    }

}

#endif // AUTOPALYA_CPP
