#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include "shift-and.h"

using namespace std;

typedef unsigned int uint;
typedef unsigned char uchar;

std::string lees(std::string bestand){
	std::ifstream file(bestand.c_str());
	std::string hooiberg((std::istreambuf_iterator<char>(file)),
						 std::istreambuf_iterator<char>() );
	return hooiberg;
}

int main(int argc, char *argv[]) {
	std::string naald = "koran";
	std::string hooiberg = lees("/Users/brechtvdv/Algoritmen2/Shift-andzoekmethode/koran.txt");

	// uchar* pattern = (uchar*)"alpha";
	// uchar* text = (uchar*)"alpha beta alpha charly";
	//Shiftand sa(pattern, 5);
	// sa.search(places, text, 23);

	Shiftand sa((uchar*) naald.c_str(), naald.size());

	queue<const uchar*> places;

	sa.search(places, (uchar*) hooiberg.c_str(), (uint) hooiberg.size());

	int aantalMatches = 0;
	while(!places.empty()){
		aantalMatches++;
		// cout<<places.front()<<endl;
		places.pop();
	}

	cout << "Aantal matches is: " << aantalMatches << endl;
	
	return 0;
}