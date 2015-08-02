/* 
 * File:   main.cpp
 * Author: brechtvdv
 *
 * Created on August 2, 2015, 5:08 PM
 */

#include <fstream>
#include <iostream>
#include "fibonacci.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    int * coefficients;
    int * startValues;
    
    // Read file fib.txt
    ifstream file;
    file.open("fib.txt");

    int n; // Maximum amount of Fibonacci-numbers that can be calculated
    file >> n;
    
    // Init
    coefficients = new int[n];
    startValues = new int[n];
    
    // Read coefficients
    for (int i = 0; i < n; i++) {
        int coefficient;
        file >> coefficient;
        coefficients[i] = coefficient;
    }
    
    // Read starting values
    for (int i = 0; i < n; i++) {
        int startValue;
        file >> startValue;
        startValues[i] = startValue;
    }
    
    // Read k-th Fibonacci number that we need to calculate
    int k;
    file >> k;
    
    // Init Fibonacci-class
    Fibonacci f(coefficients, startValues);
    
    // Calculate
    f.calculate(k);

    return 0;
}

