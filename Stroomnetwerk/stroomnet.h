#ifndef __STROOMNET_H
#define __STROOMNET_H

#include "vergrotendpadzoeker.h"
#include "graaf.h"
using std::cout;
using std::endl;

/**********************************************************************

   Class: Stroomnetwerk

   beschrijving: Een stroomnetwerk gaat uit van een gewogen gerichte graaf
                 die in de constructor wordt opgegeven

***************************************************************************/

template <class T>//T = takdata
class Stroomnetwerk:public GraafMetTakdata<GERICHT, T >{
public:
//Copyconstructor. Let op: Graaf<GERICHT>(gr) moet toegevoegd,
//anders roept de copyconstructor van GraafMetTakdata de defaultconstructor
//van Graaf op en krijgen we een lege graaf.
Stroomnetwerk(const GraafMetTakdata<GERICHT, T>& gr):
                    Graaf<GERICHT>(gr),GraafMetTakdata<GERICHT, T>(gr){};


Stroomnetwerk(const GraafMetTakdata<GERICHT, T>& gr, int _van, int _naar):
                    Graaf<GERICHT>(gr.aantalKnopen()),van(_van),naar(_naar){
    Stroomnetwerk<T> restnetwerk(gr);
    Pad<T> vergrotendpad;
    Vergrotendpadzoeker<T> vg(restnetwerk, van, naar, vergrotendpad);
    while(vergrotendpad.size() !=0 ){
//        std::cout<<"Restnetwerk\n"<<restnetwerk<<"\n";
//        std::cout<<"Vergrotend pad:\n"<<vergrotendpad<<"\n";
        restnetwerk-=vergrotendpad;
        *this+=vergrotendpad;
        Vergrotendpadzoeker<T> vg(restnetwerk, van, naar, vergrotendpad);
    }
//        std::cout<<"Restnetwerk op einde\n"<<restnetwerk<<"\n";
}
Stroomnetwerk& operator-=(const Pad<T>& pad){
    T padcapaciteit=pad.geefCapaciteit();
    for (int i=1; i<pad.size(); i++ ){
        int start=pad[i-1];//start en eind van de tak
        int eind=pad[i];
        int taknr=this->verbindingsnummer(start,eind);
        assert (taknr >= 0);
        assert(this->takdatavector[taknr]>=padcapaciteit);
        this->takdatavector[taknr]-=padcapaciteit;
//noot: eventueel tak met capaciteit 0 verwijderen.
        vergrootTak(eind,start, padcapaciteit);
    }
}
Stroomnetwerk& operator+=(const Pad<T>& pad){
    T padcapaciteit=pad.geefCapaciteit();
    for (int i=1; i<pad.size(); i++ ){
        T nucapaciteit=padcapaciteit;
        int van=pad[i-1];
        int naar=pad[i];
        int terugtak=this->verbindingsnummer(naar,van);
        if (terugtak != -1){
            if (this->takdatavector[terugtak] <= nucapaciteit){
                nucapaciteit-=this->takdatavector[terugtak];
                this->verwijderVerbinding(naar,van);
                if (nucapaciteit > 0)
                    vergrootTak(van, naar, nucapaciteit);
            }else{
                this->takdatavector[terugtak]-=nucapaciteit;
            }
        }else
            vergrootTak(van, naar, padcapaciteit);
    }
}
void vergrootTak(int start, int eind, T delta){
        int taknr=this->verbindingsnummer(start,eind);
        if (taknr==-1)
            taknr=this->voegVerbindingToe(start,eind,delta);
        else
            this->takdatavector[taknr]+=delta;
}
T geefCapaciteit(){
    T som=0;
    for (typename GraafMetTakdata<GERICHT,T>::Knoop::const_iterator it=this->knopen[van].begin();
                it!=this->knopen[van].end();it++)
        som+=this->takdatavector[it->second];
    return som;
}
protected:
int van,naar;
};
#endif
