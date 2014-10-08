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

    void voegtoe(const T& sleutel, const D& data, const blokindex bi);

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
    blokindex zoek(const T& sleutel, const T& data);

    void voegtoe(const T& sleutel, const T& data);

    void verwijder(const T& sleutel, const T& data);

    void split(Knoop& kind, stack<blokindex> pad);

private:
   Schijf<Knoop>& schijf;
   Knoop wortel;
   blokindex wortelindex;
};

template<class T, class D, unsigned int m>
blokindex Btree<T,D,m>::zoek(const T& sleutel, const T& data){
    Knoop huidig_knoop = wortel;
    blokindex huidig_blokindex = wortelindex;
    bool gevonden = false;

    // wortel moet niet meer in geheugen gelezen worden

    while ( !gevonden ) {
        blokindex i = 0; // blokindexen overlopen

        // sleutel zoeken in gerangschikte tabel met sleutels
        while( i != huidig_knoop.k && sleutel > huidig_knoop.sleutel[i] ) i++;

        if ( i != huidig_knoop.k ) {
            // gevonden
            if( sleutel == huidig_knoop.sleutel[i] ) return huidig_knoop.index[i];

            // kan niet meer verder zoeken
            else if ( huidig_knoop.isblad ){
                return -1;
            }
            // kn.sleutel < huidig_knoop.sleutel[i]
            // bij interne knoop verder zoeken in de juiste deelboom,
            // waarvan de wortel een kind is van de huidige knoop
            else {
                // wijzer naar kind heeft dzelfde index in de kindertabel als waar
                // de niet gevonden sleutel zou moeten staan in de sleuteltabel
                huidig_blokindex = huidig_knoop.index[i];
                // inlezen in geheugen
                schijf.lees(huidig_knoop, huidig_blokindex);
            }
        }
        // i == k
        else {
            return -1;
        }
    }
}

template<class T, class D, unsigned int m>
void Btree<T,D,m>::voegtoe(const T& sleutel, const T& data){
// toevoegen gebeurt steeds aan een blad

// vanuit wortel zoeken we blad waarin de sleutel zou moeten zitten en voegen hem toe
    Knoop huidig_knoop = wortel;
    blokindex huidig_blokindex = wortelindex;

    stack<blokindex> pad; // gebruikt voor ouders terug te vinden, indien gesplit moet worden
    pad.push(huidig_blokindex);

    // wortel moet niet meer in geheugen gelezen worden

    while ( !huidig_knoop.isblad ) {
        blokindex i = 0; // blokindexen overlopen

        // sleutel zoeken in gerangschikte tabel met sleutels
        while( i < huidig_knoop.k && sleutel > huidig_knoop.sleutel[i] ) i++;

        if ( i >= huidig_knoop.k ) {
            // wijzer naar kind heeft dzelfde index in de kindertabel als waar
            // de niet gevonden sleutel zou moeten staan in de sleuteltabel
            huidig_blokindex = huidig_knoop.index[i];
            pad.push(huidig_blokindex);
            // inlezen in geheugen
            schijf.lees(huidig_knoop, huidig_blokindex);
        }
    }

    // vol -> splitsen
    if ( !huidig_knoop.k <= m-1 ) {
        split(huidig_knoop, huidig_blokindex, pad);
    }

    // genoeg plaats
    // sleutels opschuiven
    // er zijn k sleutels aanwezig -> k+1 indexen/kinderen
    for(int v=huidig_knoop.k; v>i; v--) {
        huidig_knoop.sleutel[v] = huidig_knoop.sleutel[v-1];
        huidig_knoop.data[v] = huidig_knoop.data[v-1];
        huidig_knoop.index[v+1] = huidig_knoop.index[v];
    }

    // knoop toevoegen
    huidig_knoop.sleutel[i] = sleutel;
    huidig_knoop.data[i] = data;

    schijf.herschrijf(huidig_knoop, huidig_blokindex);
}

template<class T, class D, unsigned int m>
void Btree<T,D,m>::split(Knoop &kind, blokindex kind_index, stack<blokindex> pad) {
// zolang overflow in ouder is, blijven splitten
// of tot wortel moet splitten

    bool overflow = true;

    Knoop ouder;
    unsigned int midden = m/2;
    blokindex ouder_index = pad.top();
    schijf.lees(ouder, ouder_index);
    pad.pop();

    while ( overflow && !pad.empty() ) {
        Knoop broer;
        broer.k = kind.k - midden;
        for (unsigned int i = midden; i < kind.k; i++) {
            broer.sleutels[i - midden] = knoop.sleutels[i];
            broer.data[i - midden] = knoop.data[i];
            if (!kind.isblad) {
                broer.index[i - midden] = knoop.index[i];
            }
        }

        blokindex blokindex_broer = schijf.schrijf(broer);

        // voeg midden toe bij ouder
        // de twee nieuwe knopen toevoegen als kinderen van ouder
        ouder.voegtoe(kind.sleutel[kind.k-1], kind.data[kind.k-1], blokindex_broer);

        // voor de helft maar vol - 1 die naar ouder gegaan is
        kind.k = midden-1;

        schijf.herschrijf(kind, kind_index);

        kind = ouder;
        kind_index = ouder_index;
        schijf.lees(ouder, pad.pop());
        overflow = ( kind.k == m ? true : false );
    }
}

template<class T, class D, unsigned int m>
void Bknoop<T,D,m>::voegtoe(const T& sleutel, const D& data, const blokindex bi) {
    // Zoek waar de sl moet komen
    blokindex i = 0;
    while (i < k && sleutels[i] < key) {
        i++;
    }

    // Schuif alles erachter 1 plaats op.
    for (blokindex v = k; v > i; v--) {
        sleutels[v] = sleutels[v - 1];
        data[v] = data[v - 1];
        if (!isblad) {
            index[v + 1] = index[v];
        }
    }

    // Plaats de sl daar.
    sleutels[i] = key;
    data[i] = val;
    if (!isblad && bi != 0) {
        index[i + 1] = bi;
    }
    k++;
    return i;
}

#endif
