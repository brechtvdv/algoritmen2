#include <iostream>
#include "zoekboom.h"

using namespace std;

int main()
{
    Zoekboom<int,int> b;

    b.voegtoe(1,1);
    b.voegtoe(2,2);
    b.voegtoe(3,3);
    b.voegtoe(4,4);
    b.voegtoe(1,2);

    cout << b << endl;

    // naar links roteren
    b.deBinboom.roteer(true);

    cout << b.deBinboom.is_binaire_boom() << endl;

    return 0;
}
