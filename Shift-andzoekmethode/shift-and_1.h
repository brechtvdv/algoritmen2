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
	Bitpattern Shift(Bitpattern &p);
};

Shiftand::Shiftand(const uchar* pattern,uint _patternLength) {
	patternLength = _patternLength;
	
	for (int i=0; i < alphabetSize; i++) {
		for (int j=0; j< patternLength; j++) {
			if (pattern[j] == (uchar)(i)) letterPattern[i] |= Bitpattern::onebit(j);
		}
	}
	
}

Bitpattern Shiftand::Shift(Bitpattern &p){
	return p.shiftRight(1)|Bitpattern::onebit(0);
}

//Queue contains pointers to the position in the text where the pattern is found
void Shiftand::search(std::queue<const uchar*>& places,
					const uchar* text, uint textLength) {
	Bitpattern r0(0);
	Bitpattern r1(0);
	r1 |= Bitpattern::onebit(0);
	
	for (int i=0; i<textLength; i++) {

		Bitpattern r0_j = r0; // Temporary, needed for r1
		r0 = Shift(r0) & letterPattern[text[i]];
		if (r0._and(Bitpattern::onebit(patternLength-1)))
			places.push(&text[i-patternLength+1]);
		
		r1 = r0_j | Shift(r0) | Shift(r0_j) | (Shift(r1) & letterPattern[text[i]]);
		if (r1._and(Bitpattern::onebit(patternLength-1)))
			places.push(&text[i-patternLength+1]);
		
	}
}