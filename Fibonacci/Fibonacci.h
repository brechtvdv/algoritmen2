#ifndef FIBONACCI_H_INCLUDED
#define FIBONACCI_H_INCLUDED

#include <vector>
using std::vector;
using std::cout;
using std::endl;

class Fibonacci {
public:
    Fibonacci(vector<int> &coefficienten, vector<int> &startwaarden, const int n);

// de te bekomen veralgemeende Fibonaccigetal fn
    int fn = 0;
private:
    vector<int> coefficienten;
    vector<int> startwaarden;

// bevat alle n voorgaande Fibonaccigetallen
    vector<int> f;

// aantal startwaarden
    int k = 0;

// berekent veralgemeende Fibonaccigetallen fn voor gegeven n
    int bereken_f(const int n);

// Eerste k startwaarden kennen we
// Berekent n-k opvolgende fibonaccigetallen
    void bereken_voorgaande_f(const int n);
};

Fibonacci::Fibonacci(vector<int> &coefficienten, vector<int> &startwaarden, const int n)
{
    this->coefficienten = coefficienten;
    k = startwaarden.size();

    if(k>=n) f.reserve(n);
    else f.reserve(k);

    // startwaarden kopieren
    for(int i=0; i<k-1; i++)
    {
        f[i] = startwaarden[i];
    }

    if(k<n) {
        bereken_voorgaande_f(n-1);
        fn = bereken_f(n);
    } else fn = f[n];
}

void Fibonacci::bereken_voorgaande_f(const int n)
{
    for(int i=k; i<n; i++)
    {
        f[i] = bereken_f(i);
        std::cout << "nieuwe fn " << f[i] << std::endl;
    }
}

int Fibonacci::bereken_f(const int n)
{
    int fn = 0;

    for(int i=1; i<this->k; i++)
    {
        if(coefficienten[i] != 0)
            fn += coefficienten[i] * f[n-i];
    }

    return fn;
}


#endif // FIBONACCI_H_INCLUDED
