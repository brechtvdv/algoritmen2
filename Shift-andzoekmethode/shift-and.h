#include "bitpattern.h"
#include <queue>
#include<vector>
//#include<math.h>

using namespace std;

typedef unsigned int uint;
typedef unsigned char uchar;
const int alphabetSize = 256;

class Shiftand{
public:
    Shiftand(const uchar* pattern,uint _patternLength);
    void search(std::queue<const uchar*>& places,
			  const uchar* text, uint textLength);
private:
	Bitpattern letterPattern[alphabetSize];
    uint patternLength;
};

Shiftand::Shiftand(const uchar* pattern,uint _patternLength) {
	patternLength = _patternLength;
	
	for (int i=0; i < alphabetSize; i++) {
		for (int j=0; j< patternLength; j++) {
			if (pattern[j] == (uchar)(i)) letterPattern[i] |= Bitpattern::onebit(j);
		}
	}
	
}

//Queue contains pointers to the position in the text where the pattern is found
void Shiftand::search(std::queue<const uchar*>& places,
					const uchar* text, uint textLength) {
	Bitpattern r(0);
	
	for (int i=0; i<textLength; i++) {
		r = r.shiftRight(1); // schuif
		r |= Bitpattern::onebit(0); // 1 vanvoor zetten
		r &= letterPattern[text[i]]; // AND met patroon van de letter van de tekst
		
		//cout<<r<<endl;
		//cout<<r.en(Bitpatroon::eenbit(naaldlengte-1))<<endl;
		if (r._and(Bitpattern::onebit(patternLength-1))){
			const uchar* test = &text[i-patternLength+1];
			places.push(test);
		}
	}
}
