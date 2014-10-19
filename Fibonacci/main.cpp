#include <iostream>
#include <fstream>
#include "Fibonacci.h"

using namespace std;

void inlezen(vector<int> &coefficienten, vector<int> &startwaarden, vector<int> &testwaarden)
{
    int aantal;
    int hulp;

    ifstream myfile ("fib.txt");
    if (myfile.is_open())
    {
        myfile >> aantal;

        coefficienten.reserve(aantal);
        startwaarden.reserve(aantal);

        int i = aantal;
        while ( i > 0 )
        {
          myfile >> hulp;
          coefficienten.push_back(hulp);
          i--;
        }

        i = aantal;
        while( i > 0 )
        {
            myfile >> hulp;
            startwaarden.push_back(hulp);
            i--;
        }

        while( !myfile.eof() )
        {
            myfile >> hulp;
            testwaarden.push_back(hulp);
        }

        myfile.close();
    }

    else cout << "Unable to open file";
}


int main()
{
    vector<int> coefficienten;
    vector<int> startwaarden;
    vector<int> testwaarden;

    int n = 100;

    inlezen(coefficienten, startwaarden, testwaarden);

    Fibonacci f(coefficienten, startwaarden, n);

    cout << f.fn << endl;
    return 0;
}
