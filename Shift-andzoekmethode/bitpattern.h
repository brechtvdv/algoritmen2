#ifndef __BITPATTERN
#define __BITPATTERN
#include <iostream>
using std::ostream;
typedef unsigned int uint;
const int patternlength=sizeof(uint)*8;
class Bitpattern{
public:
    uint bits;
    Bitpattern(uint u=0):bits(u){};
//AND-operator
    const Bitpattern operator&(const Bitpattern& b) const{
        return Bitpattern(bits & b.bits);
    }
//OR-operator
    const Bitpattern operator|(const Bitpattern& b) const{
        return Bitpattern(bits | b.bits);
    }
//AND-=-operator
    const Bitpattern& operator&=(const Bitpattern& b){
        bits&= b.bits;
        return *this;
    }
//OR-=-operator
    const Bitpattern& operator|=(const Bitpattern& b){
        bits|= b.bits;
        return *this;
    }
//logical operators
    bool _and(const Bitpattern& b) const{
        return (bits & b.bits)!=0;
    }
    bool _or(const Bitpattern& b) const{
        return (bits | b.bits)!=0;
    }
//warning: shiftoperations doens't shift if shifting >= patternlength.
    const Bitpattern shiftLeft(uint shifting) const{
        return Bitpattern(bits<<shifting);
    }
    const Bitpattern shiftRight(uint shifting) const{
        return Bitpattern(bits>>shifting);
    }
//not secured: u must be smaller than patternlength.
    static Bitpattern onebit(uint u){
        return Bitpattern(uint(1)<<(patternlength-1-u));
    }
    friend ostream& operator<<(ostream& os, const Bitpattern& b){
      for (int i=0;i<patternlength;i++){
          os<<b._and(onebit(i));
      }
        return os;
    }
};
#endif
    
