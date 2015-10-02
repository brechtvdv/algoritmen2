/**********************************************************************

   
   beschrijving: Deze code bevat fouten !!!!!!!!!!!!!!!!
   en C++11-features
   
***************************************************************************/
#ifndef __ZOEKBOOM_H
#define __ZOEKBOOM_H

#include <cstdlib>
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

using std::ostream;
using std::unique_ptr;
using std::max;
using std::vector;

/**********************************************************************

   Klasse: Binboom met Binknoop: binaire boom
   
   beschrijving: Domme klasse om de gegevens van een boom te bevatten
                 Omdat ze enkel in een wrapper wordt gebruikt, heeft ze
                 alles publiek staan. Ze mag dan ook nooit buiten een
                 wrapper gebruikt worden!
   
***************************************************************************/

template<class Sleutel, class Data>
class Binknoop;

template<class Sleutel, class Data>
class Binboom : public unique_ptr<Binknoop<Sleutel, Data>> {
public:
    using unique_ptr<Binknoop<Sleutel, Data>>::unique_ptr;

    Binboom<Sleutel, Data>() { }

    ~Binboom<Sleutel, Data>() { }

    Binboom<Sleutel, Data>(Binboom<Sleutel, Data> &&b) : unique_ptr<Binknoop<Sleutel, Data>>(move(b)) {
    }

    Binboom<Sleutel, Data> &operator=(Binboom<Sleutel, Data> &&b) {
        unique_ptr<Binknoop<Sleutel, Data>>::operator=(move(b));
        return *this;
    }

    int diepte() const {
        if (!*this)
            return 0;
        else
            return max((*this)->links.diepte(), (*this)->rechts.diepte()) + 1;
    };

    void gemiddeldeDiepteUtil(vector<int>* v, int diepte);

    void schrijf(ostream &) const;

    void schrijf(ostream &os, Binknoop<Sleutel, Data> *kn) const {
        if (kn != 0)
            os << "(" << kn->sl << "," << kn->data << ")";
        else
            os << "(,)";
    }

    void roteer(bool links);
};

template<class Sleutel, class Data>
class Binknoop {
public:
    Sleutel sl;
    Data data;
    Binknoop<Sleutel, Data> *ouder;
    Binboom<Sleutel, Data> links, rechts;

    Binknoop() : ouder(0) { }

    Binknoop(const Sleutel &_sl, const Data &_data) : ouder(0), sl(_sl), data(_data) { }
};

/**********************************************************************

   klasse: Zoekboom
   
   beschrijving: Dit is een wrapper voor een Binboom,
                 die ervoor zorgt dat de sleutels in de Binboom
                 op volgorde staan
   
***************************************************************************/

template<class Sleutel, class Data>
class Zoekboom {
public:
    Zoekboom<Sleutel, Data>() {};
    ~Zoekboom<Sleutel, Data>() {};

    virtual void voegtoe(const Sleutel &, const Data &);

    void voegtoe(Binboom<Sleutel, Data> &knoop, const Sleutel &sl, const Data &data);

//volgende functie doet niets als er geen knoop is met het gegeven Sleutel
    virtual void verwijder(const Sleutel &);

//geef pointer naar data horend bij een sleutel
    virtual Data *zoekdata(const Sleutel &);

    virtual Data *zoekdatametsplay(const Sleutel &);

    int diepte() const { return deBinboom.diepte(); };

    friend ostream &operator<<(ostream &os, Zoekboom<Sleutel, Data> &b) {
        b.deBinboom.schrijf(os);
        return os;
    };

    // Diepte naar elke blad gedeeld door aantal bladeren
    double gemiddeldeDiepte();

protected:
//zoekplaats: geeft adres van boom waaraan knoop hangt, of zou moeten hangen
//en adres van de ouder.
    virtual void zoekplaats(const Sleutel &, Binboom<Sleutel, Data> *&, Binknoop<Sleutel, Data> *&ouder);

    virtual void zoekplaatsmetsplay(const Sleutel &, Binboom<Sleutel, Data> *&);


//De binaire boom die de data bevat
    Binboom<Sleutel, Data> deBinboom;

//geeft de voorganger. Veronderstelt dat de linkerboom onder de knoop niet leeg is
    Binboom<Sleutel, Data> * ondervoorganger(Binboom<Sleutel, Data> *);
};

template<class Sleutel, class Data>
void Binboom<Sleutel, Data>::roteer(bool links) {
    Binboom<Sleutel, Data> op;
    if (links) {
        op = move((*this)->rechts);
        (*this)->rechts = move(op->links);
        if ((*this)->rechts != nullptr)
            (*this)->rechts->ouder = (*this).get();
        op->links = move(*this);
        *this = move(op);
        (*this)->ouder = (*this)->links->ouder;
        (*this)->links->ouder = (*this).get();
    }
    else {
        op = move((*this)->links);
        (*this)->links = move(op->rechts);
        if ((*this)->links != nullptr)
            (*this)->links->ouder = (*this).get();
        op->rechts = move(*this);
        *this = move(op);
        (*this)->ouder = (*this)->rechts->ouder;
        (*this)->rechts->ouder = (*this).get();
    }
}

template<class Sleutel, class Data>
void Binboom<Sleutel, Data>::gemiddeldeDiepteUtil(vector<int>* v, int diepte) {
    // std::cout << this->get()->sl << " - " << diepte << std::endl;
    // Indien geen lege boom
    if(this->get() != nullptr) {
        if (this->get()->rechts == 0 && this->get()->links == 0) {
            v->push_back(diepte);
        } else {
            if (this->get()->links) {
                this->get()->links.gemiddeldeDiepteUtil(v, diepte + 1);
            }
            if (this->get()->rechts) {
                this->get()->rechts.gemiddeldeDiepteUtil(v, diepte + 1);
            }
        }
    }
};

template<class Sleutel, class Data>
double Zoekboom<Sleutel, Data>::gemiddeldeDiepte() {
    vector<int> diepteVector;
    int diepte = 0;

    deBinboom.gemiddeldeDiepteUtil(&diepteVector, diepte);

    double som = 0.0;
    // Bereken som van dieptes / aantal
    for (int i=0; i<diepteVector.size(); i++) {
        som += diepteVector[i];
    }

    return som/diepteVector.size();
};

template<class Sleutel, class Data>
void Zoekboom<Sleutel, Data>::zoekplaats(const Sleutel &sl, Binboom<Sleutel, Data> *&plaats,
                                         Binknoop<Sleutel, Data> *&ouder) {
    plaats = &deBinboom;
    ouder = 0;
    while (*plaats != 0 && (*plaats)->sl != sl) {
        ouder = plaats->get();
        if (sl < (*plaats)->sl)
            plaats = &((*plaats)->links);
        else
            plaats = &((*plaats)->rechts);
    }
}

template<class Sleutel, class Data>
Data *Zoekboom<Sleutel, Data>::zoekdata(const Sleutel &sl) {
    Binboom<Sleutel, Data> *plaats;
    Binknoop<Sleutel, Data> *ouder;
    zoekplaats(sl, plaats, ouder);
    if (plaats == 0)
        return 0;
    else return &((*plaats)->data);
}

template<class Sleutel, class Data>
Data *Zoekboom<Sleutel, Data>::zoekdatametsplay(const Sleutel &sl) {
    Binboom<Sleutel, Data> *plaats = &deBinboom;
    zoekplaatsmetsplay(sl, plaats);
    if (plaats == 0)
        return 0;
    else return &((*plaats)->data);
}

template<class Sleutel, class Data>
void Zoekboom<Sleutel, Data>::zoekplaatsmetsplay(const Sleutel &sl, Binboom<Sleutel, Data> *&plaats) {
    // Als je in een lege boom zit, of in de boom waarvan de wortel de gezochte sleutel heeft, stop.
    if (plaats == 0 || (*plaats)->sl == sl) {

    } else {
        // Als de gezochte sleutel kleiner is dan de sleutel in de wortel, roteer naar rechts.
        if (sl < (*plaats)->sl) {
            plaats->roteer(false);
        } else {
            plaats->roteer(true);
        }
        if (sl == (*plaats)->sl) {
            // gevonden dus niet meer verderzoeken
        } else if (sl < (*plaats)->sl) {
            plaats = &((*plaats)->links);
            zoekplaatsmetsplay(sl, plaats);
        } else {
            // Als de gezochte sleutel daarmee naar rechts geroteerd is ga naar de rechter deelboom.
            plaats = &((*plaats)->rechts);
            zoekplaatsmetsplay(sl, plaats);
        }
    }
}

template<class Sleutel, class Data>
void Zoekboom<Sleutel, Data>::voegtoe(const Sleutel &sl, const Data &data) {
    if (deBinboom == 0) {
        unique_ptr <Binknoop<Sleutel, Data>> nieuw = unique_ptr<Binknoop<Sleutel, Data>>(
                new Binknoop<Sleutel, Data>(sl, data));
        deBinboom = move(nieuw);
        deBinboom->ouder = 0;
    }
    else
        voegtoe(deBinboom, sl, data);
}

template<class Sleutel, class Data>
void Zoekboom<Sleutel, Data>::voegtoe(Binboom<Sleutel, Data> &knoop, const Sleutel &sl, const Data &data) {
    Binboom<Sleutel, Data> *kind;
    if (sl < knoop->sl)
        kind = &(knoop->links);
    else
        kind = &(knoop->rechts);
    if (*kind == 0) {
        (*kind) = move((unique_ptr < Binknoop<Sleutel, Data>>) new Binknoop<Sleutel, Data>(sl, data));
        (*kind)->ouder = knoop.get();
    }
    else
        voegtoe(*kind, sl, data);
}

template<class Sleutel, class Data>
void Zoekboom<Sleutel, Data>::verwijder(const Sleutel &sl) {
    // throw "verwijder nog niet aangepast aan C++11: extra oefening";

    Binboom<Sleutel,Data>* weg;
    Binknoop<Sleutel,Data>* ouder;
    zoekplaats(sl,weg,ouder);
    if (weg != 0){
//        if ((*weg)->links==0){
//            (*weg)->rechts->ouder=ouder; // ouder van kind eerst aanpassen zodat we geen extra pointer moeten gebruiken
//            (*weg)->rechts = move(weg);
//        }
//        else if ((*weg)->rechts==0){
//            (*weg)->links->ouder=ouder;
//            (*weg)->links = move(weg);
//        }
//        else{
            //vervangen door voorganger
//            Binboom<Sleutel,Data>* voorlink=ondervoorganger(weg);
//            Binknoop<Sleutel,Data>* voorganger=voorlink;
//            if (voorlink!=&(weg->links)){
//                voorlink=voorganger->links;
//                if (voorganger->links !=0)
//                    voorganger->links->ouder=voorganger->ouder;
//                //geen test voor volgende twee: deze bestaan!
//                weg=voorganger;
//                voorganger->ouder=ouder;
//                voorganger->links=weg->links;
//                voorganger->links->ouder=voorganger;
//                voorganger->rechts=weg->rechts;
//                voorganger->rechts->ouder=voorganger;
//            }
//            else{
//                voorganger->rechts.k=weg->rechts;
//                weg->rechts.k->ouder=voorganger;
//                voorganger->ouder=weg->ouder;
//                plaats->k=voorganger;
//            }
//            weg->links=0;
//            weg->rechts=0;
//            delete weg;
       // }
    }
}

template<class Sleutel, class Data>
Binboom<Sleutel, Data>* Zoekboom<Sleutel, Data>::ondervoorganger(Binboom<Sleutel, Data>* kn) {
    Binboom<Sleutel, Data> * onder = kn->links->get();
    while (onder->rechts != 0)
        onder = onder->rechts->get();
    return onder;
}


template<class Sleutel, class Data>
void Binboom<Sleutel, Data>::schrijf(ostream &os) const {
    if (*this != 0) {
        Binknoop<Sleutel, Data> *loper = this->get();
        std::queue<Binknoop<Sleutel, Data> *, std::deque<Binknoop<Sleutel, Data> *> > q;
        q.push(loper);
        while (!q.empty()) {
            Binknoop<Sleutel, Data> *nu = q.front();
            schrijf(os, nu);
            os << " links: ";
            schrijf(os, nu->links.get());
            os << " rechts: ";
            schrijf(os, nu->rechts.get());
            os << " ouder: ";
            schrijf(os, nu->ouder);
            os << std::endl;
            if (nu->links != 0)
                q.push(nu->links.get());
            if (nu->rechts != 0)
                q.push(nu->rechts.get());
            q.pop();
        }
    }
    else {
        os << " XX ";
    }
}


#endif

