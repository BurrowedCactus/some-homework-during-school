#ifndef POLY_H
#define POLY_H
#include <iostream>
#include <cstdint>

struct Polynomial {
    int64_t *coeffs; // heap allocated array
    int capacity;     // size of allocated array
    
    Polynomial();
    Polynomial(int num);

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
    Polynomial operator*(const int A) const;
    Polynomial half_first() const;
    Polynomial half_last() const;
    bool operator==(const Polynomial &rhs) const;
    // degree of the zero polynomial is -1
    int degree() const;
};

// Print with decresing exponents.
std::ostream& operator<<(std::ostream& out, const Polynomial &poly);

#endif

