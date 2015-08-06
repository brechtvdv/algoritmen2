#ifndef KMP_H
#define KMP_H

#include <queue>
#include <vector>
#include <iostream>

using namespace std;

typedef unsigned int uint;
typedef unsigned char uchar;
class KnuthMorrisPratt{
    const uchar* naald_;
    uint naaldLengte_;
    
private:
    // LPS = Langste Prefix dat ook Suffix is
    // Moet voor het zoeken doorheen de tekst berekend worden
    // Vermijdt dat we informatie waarvan we weten dat het matcht opnieuw moeten checken
    // Voor patroon “AABAACAABAA”, lps[] is [0, 1, 0, 1, 2, 0, 1, 2, 3, 4, 5]
    void berekenLPSArray(std::vector<uint>& lps);
    
public:
    KnuthMorrisPratt(const uchar* naald,uint _naaldlengte);
    void zoek(std::queue<const uchar*>& plaats,
                     const uchar* hooiberg, uint hooiberglengte);
};

KnuthMorrisPratt::KnuthMorrisPratt(const uchar* naald, uint _naaldlengte)
{
    for (uint i=0; i<_naaldlengte; i++)
    {
        naald_ = naald;
    }
//    naald_ = naald;
    naaldLengte_ = _naaldlengte;
}

void KnuthMorrisPratt::zoek(std::queue<const uchar*>& plaats, const uchar* hooiberg, uint hooiberglengte)
{
    std::vector<uint> lps;
    berekenLPSArray(lps); // preprocessing

    uint i = 0; // pointer die naar letter in tekst (bijbel) verwijst
    uint j = 0; // pointer die naar letter in patroon verwijst
    
    while (i<hooiberglengte)
    {
        if (naald_[j] == hooiberg[i])
        {
            i++;
            j++;
        }
        
        if (j == naaldLengte_)
        {
            plaats.push(&hooiberg[i-j]);
            j = lps[j-1];
        }
        
        // Mismatch
        else if (i<hooiberglengte && naald_[j] != hooiberg[i])
        {
            // Geen nut om lps[0..lps[j-1]] characters te matchen
            // Zullen sowieso matchen
            if (j!=0)
            {
                j = lps[j-1];
            } else {
                i++;
            }
        }
    }
    
    
}

void KnuthMorrisPratt::berekenLPSArray(std::vector<uint>& lps)
{
    uint lengte = 0; // Lengte van de vorige langste prefix suffix
    uint i;
    
    lps.reserve(naaldLengte_);
    
    lps[0] = 0; // lps[0] is altijd 0
    i = 1;
    
    // lps[i] berekenen voor gehele patroon
    while (i<naaldLengte_)
    {
        if (naald_[i] == naald_[lengte])
        {
            lengte++;
            lps[i] = lengte;
            i++;
        }
        else // naald_[i] != naald_[lengte]
        {
            if (lengte != 0)
            {
                lengte = lps[lengte-1]; // vorige lps
                
                // i wordt niet verhoogd!
            } else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

#endif
    
