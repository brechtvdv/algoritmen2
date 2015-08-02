/* 
 * File:   main.cpp
 * Author: brechtvdv
 *
 * Created on August 2, 2015, 5:08 PM
 */

#include <fstream>
#include <iostream>
#include <vector>
#include "fibonacci.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    vector<int> coefficients;
    vector<int> startValues;
    
    // Read file fib.txt
    ifstream file;
    file.open("fib.txt");

    int k; // Amount of coefficients/startValues
    file >> k;
    
    // Read coefficients
    for (int i = 0; i < k; i++) {
        int coefficient;
        file >> coefficient;
        coefficients.push_back(coefficient);
    }
    
    // Read starting values
    for (int i = 0; i < k; i++) {
        int startValue;
        file >> startValue;
        startValues.push_back(startValue);
    }
    
    // Init Fibonacci-class
    Fibonacci f(coefficients, startValues, k);
    
    // Read n-th Fibonacci number that we need to calculate
    int n;
    file >> n;
    
    // Calculate
    int fn = f.calculate(n);
    
    cout << "Fibonacci number of " << n << " is: " << fn << endl;
    
    return 0;
}

