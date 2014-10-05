#ifndef RZWBOOM_H_INCLUDED
#define RZWBOOM_H_INCLUDED

#include <cstdlib>
#include <iostream>
using std::ostream;
using std::max;
using std::min;
using std::pair;
using std::cout;
using std::endl;
#include <queue>
#include <cassert>


template <class T,class D>
class Rzwboom;

template <class T,class D>
class Rzwknoop;


template <class T,class D>
class Rzwboom{
friend class Rzwknoop<T,D>;
const static int rood,zwart;
public:
    Rzwboom<T,D>(){
        k=0;
    }
    ~Rzwboom<T,D>(){
        delete k;
    }
//bottom-up toevoegen, geen duplicaten toegestaan.
//geeft false als de sleutel al in de boom zat.
//geldigeKleur=false: knoop wordt toegevoegd zonder op kleur te letten.
    bool voegtoe(const T&,const D&,bool geldigeKleur=true );
//volgende functie geeft false als de sleutel niet kan verwijderd
//worden omdat hij niet in de boom zit.
    bool verwijder(const T&);
    D* zoekdata(const T&);
    int diepte();
// << schrijft uit in level order.
    friend ostream& operator<<(ostream& os,Rzwboom<T,D>& b){
        b.schrijf(os);
        return os;
    }
//-1 is ongeldige boom; zwartediepte kan dus ook gebruikt worden
//om boom te controleren.
    int zwartediepte();

// recursief
// beter deze manier door recursie omdat je anders 2 dingen vraagt aan je kind
    pair<int, int> zwartediepterec();

    bool is_kleurbaar();

// recursief
// geeft dubbele pair terug <<min_zwarte_lengte,max_zwarte_lengte>, rzw bij min_zwarte_lengte>
// .first: Inwendige pair stelt zijn 'vork' (interval) van mogelijke zwarte lengtes voor
// .second: zwart default. Pas rood kleuren indien niet anders kan
    pair<pair<int,int>,int> is_kleurbaar_rec();

// kleurt de boom (indien hij kleurbaar is)
    void kleur();

//geeft de voorganger als de linkerboom niet leeg is
    Rzwboom<T,D>* ondervoorganger(Rzwknoop<T,D>*);
    bool ouderOK();
private:
// duwt rood in de deelboom
    void duw();

// corrigeert 2 keer rood na elkaar door wortel zwart te maken en rood te duwen naar beneden
    void corrigeer();

    void schrijf(ostream&);
    int geefkleur(){
        if (k!=0)
           return k->rzw;
        else
            return zwart;
    }
//Dit hoort op het eerste gezicht bij de klasse Rzwknoop.
//Maar dit kan niet omdat kn een nulpointer mag zijn
    void schrijf(ostream& os ,Rzwknoop<T,D>* kn);
//alleen roteer oproepen als de operatie kan!
    void roteer(bool naarlinks);
//maakzwart maakt de knoop in plaats->k zwart, en laat plaats wijzen naar
//volgende boom die een probleem kan opleveren bij bottom-up toevoegen.
    void maakzwart(Rzwboom<T,D>*& plaats);
//zoekknoop: postconditie: plaats wijst naar knoop met gezochte sleutel,
//                           of naar lege boom die naar die knoop zou wijzen als hij bestond
//                         ouder heeft waarde die in het ouderveld van de knoop staat/zou moeten staan
    void zoekknoop(const T&,Rzwboom<T,D>*& plaats,Rzwboom<T,D>*& ouder);

//gegevensveld
    Rzwknoop<T,D>* k;
};
template <class T,class D>
const int Rzwboom<T,D>::rood=0;
template <class T,class D>
const int Rzwboom<T,D>::zwart=1;

template <class T,class D>
class Rzwknoop{
    friend class Rzwboom<T,D>;
    public:
        T sl;
        D data;
        int rzw;
        Rzwboom<T,D>* ouder;//wijst naar de boom die naar de ouderknoop wijst
        Rzwboom<T,D> links,rechts;
        Rzwknoop<T,D>(const T& _sl,const D& _data):
                ouder(0),sl(_sl),data(_data),rzw(Rzwboom<T,D>::rood){}
};

template <class T,class D>
void Rzwboom<T,D>::kleur() {
    if( this->is_kleurbaar() ) {

        int diepte_links = this->k->links.zwartediepte();
        int diepte_rechts = this->k->rechts.zwartediepte();

        if( diepte_links != diepte_rechts ) {
            if( diepte_links > diepte_rechts ) {
                this->k->links.duw();   // links roder maken
            } else {
                this->k->rechts.duw();
            }
        } else {
            this->k->rzw = zwart;
        }
    } else {
        cout << "Niet inkleurbaar" << endl;
    }
}

// maakt de wortel van de boom rood
// indien al rood, wordt dit rood verder geduwd naar zijn kinderen
template <class T,class D>
void Rzwboom<T,D>::duw() {
    // wortel deelboom al rood = dubbel rood
    if( this->geefkleur() == rood ) {
        this->k->links.duw();
        this->k->rechts.duw();
    }
    //  controle 2 keer rood na elkaar
    else if ( this->k->links.geefkleur() == rood ) {
        this->k->links.corrigeer();
    }
    else if ( this->k->rechts.geefkleur() == rood ) {
        this->k->rechts.corrigeer();
    }
    else {
        this->k->rzw = rood;
    }
}

// bij 2 rode knopen na elkaar
// wortel zwart maken en rood duwen naar zijn kinderen
template <class T, class D>
void Rzwboom<T,D>::corrigeer() {
    this->k->rzw = zwart;
    this->k->links.duw();
    this->k->rechts.duw();
}

template <class T,class D>
int Rzwboom<T,D>::diepte() {

    if (this->k == 0) {
        return 1;
    } else {
        int diepte_links = this->k->links.diepte()+1;
        int diepte_rechts = this->k->rechts.diepte()+1;
        return (diepte_links > diepte_rechts)? diepte_links : diepte_rechts;
    }
}

template<class T, class D>
int Rzwboom<T,D>::zwartediepte() {
    if(k==0)
        return 1;
    else if(geefkleur() == rood && (k->rechts.geefkleur() == rood || k->links.geefkleur() == rood))
    {
        return -1;
    }
    else if((k->links.zwartediepte() != k->rechts.zwartediepte())|| k->links.zwartediepte() == -1) {
        return -1;
    }
    else return k->links.zwartediepte() + geefkleur();
}

// boom geeft zijn zwartediepte + of hij rood/zwart is
// zo kan zijn ouder checken of er 2 rode na elkaar zijn
// pair: zwartediepte , zwart/rood
template<class T, class D>
pair<int, int> Rzwboom<T,D>::zwartediepterec() {
    if(k==0)
    {
         return std::make_pair(1, zwart);
    }

    // First: zwarte diepte
    // Second: 0 = rood | 1 = zwart
    pair<int, int> zwl = k->links.zwartediepterec();
    pair<int, int> zwr = k->rechts.zwartediepterec();

    // verboden 2 rode knopen na elkaar
    if(geefkleur() == rood && (zwl.second == rood || zwr.second == rood ) )
    {
        return std::make_pair(-1, geefkleur());
    }
    // zwarte hoogte van kinderen moeten gelijk zijn
    else if((zwl.first != zwr.first) || zwl.first == -1) {
        return std::make_pair(-1, geefkleur());
    }

    else return std::make_pair(zwl.first + geefkleur(), geefkleur());
}

template <class T,class D>
bool Rzwboom<T,D>::is_kleurbaar() {

    return this->is_kleurbaar_rec().first.first != -1;
}

// geeft dubbele pair terug <<min_zwarte_lengte,max_zwarte_lengte>, rzw bij min_zwarte_lengte>
template <class T,class D>
pair<pair<int,int>,int> Rzwboom<T,D>::is_kleurbaar_rec() {
    if (this->k == 0) {
        //Knoop is null, dus boom is een blad. Blad is sowieso zwart dus min en max zijn 1.
        //return make_pair(make_pair(1,1),zwart);
        pair<int,int> vork(1,1);
        return pair<pair<int,int>, int> (vork,zwart);

    } else {
        // get lengt of child trees
        pair<pair<int,int>,int> antwoord_links, antwoord_rechts;
        antwoord_links = this->k->links.is_kleurbaar_rec();
        antwoord_rechts = this->k->rechts.is_kleurbaar_rec();
        int min_lengte_links = antwoord_links.first.first;
        int max_lengte_links = antwoord_links.first.second;
        int min_lengte_rechts = antwoord_rechts.first.first;
        int max_lengte_rechts = antwoord_rechts.first.second;
        int rzw_links = antwoord_links.second;
        int rzw_rechts = antwoord_rechts.second;

        // check if child-trees are impossible to make black-red
        if (min_lengte_links == -1 || min_lengte_rechts == -1 ) {
            //return make_pair(make_pair(-1,-1),zwart);
            pair<int,int> vork(-1,-1);
            return pair<pair<int,int>,int>(vork,zwart);
        }

        // intersectie beide intervallen
        int huidig_grens_min = max(min_lengte_rechts, min_lengte_rechts);
        int huidig_grens_max = min(max_lengte_links, max_lengte_rechts);
        // check geldigheid van intersectie
        if (huidig_grens_min > huidig_grens_max) {
            //return make_pair(make_pair(-1,-1),zwart);
            pair<int,int> vork(-1,-1);
            return pair<pair<int,int>,int>(vork,zwart);
        }

        //std::cout << std::endl << huidig_grens_min << " " << huidig_grens_max << std::endl;

        int min_lengte_rzw; // is afhankelijk van kleur van kind(eren) met kortste zwarte lengte
        huidig_grens_max++; // zichzelf zwart inkleuren

        // bepaal of linker- en/of rechterboom verantwoordelijk zijn voor minimum zwarte lengte
        // afhankelijk van die zijn kleur moeten we de minimum lengte van onze boom aanpassen

        // links en rechts zelfde minimum
        if( huidig_grens_min == min_lengte_links && huidig_grens_min == min_lengte_rechts ) {
            // nu kijken naar hun kleur
            // indien één rood, dan moet onze minimum zwarte lengte verhoogd worden
            if( rzw_links == rood || rzw_rechts == rood ) {
                pair<int,int> vork(huidig_grens_min++,huidig_grens_max);
                return pair<pair<int,int>,int>(vork,zwart);
            }
            else {
                pair<int,int> vork(huidig_grens_min,huidig_grens_max);
                // we kleuren hem rood, want minimale zwarte lengte = afwisselend zwart-rood
                return pair<pair<int,int>,int>(vork,rood);
            }
        }
        else if ( huidig_grens_min == min_lengte_links ) {
            if (rzw_links == rood) {
                //return make_pair(make_pair(huidig_grens_min++, huidig_grens_max),zwart);
                pair<int,int> vork(huidig_grens_min++,huidig_grens_max);
                return pair<pair<int,int>,int>(vork,zwart);
            } else {
                //return make_pair(make_pair(huidig_grens_min, huidig_grens_max),rood);
                pair<int,int> vork(huidig_grens_min,huidig_grens_max);
                return pair<pair<int,int>,int>(vork,rood);
            }
        } else {
            if (rzw_rechts == rood) {
                //return make_pair(make_pair(huidig_grens_min++, huidig_grens_max),zwart);
                pair<int,int> vork(huidig_grens_min++,huidig_grens_max);
                return pair<pair<int,int>,int>(vork,zwart);
            } else {
                //return make_pair(make_pair(huidig_grens_min, huidig_grens_max),rood);
                pair<int,int> vork(huidig_grens_min,huidig_grens_max);
                return pair<pair<int,int>,int>(vork,rood);
            }
        }
    }
}

template <class T,class D>
void Rzwboom<T,D>::roteer(bool naarlinks){
    Rzwknoop<T,D>* op;
    Rzwknoop<T,D>* neer=k;
    if (naarlinks){
        op=k->rechts.k;
        if (neer->links.k!=0)
            neer->links.k->ouder=&(op->links);
        neer->rechts.k=op->links.k;
        if (op->links.k!=0){
            Rzwknoop<T,D>* kind=op->links.k;
            kind->ouder=&(op->links);
            if (kind->links.k!=0)
                kind->links.k->ouder=&(neer->rechts);
            if (kind->rechts.k!=0)
                kind->rechts.k->ouder=&(neer->rechts);
        }
        if (op->rechts.k!=0)
            op->rechts.k->ouder=this;
        op->links.k=neer;
    }
    else{
        op=k->links.k;
        if (neer->rechts.k!=0)
            neer->rechts.k->ouder=&(op->rechts);
        neer->links.k=op->rechts.k;
        if (op->links.k!=0)
            op->links.k->ouder=this;
        if (op->rechts.k!=0)
            op->rechts.k->ouder=&(op->rechts);
        if (op->rechts.k!=0){
            Rzwknoop<T,D>* kind=op->rechts.k;
            kind->ouder=&(op->rechts);
            if (kind->links.k!=0)
                kind->links.k->ouder=&(neer->links);
            if (kind->rechts.k!=0)
                kind->rechts.k->ouder=&(neer->links);
        }
        op->rechts.k=neer;
    }
    k=op;
    op->ouder=neer->ouder;
    neer->ouder=this;
}



template <class T,class D>
void Rzwboom<T,D>::zoekknoop(const T& sl,Rzwboom<T,D>*& plaats,
                                         Rzwboom<T,D>*& ouder){
    plaats=this;
    ouder=0;
    while (plaats->k!=0 && plaats->k->sl!=sl){
        ouder=plaats;
        if (sl<plaats->k->sl)
            plaats=&(plaats->k->links);
        else
            plaats=&(plaats->k->rechts);
    }
}

template <class T,class D>
D* Rzwboom<T,D>::zoekdata(const T& sl){
    Rzwboom<T,D>* plaats;
    Rzwboom<T,D>* ouder;//dummy, eigenlijk overbodig bij zoekdata
    zoekknoop(sl,plaats,ouder);
    if (plaats->k==0)
        return 0;
    else return &(plaats->k->data);
}

template <class T,class D>
void Rzwboom<T,D>::maakzwart(Rzwboom<T,D>*& plaats){
    Rzwboom<T,D>* kind=plaats;
    Rzwboom<T,D>* ouder=kind->k->ouder;
    Rzwboom<T,D>* grootouder=ouder->k->ouder;
    if (grootouder->k->links.geefkleur()==rood && grootouder->k->rechts.geefkleur()==rood){
        grootouder->k->rzw=rood;
        grootouder->k->links.k->rzw=zwart;
        grootouder->k->rechts.k->rzw=zwart;
    }
    else {//geval 1
        bool ouderlinks=(ouder==&(grootouder->k->links));
        bool kindlinks=(kind==&(ouder->k->links));
        if (kindlinks!=ouderlinks){//geval 1b
            if (ouderlinks)
                grootouder->k->links.roteer(true);
            else
                grootouder->k->rechts.roteer(false);
        };
        //geval 1a
        grootouder->k->rzw=rood;
        ouder->k->rzw=zwart;
        grootouder->roteer(!ouderlinks);
    }
    plaats=grootouder;
}

//bottom up
template <class T,class D>
bool Rzwboom<T,D>::voegtoe(const T& sl,const D& data, bool geldigeKleur){
    Rzwboom<T,D>* plaats;
    Rzwboom<T,D>* ouder;
    zoekknoop(sl,plaats,ouder);
    bool nietgevonden=plaats->k==0;
    if (nietgevonden){
        plaats->k=new Rzwknoop<T,D>(sl,data);
        plaats->k->ouder=ouder;
//noot: ouder wijst nooit naar een ledige boom.
        if (geldigeKleur){
            bool dubbelrood=(ouder!=0 && ouder->k->rzw==rood);
            while (dubbelrood){
                if (sl==18){
                    std::cout<<"plaats->k->sl== "<<plaats->k->sl;
                    std::cout<<"ouder->k->sl== "<<ouder->k->sl;
                    std::cout<<'\n';
                }
                maakzwart(plaats);
                assert(plaats->k!=0);
                ouder=plaats->k->ouder;
                dubbelrood=(plaats->k->rzw==rood && ouder !=0
                                              && ouder->k->rzw==rood);
            }
            k->rzw=zwart;//eventueel wortel zwart maken.
        }
    }
    return nietgevonden;
}


template <class T,class D>
void Rzwboom<T,D>::schrijf(ostream& os){
    if (k!=0){
       std::queue<Rzwknoop<T,D>*, std::deque<Rzwknoop<T,D>*> > q;
       q.push(k);
       while(!q.empty()){
           Rzwknoop<T,D>* nu=q.front();
           schrijf(os,nu);
           os<<" links: ";
           schrijf(os,nu->links.k);
           os<<" rechts: ";
           schrijf(os,nu->rechts.k);
           os<<" ouder: ";
           if (nu->ouder==0)
               schrijf(os,0);
           else
               schrijf(os,nu->ouder->k);
           os<<std::endl;
           if (nu->links.k!=0)
               q.push(nu->links.k);
           if (nu->rechts.k!=0)
               q.push(nu->rechts.k);
           q.pop();
       }
    }
    else{
        schrijf(os,k);
    }
}

template <class T,class D>
void Rzwboom<T,D>::schrijf(ostream& os ,Rzwknoop<T,D>* kn){
    if (kn!=0)
        os<<
        (kn->rzw==rood?
            "rood ":"zwart")
        <<"("<<kn->sl<<","<<kn->data<<")";
    else
        os<<"---";
}


#endif // RZWBOOM_H_INCLUDED
