/* 
 * File:   main.cpp
 * Author: brechtvdv
 *
 * Created on 06 August 2015, 12:40
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include "knuthmorrispratt.h"

typedef unsigned int uint;
typedef unsigned char uchar;

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    cout << "Give me a string to search in the bible:" << endl;
        
    string input;
    cin >> input;

    uchar* naald = (uchar *) input.c_str();
    uint naaldLengte = input.length();
    
    // Hooiberg is de bijbel
    ifstream in("bijbel.txt");
    string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    
    uchar* hooiberg = (uchar *) contents.c_str();
    uint hooibergLengte = contents.length();

    KnuthMorrisPratt kmp(naald, naaldLengte);
    queue<const uchar*> plaats;
    kmp.zoek(plaats, hooiberg, hooibergLengte);
    
    cout << naald << " komt "  << plaats.size() << " keer voor." << endl;
    
//    cout << *(plaats.front()) << endl;
    
    return 0;
}