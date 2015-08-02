/* 
 * File:   fibonacci.h
 * Author: brechtvdv
 *
 * Created on August 2, 2015, 5:34 PM
 */

#ifndef FIBONACCI_H
#define	FIBONACCI_H

#include <vector>
#include <iostream>
using namespace std;

class Fibonacci {
    
    vector<int> coefficients_; // contains k coefficients
    vector<int> startValues_; // contains first Fibonacci-numbers

    int k_; // Amount of coefficients
    
    int size_; // Size of values we already know in startValues
    
public: 
    Fibonacci(const vector<int>& _coefficients, const vector<int>& _startValues, int _size);
    
    // Calculates nth Fibonacci number
    int calculate(int n);
    
    // Utility function that calculates next number and saves it
    void calculateNextFibonacci();

};

Fibonacci::Fibonacci(const vector<int>& _coefficients, const vector<int>& _startValues, int _size) {
    this->coefficients_ = _coefficients;
    this->startValues_ = _startValues;
    this->k_ = _size;
    this->size_ = _size; // Initial is the amount of startValues equals size
}


int Fibonacci::calculate(int n) {
    int fn = 0;
    
    while (n > size_-1) {
        calculateNextFibonacci();
    }

    return startValues_.at(n);
}

void Fibonacci::calculateNextFibonacci() {
    int fn = 0;
    
    // Loop through coefficients
    for (int i=0; i<k_; i++) {
        fn += coefficients_[i] * startValues_.at(size_-1-i);
    }
    
    cout << "Calculated Fibonacci nr: " << size_ << " : " << fn << endl;
    startValues_.push_back(fn); // Update
    size_++;
}

#endif	/* FIBONACCI_H */

