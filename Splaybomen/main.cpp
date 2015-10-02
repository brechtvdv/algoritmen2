#include <iostream>
#include "zoekboom_Cpp11.h"
#include <cassert>
#include <cstdlib>

using namespace std;

void test_voegtoe() {
    Zoekboom<int,int> zb;

    zb.voegtoe(5,1);
    zb.voegtoe(3,1);
    zb.voegtoe(4,1);
    zb.voegtoe(2,1);
    zb.voegtoe(0,1);
    zb.voegtoe(10,1);
    zb.voegtoe(9,1);
    zb.voegtoe(8,1);
    zb.voegtoe(7,1);

    cout << "Zoekboom: " << zb << endl;
}

void test_zoekdata() {
    Zoekboom<int, int> zb;

    zb.voegtoe(5,1000);
    zb.voegtoe(10,1);

    // Zoek de data van knoop met sleutel 5
    zb.zoekdata(5);
    assert(*zb.zoekdata(5) == 1000);

    zb.zoekdata(10);
    assert(*zb.zoekdata(10) == 1);
}

void test_diepte() {
    Zoekboom<int,int> zb;

    zb.voegtoe(5,1);
    zb.voegtoe(3,1);
    zb.voegtoe(4,1);
    zb.voegtoe(2,1);
    zb.voegtoe(0,1);
    zb.voegtoe(10,1);
    zb.voegtoe(9,1);
    zb.voegtoe(8,1);
    zb.voegtoe(7,1);

    // Diepte van boom moet 5 zijn
    assert(zb.diepte() == 5);
}

void test_verwijder() {
    Zoekboom<int,int> zb;

    zb.voegtoe(5,1);
    zb.voegtoe(3,1);
    // zb.voegtoe(4,1);

    cout << "Voor: " << zb << endl;

    // verwijder knoop met sleutel 3
    zb.verwijder(5);

    cout << "Na: " << zb << endl;

}

void test_voorganger() {
    Zoekboom<int,int> zb;

    // Data bevat inorder nummer
    // Voorganger is knoop met inorder-nr eentje kleiner
    zb.voegtoe(4,1);
    zb.voegtoe(6,2);
    zb.voegtoe(7,3);
    zb.voegtoe(5,4);
    zb.voegtoe(10,5);
    zb.voegtoe(11,6);
    zb.voegtoe(15,7);
    zb.voegtoe(17,8);
    zb.voegtoe(18,9);
    zb.voegtoe(20,10);
    zb.voegtoe(25,11);
    zb.voegtoe(27,12);
    zb.voegtoe(26,13);
    zb.voegtoe(28,14);

    // cout << zb << endl;

    // zb.ondervoorganger()
}

void test_gemiddelde_diepte() {
    Zoekboom<int,int> zb;

    zb.voegtoe(5,1);
    zb.voegtoe(3,1);
    zb.voegtoe(4,1);
    zb.voegtoe(10,1);
    zb.voegtoe(6,1);
    zb.voegtoe(7,1);

    cout << zb << endl;
    cout << "Gemiddelde diepte: " << zb.gemiddeldeDiepte() << endl;
}

void test_splay_involgorde() {
    Zoekboom<int,int> zb;

    int AANTAL = 1000;
    for(int i=0; i<AANTAL; i++) {
       zb.voegtoe(i, 1);
    }
    cout << AANTAL << " knopen GEORDEND toegevoegd" << endl;

    cout << "Gemiddelde diepte: " << zb.gemiddeldeDiepte() << endl;

    cout << "SPLAY door " << AANTAL << " knopen te zoeken" << endl;
    srand (time(NULL));

    for(int i=0; i<AANTAL; i++) {
        int rg = rand() % (AANTAL-1) + 1; // AANTAL zelf mag niet gezocht worden, want is niet toegevoegd
        cout << "Zoek : " << rg << endl;
        zb.zoekdatametsplay(rg);
        cout << "Gemiddelde diepte: " << zb.gemiddeldeDiepte() << endl;
    }
}

void test_splay_randomvolgorde() {
    Zoekboom<int,int> zb;
    std::vector<int> v; // om te kunnen shuffelen
    srand (time(NULL));

    int AANTAL = 1000;
    for(int i=0; i<AANTAL; i++) {
        v.push_back(i);
    }

    // Shuffle
    random_shuffle ( v.begin(), v.end() );

    // Voeg toe aan boom
    for(int i=0; i<AANTAL; i++) {
        zb.voegtoe(v[i], 1);
    }

    cout << AANTAL << " knopen RANDOM toegevoegd" << endl;

    cout << "Gemiddelde diepte: " << zb.gemiddeldeDiepte() << endl;

    cout << "SPLAY door " << AANTAL << " knopen te zoeken" << endl;


    for(int i=0; i<AANTAL; i++) {
        int rg = rand() % (AANTAL-1) + 1; // AANTAL zelf mag niet gezocht worden, want is niet toegevoegd
        cout << "Zoek : " << rg << endl;
        zb.zoekdatametsplay(rg);
        cout << "Gemiddelde diepte: " << zb.gemiddeldeDiepte() << endl;
    }
}

int main() {
    // test_voegtoe();

    // test_zoekdata();

    //test_diepte();

    // test_voorganger();

    // test_verwijder();

    // test_gemiddelde_diepte();

    // test_splay_involgorde();

    test_splay_randomvolgorde();


    return 0;
}