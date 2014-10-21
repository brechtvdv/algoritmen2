#include <iostream>
#include "graaf.h"

using namespace std;

int main()
{
    Graaf<GERICHT> g;

    g.voegKnoopToe();
    g.voegKnoopToe();
    g.voegKnoopToe();
    g.voegKnoopToe();

    g.voegVerbindingToe(0,2);
    g.voegVerbindingToe(2,1);

    // stap 1
    Graaf<GERICHT> omg = g.keerOm();

    // stap 2
    map<int, int> post = omg.diepte_eerst_zoeken();

    // stap 3
    g.componenten_maken(post);

    for(int i = 0; i<g.aantalKnopen(); i++)
    {
        cout << i << " " << g.componenten[i] << endl;
    }

    cout << g << endl;
    cout << omg << endl;

    // beginnen bij hoogste postorder nummer
    //map<int,int>::iterator it = post.begin();
    //while(it!=post.end())
    //{
     //   cout << it->first << it->second << endl;
     //   it++;
    //}
    return 0;
}
