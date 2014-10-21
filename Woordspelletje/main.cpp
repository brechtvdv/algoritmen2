#include <iostream>
#include "graaf.h"

using namespace std;

int main()
{
    Graaf<GERICHT> g;

    g.voegKnoopToe();
    g.voegKnoopToe();
    g.voegKnoopToe();

    g.voegVerbindingToe(0,2);
    g.voegVerbindingToe(2,1);

    Graaf<GERICHT> omg = g.keerOm();

    vector<int> post = g.diepte_eerst_zoeken();


    cout << g << endl;
    cout << omg << endl;

      for(int i = 0; i<post.size(); i++)
    {
        cout << post[i] << endl;
    }

    return 0;
}
