#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <cmath>
#include <vector>
#include "csv.h"
#include "zoekboom_Cpp11.h"
#include "puntgenerator.h"
using namespace std;


int aantalDatapunten=6000;
string BESTANDSNAAM = "/Users/brechtvdv/School/Algoritmen2/Splaybomen/dieptedata.csv"; // ZELF AANPASSEN

int main(int argc, char *argv[]){
    CsvData grafiek(BESTANDSNAAM,'.');
    Puntgenerator dePuntgenerator;

    Zoekboom<double,unsigned int> deZoekboom;
    Zoekboom<double,unsigned int> deZoekboomMetSplay;

    vector<int> aantalKnopenData;
    vector<double> diepteData;
    vector<double> gemiddeldeDiepteZonderSplay;
    vector<double> diepteMetSplay;
    vector<double> gemiddeldeDiepteMetSplay;
    int aantal=0;
    int aantalKnopen=0;
    for (int i=0; i<aantalDatapunten; i++ ){
        double nupunt=dePuntgenerator.geefpunt();
//        deZoekboom.voegtoe(dePuntgenerator.geefpunt(),i);
        deZoekboom.voegtoe(nupunt,i);
        deZoekboomMetSplay.voegtoe(nupunt,i); // is dezelfde, maar gaan we gebruiken om te splayen
        aantal++;
        aantalKnopen++;
        if (aantal*50 >= aantalDatapunten) {
            aantalKnopenData.push_back(aantalKnopen);
            diepteData.push_back(deZoekboom.diepte());
            gemiddeldeDiepteZonderSplay.push_back(deZoekboom.gemiddeldeDiepte());

            // Eerst de knoop zoeken en bijgevolg splayen
            deZoekboomMetSplay.zoekdatametsplay(nupunt);

            diepteMetSplay.push_back(deZoekboomMetSplay.diepte());
            gemiddeldeDiepteMetSplay.push_back(deZoekboomMetSplay.gemiddeldeDiepte());
            aantal=0;
        }
    }
    grafiek.voegDataToe(aantalKnopenData);
    grafiek.voegDataToe(diepteData);
    grafiek.voegDataToe(gemiddeldeDiepteZonderSplay);
    grafiek.voegDataToe(diepteMetSplay);
    grafiek.voegDataToe(gemiddeldeDiepteMetSplay);
    return 0;
}

