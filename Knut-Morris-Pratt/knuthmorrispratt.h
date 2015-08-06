#include <queue>
typedef unsigned int uint;
typedef unsigned char uchar;
class KnuthMorrisPratt{
    const uchar* naald_;
    uint naaldLengte_;
    
public:
    KnuthMorrisPratt(const uchar* naald,uint _naaldlengte);
    void zoek(std::queue<const uchar*>& plaats,
                     const uchar* hooiberg, uint hooiberglengte);
};

KnuthMorrisPratt::KnuthMorrisPratt(const uchar* naald, uint _naaldlengte)
{
    naald_ = naald;
    naaldLengte_ = _naaldlengte;
}

void KnuthMorrisPratt::zoek(std::queue<const uchar*>& plaats, const uchar* hooiberg, uint hooiberglengte)
{
    
}
    
