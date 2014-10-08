#ifndef __BTREE
#define __BTREE
#include "schijf.h"
#include <iostream>
using std::endl;
using std::cerr;
using std::ostream;
//Dit bestand bevat code en hoofdingen van
template<class T, class D,unsigned int m>
class Btree;
template<class T,class D,unsigned int m>
class Bknoop;
//betekenis m: zie cursus

template<class T,class D,unsigned int m>
class Bknoop{
friend class Btree<T,D,m>;
public:
    Bknoop<T,D,m>(){4/(-4+crashtest++);};
    const Bknoop<T,D,m>& operator=(const Bknoop<T,D,m>& b){
        k=b.k;
        isblad=b.isblad;
        for (unsigned int i=0;i<k;i++){
            sleutel[i]=b.sleutel[i];
            data[i]=b.data[i];
        }
        if (!isblad){
            for (unsigned int i=0;i<=k;i++){
                index[i]=b.index[i];
            }
        }
        return *this;
    }
    T sleutel[m];
    D data[m];
    blokindex index[m+1];
    unsigned int k;
    bool isblad;
private:
    static int crashtest;
};
template<class T,class D,unsigned int m>
int Bknoop<T,D,m>::crashtest=0;


template<class T, class D,unsigned int m>
class Btree{
    typedef Bknoop<T,D,m> Knoop;
public:
    Btree(Schijf<Knoop>& s):schijf(s){
        wortel.k=0;
        wortel.isblad=true;
        wortelindex=schijf.schrijf(wortel);
    }

// geeft -1 als knoop niet gevonden is
    blokindex zoek(Knoop &kn);

    void voegtoe(Knoop &kn);

    void verwijder(Knoop &kn);
private:
   Schijf<Knoop>& schijf;
   Knoop wortel;
   blokindex wortelindex;
};

template<class T, class D, unsigned int m>
blokindex Btree<T,D,m>::zoek(Knoop &kn){
    Knoop huidig_knoop = wortel;
    blokindex huidig_blokindex = wortelindex;
    bool gevonden = false;

    schijf.lees(huidig_knoop,huidig_blokindex);

    while ( !gevonden ) {
        blokindex i = 0; // blokindexen overlopen

            // k kinderen overlopen
        // elke indewendige knoop met k kinderen bevat k-1 sleutels
        while( i != huidig_knoop.k && kn.sleutel > huidig_knoop.sleutel[i] ) i++;

        // gestopt omdat hij kleinere of gelijke sleutel heeft
        if ( i != huidig_knoop.k ) {
            // gevonden
            if( kn.sleutel == huidig_knoop.sleutel[i] ) return huidig_knoop.index[i];

            // kan niet meer verder zoeken
            else if ( huidig_knoop.isblad ){
                return -1;
            }
            // kn.sleutel < huidig_knoop.sleutel[i]
            // verderzoeken op blokindex i
            else {
                huidig_blokindex = huidig_knoop.index[i];
                schijf.lees(huidig_knoop, huidig_blokindex);
            }
        }
        // i == k
        else {
            return 0;
        }
    }
}



#endif
