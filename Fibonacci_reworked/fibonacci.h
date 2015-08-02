/* 
 * File:   fibonacci.h
 * Author: brechtvdv
 *
 * Created on August 2, 2015, 5:34 PM
 */

#ifndef FIBONACCI_H
#define	FIBONACCI_H

class Fibonacci {
    
    int *coefficients_;
    int *startValues_;
    
public: 
    Fibonacci(int * _coefficients, int * _startValues);
    
    // Calculates kth Fibonacci number
    // If k > size(_coefficients), calculate previous first
    int calculate(int k);    
};

Fibonacci::Fibonacci(int* _coefficients, int* _startValues) {
    this->coefficients_ = _coefficients;
    this->startValues_ = _startValues;
}

int Fibonacci::calculate(int k) {
    
    return 0;
}

#endif	/* FIBONACCI_H */

