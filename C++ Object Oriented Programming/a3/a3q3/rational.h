#ifndef RAT_H
#define RAT_H
#include <iostream>
struct Rational {
  int num;
  int den;
  void simplify();

  Rational(int num = 0, int den = 1);
  Rational operator+(const Rational &rhs) const;
  Rational operator-(const Rational &rhs) const;
  Rational operator*(const Rational &rhs) const;
  Rational operator/(const Rational &rhs) const;
  
  Rational &operator+=(const Rational &rhs);
  Rational &operator-=(const Rational &rhs);
  Rational operator-() const;

  int getNumerator() const;
  int getDenominator() const;
  bool isZero() const;
};
std::ostream &operator<<(std::ostream &out, const Rational &rat);
std::istream &operator>>(std::istream &in, Rational &rat);
#endif
