#include <iostream>
#include "bloklijst.h"
#include <string>

using namespace std;

void test_bloklijst_voegtoe() {
    Schijf<Schijfpagina<int, string>> schijf;
    Bloklijst<int, string> lijst(schijf);

    lijst.voegtoe(5,"test");
    lijst.voegtoe(19,"joo");
    lijst.voegtoe(24,"joo");
    lijst.voegtoe(2,"joo");

    cout << lijst << endl;
}

int main() {
    // test_bloklijst_voegtoe();


    return 0;
}