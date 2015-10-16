//
// Created by Brecht Van de Vyvere on 12/10/15.
//

#ifndef LINEAR_HASHING_BLOKLIJST_H
#define LINEAR_HASHING_BLOKLIJST_H

#include <iostream>
#include <vector>
#include "schijf.h"

using std::vector;
using std::ostream;
using std::cout;
using std::endl;
using std::pair;

typedef unsigned int blokindex;

template<class Sleutel, class Data>
class Schijfpagina {
public:
    Schijfpagina<Sleutel, Data>() {
        // Volgende pagina bestaat nog niet
        _volgende = 0;
    }

    ~Schijfpagina<Sleutel, Data>() { }

    void voegtoe(Sleutel sl_, Data d_) {
        pair<Sleutel, Data> p(sl_, d_);
        _gegevens.push_back(p);
    }

    bool isVol() {
       return _gegevens.size() == CAPACITEIT;
    }

    blokindex geefBlokIndexVolgendeSchijfpagina() {
        return _volgende;
    };

    void zetBlokIndexVolgendeSchijfpagina(blokindex bi) {
        _volgende = bi;
    }

    void schrijf(ostream &ostream);

private:
    int CAPACITEIT = 1;
    vector<pair<Sleutel, Data>> _gegevens;
    blokindex _volgende;
};

template<class Sleutel, class Data>
void Schijfpagina<Sleutel, Data>::schrijf(ostream &ostream) {
    for (int i=0; i<_gegevens.size(); i++) {
        ostream << "<" << _gegevens[i].first << ", " << _gegevens[i].second << "> ";
    }
}

/*
 *  Bloklijst is gelinkte lijst waarvan de knopen Schijfpagina's zijn.
 *
 */
template<class Sleutel, class Data>
class Bloklijst {
public:
    ~Bloklijst<Sleutel, Data>() { }

    Bloklijst<Sleutel, Data>(Schijf<Schijfpagina<Sleutel, Data>> & schijf_) : _schijf(schijf_) {
        // Nieuwe lege schijfpagina aanmaken
        Schijfpagina<Sleutel, Data> pag;

        // Wegschrijven naar schijf
        _blokindex = _schijf.schrijf(pag);
    }

    void voegtoe(Sleutel sl_, Data d_);

    void schrijf(ostream &) const;

    friend ostream &operator<<(ostream &os, const Bloklijst<Sleutel, Data> &lijst) {
        lijst.schrijf(os);
        return os;
    };
private:
    Schijf<Schijfpagina<Sleutel, Data>> & _schijf;
    blokindex _blokindex; // verwijst naar de eerste knoop (=Schijfpagina)

};

template<class Sleutel, class Data>
void Bloklijst<Sleutel, Data>::voegtoe(Sleutel sl_, Data d_) {
    //Toevoegen van nieuwe schijfpagina's als alle pagina's uit de lijst vol zijn, gebeurt achteraan.
    //Let erop dat alle informatie op de schijf moet bewaard worden.
    // Nadat een operatie (zoeken, toevoegen, ...) is uitgevoerd moeten alle pagina's op de schijf staan.
    // Je moet ook veronderstellen dat een pagina groot is: je mag nooit meer dan twee pagina's in het `geheugen' (dus: buiten de schijf) hebben.
    // Deze moeten in statisch aangemaakte variabelen binnen de functie zitten, zodat ze verdwijnen als de functie is uitgevoerd.

    // 1) Eerste schijfpagina ophalen
    Schijfpagina<Sleutel, Data> wijzer;
    _schijf.lees(wijzer, _blokindex);

    blokindex huidigeBi = _blokindex;
    blokindex volgendeBi = wijzer.geefBlokIndexVolgendeSchijfpagina();
    while (wijzer.isVol() && volgendeBi != 0) {
        _schijf.lees(wijzer, volgendeBi);
        huidigeBi = volgendeBi;
        volgendeBi = wijzer.geefBlokIndexVolgendeSchijfpagina();
    }

    // Ofwel is hij gestopt, omdat schijfpagina dat wijzer naar wijst niet vol is
    if (!wijzer.isVol()) {
        wijzer.voegtoe(sl_, d_);
        _schijf.herschrijf(wijzer, huidigeBi);
    } else {
    // Ze allemaal vol. We moeten nieuwe schijfpagina toevoegen
        Schijfpagina<Sleutel, Data> nieuwePagina;
        nieuwePagina.voegtoe(sl_, d_);

        // Wegschrijven
        blokindex bi = _schijf.schrijf(nieuwePagina);

        wijzer.zetBlokIndexVolgendeSchijfpagina(bi);

        _schijf.herschrijf(wijzer, huidigeBi);
    }
}

template<class Sleutel, class Data>
void Bloklijst<Sleutel, Data>::schrijf(ostream &os) const {
    Schijfpagina<Sleutel, Data> wijzer;
    _schijf.lees(wijzer, _blokindex);
    os << "Schijfpagina met blokindex " << _blokindex << endl;
    wijzer.schrijf(os);
    os << endl;

    while (wijzer.geefBlokIndexVolgendeSchijfpagina() != 0) {
        blokindex bi = wijzer.geefBlokIndexVolgendeSchijfpagina();
        os << "Schijfpagina met blokindex " << bi << endl;
        _schijf.lees(wijzer, wijzer.geefBlokIndexVolgendeSchijfpagina());
        wijzer.schrijf(os);
        os << endl;
    }

    os << endl;
};

#endif //LINEAR_HASHING_BLOKLIJST_H
