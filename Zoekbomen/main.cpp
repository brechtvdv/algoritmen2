#include <iostream>
#include "zoekboom.h"

using namespace std;

int main()
{
    Zoekboom<int,const char*> b;

    b.voegtoe(1,1);
    b.voegtoe(2,2);
    b.voegtoe(3,3);
    b.voegtoe(4,4);
    b.voegtoe(1,2);

    cout << b << endl;

	cout << *(b.zoekdata(20)) << endl;
    // naar links roteren
    //b.deBinboom.roteer(true);

    cout << b.deBinboom.is_binaire_boom() << endl;

    //b.verwijder("twintig");

    cout << *(b.zoekdata(20)) << endl;


    return 0;
}
