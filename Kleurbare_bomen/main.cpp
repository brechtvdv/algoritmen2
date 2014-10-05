#include <iostream>
#include "rzwboom.h"

using namespace std;

int main()
{
    Rzwboom<int, int> boom;
	int data[13] = { 10, 3, 15, 2, 6, 12, 18, 4, 8, 11, 13, 16, 20 };
	int i = 0;
	while (i < 13) {
		boom.voegtoe(data[i], data[i]);
		i++;
	}

	//boom.verwijder(3);
	cout << boom << endl;
	cout << "Normale diepte " << boom.diepte() << endl;
	cout << "Rood zwarte diepte : " << boom.zwartediepterec().first << endl;
    cout << "Is kleurbaar: " << boom.is_kleurbaar() << endl;

    boom.kleur();

    cout << boom << endl;

    return 0;
}
