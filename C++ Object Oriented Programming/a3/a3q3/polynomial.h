#ifndef POLY_H
#define POLY_H
#include <iostream>
#include "rational.h"

struct Polynomial {
    Rational *coeffs; // heap allocated array
    int capacity;     // size of allocated array

    Polynomial();     //creates the 0 polynomial

    //Big five
    ~Polynomial();
    Polynomial(const Polynomial &other);
    Polynomial(Polynomial &&other);
    Polynomial &operator=(const Polynomial &other);
    Polynomial &operator=(Polynomial &&other);

    // Arithmetic operations behave in the standard way 
    Polynomial operator+(const Polynomial &rhs) const;
    Polynomial operator-(const Polynomial &rhs) const;
    Polynomial operator*(const Polynomial &rhs) const;

    //returns quotient after long division
    Polynomial operator/(const Polynomial &rhs) const; 

    //returns remainder after long division
    Polynomial operator%(const Polynomial &rhs) const; 

    // degree of the zero polynomial is -1
    int degree() const;
};

// Print with decresing exponents.
std::ostream& operator<<(std::ostream& out, const Polynomial &poly);

// Read until newline consisting of one polynomial in specified format
std::istream& operator>>(std::istream& in, Polynomial &poly);
#endif

