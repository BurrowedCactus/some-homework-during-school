#include "rational.h"
#include <iostream>

int gcd(const int a, const int b){
	if (a > b){
		return gcd(b, a);
	}
	if(a == 0){
		return b;
	}
	return gcd(b%a, a);
}

int abs(const int a){
	if (a < 0){
		return -a;
	}
	return a;
}

void Rational::simplify(){
	bool positive;
	if(num * den > 0){
		positive = true;
	} else {
		positive = false;
	}
	int divisor = gcd (abs(num), abs(den));
	if (positive){
		num = abs(num) / abs(divisor);
	} else {
		num = - abs(num) / abs(divisor);
	}
	if (num == 0){
		den = 1;
	} else {
		den = abs(den / divisor);
	}
}

Rational::Rational(int num, int den){
	this->num = num;
	this->den = den;
	if (den != 0){
		simplify();
	}
}

Rational Rational::operator+(const Rational &rhs) const{
	Rational temp{this->num * rhs.den + this->den * rhs.num, this->den * rhs.den};
	return temp;
}

Rational Rational::operator-(const Rational &rhs) const{
	Rational temp{this->num * rhs.den - this->den * rhs.num, this->den * rhs.den};
	return temp;
}

Rational Rational::operator*(const Rational &rhs) const{
	Rational temp{this->num * rhs.num, this->den * rhs.den};
	return temp;
}

Rational Rational::operator/(const Rational &rhs) const{
	Rational temp{this->num * rhs.den, this->den * rhs.num};
	return temp;
}

Rational& Rational::operator+=(const Rational &rhs){
	Rational temp = *this + rhs;
	this->num = temp.num;
	this->den = temp.den;
	return *this;
}

Rational& Rational::operator-=(const Rational &rhs){
	Rational temp = *this - rhs;
	this->num = temp.num;
	this->den = temp.den;
	return *this;
}

Rational Rational::operator-() const{
	Rational temp{- this->num, this->den};
	return temp;
}

int Rational::getNumerator() const{
	return num;
}

int Rational::getDenominator() const{
	return den;
}

bool Rational::isZero() const{
	if (num == 0){
		return true;
	}
	return false;
}
std::ostream &operator<<(std::ostream &out, const Rational &rat){
	if (rat.den == 1){
		out << rat.num;
	} else {
		out << rat.num << '/' << rat.den;
	}
	return out;
}
std::istream &operator>>(std::istream &in, Rational &rat){
	int temp;
	in >> temp;
	rat.num = temp;
	char divide;
	in >> divide;
	in >> temp;
	rat.den = temp;
	if (rat.den != 0){
		rat.simplify();
	}
	return in;
}
