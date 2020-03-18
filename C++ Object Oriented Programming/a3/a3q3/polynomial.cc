#include <iostream>
#include <utility>
#include "rational.h"
#include "polynomial.h"
using namespace std;

void resize (Polynomial& poly, int new_size){
	if (poly.capacity < new_size){
		Rational* temp = new Rational[new_size];
		for (int i = 0; i < poly.capacity; ++i){
			temp[i] =  poly.coeffs[i] ;
		}
		delete[] poly.coeffs;
		poly.coeffs = temp;
		poly.capacity = new_size;
	}
}

Polynomial::Polynomial(): coeffs{new Rational[1]}, capacity{1} {}

void add (Polynomial& p, Rational r, int i){
	resize(p, i+1);
	p.coeffs[i] += r;
}

int smaller(int a, int b){
	if (a < b){
		return a;
	}
	return b;
}

int larger(int a, int b){
	if (a < b){
		return b;
	}
	return a;
}

//Big five
Polynomial::~Polynomial(){
	delete[] coeffs;
}

Polynomial::Polynomial(const Polynomial &other): 
		coeffs{new Rational[other.capacity]}, capacity{other.capacity} {
	for (int i = 0; i < capacity; ++i){
		coeffs[i] = other.coeffs[i];
	}
}

Polynomial::Polynomial(Polynomial &&other): 
		coeffs{other.coeffs}, capacity{other.capacity} {
	other.coeffs = nullptr;
}

Polynomial& Polynomial::operator=(const Polynomial &other){ 
	Polynomial temp = other;
	swap(temp.coeffs, this->coeffs);
	swap(temp.capacity, this->capacity);
	return *this;
	
}


Polynomial& Polynomial::operator=(Polynomial &&other){
	swap(other.coeffs, this->coeffs);
	swap(other.capacity, this->capacity);
	return *this;

}



// Arithmetic operations behave in the standard way
Polynomial Polynomial::operator+(const Polynomial &rhs) const{
	Polynomial temp{*this};
	int small = smaller(temp.capacity, rhs.capacity);
	int large = larger(temp.capacity, rhs.capacity);
	bool enlarged = false;
	if (temp.capacity < rhs.capacity){
		resize(temp, rhs.capacity);
		enlarged = true;
        }
        for (int i = 0; i < small; ++i){
		temp.coeffs[i] += rhs.coeffs[i];
        }
	if(enlarged){

	for (int i = small; i < large; ++i){
			temp.coeffs[i] = rhs.coeffs[i];
	}
}
	return temp;
}

Polynomial Polynomial::operator-(const Polynomial &rhs) const{
	Polynomial temp{*this};
        int small = smaller(temp.capacity, rhs.capacity);
        int large = larger(temp.capacity, rhs.capacity);
        bool enlarged = false;
        if (temp.capacity < rhs.capacity){
                resize(temp, rhs.capacity);
                enlarged = true;
        }
        for (int i = 0; i < small; ++i){
                temp.coeffs[i] -= rhs.coeffs[i];
        }
	if(enlarged){
        	for (int i = small; i < large; ++i){
                        temp.coeffs[i] = -rhs.coeffs[i];
                

                }
        }
        return temp;
}

Polynomial Polynomial::operator*(const Polynomial &rhs) const{
	int new_cap = capacity + rhs.capacity - 1;
	Polynomial temp_p = *this;
	temp_p.capacity = new_cap;
	Rational* temp_r = new Rational[new_cap];
	for (int i = 0; i < capacity; ++i){
		for (int j = 0; j < rhs.capacity; ++j){
			temp_r[i+j] += coeffs[i] * rhs.coeffs[j];
		}
	}
	delete[] temp_p.coeffs;
	temp_p.coeffs = temp_r;
	return temp_p;
}
    //returns quotient after long division

Polynomial Polynomial::operator/(const Polynomial &rhs) const{
	// divisor cant be zero polynomial
	Polynomial answer;
	Polynomial dividend{*this};
	int deg_l = dividend.degree();
        int deg_r = rhs.degree();
	while (deg_l >= deg_r){
		Rational highest_r = dividend.coeffs[deg_l] / rhs.coeffs[deg_r];
		Polynomial temp;
		add(temp, highest_r, deg_l - deg_r);
		temp = temp * rhs;
		dividend = dividend - temp;
		add(answer, highest_r, deg_l - deg_r);
		deg_l = dividend.degree();
	}
	return answer;
}
    //returns remainder after long division
Polynomial Polynomial::operator%(const Polynomial &rhs) const{
	return *this - (*this / rhs * rhs);
}

    // degree of the zero polynomial is -1
	
    //returns remainder after long division

    // degree of the zero polynomial is -1
int Polynomial::degree() const{
	for (int degree = capacity - 1; degree >=0; --degree){
		if (coeffs[degree].getNumerator() != 0){
			return degree;
		}
	}
	return -1;
}


// Print with decresing exponents.
std::ostream& operator<<(std::ostream& out, const Polynomial &poly){
	bool first = true;
	bool zero = true;
	for (int i = poly.capacity - 1; i > 1; --i ){
		if ((poly.coeffs[i].getNumerator()) != 0){
			zero = false;
			if (first){
				first = false;
				out << '(' << poly.coeffs[i] <<  ")x^" << i;
			} else {
				out << " + (" << poly.coeffs[i] <<  ")x^" << i;
			}
		}
	}
	if (poly.capacity > 1 && (poly.coeffs[1].getNumerator()) != 0){
		zero = false;
		if (first){
			first = false;
			out << '(' << poly.coeffs[1] <<  ")x";
		} else {
			out << " + (" << poly.coeffs[1] <<  ")x";
		}
	}
	if (poly.capacity > 0 && (poly.coeffs[0].getNumerator()) != 0){
		zero = false;
		if (first){
			first = false;
			out << '(' << poly.coeffs[0] <<  ")";
		} else {
			out << " + (" << poly.coeffs[0] <<  ")";
		}
	}
	if (zero){
		out << 0;
	}
	return out;
}

// Read until newline consisting of one polynomial in specified format
std::istream& operator>>(std::istream& in, Polynomial &poly){
	Rational temp_rational;
	int degree;
	while (!in.eof()){
		in >> temp_rational;
		in >> degree;
		if(in.fail()){
			in.clear();
			break;
		}
		add (poly, temp_rational, degree);
	}
	return in;
}

