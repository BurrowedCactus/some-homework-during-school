#include <iostream>
#include <utility>
#include <cstdint>
#include <cmath>

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

void resize (Polynomial& poly, int new_size, int mode = -1){
	if (mode == -1){
		if (poly.capacity < new_size){
			int64_t* temp = new int64_t[new_size];
			for (int i = 0; i < poly.capacity; ++i){
				temp[i] =  poly.coeffs[i];
			}
			for (int i = poly.capacity; i < new_size; ++i){
				temp[i] = 0;
			}
			delete[] poly.coeffs;
			poly.coeffs = temp;
			poly.capacity = new_size;
		}
	//copy first half
	} else if (mode == 1){
		int64_t* temp = new int64_t[new_size - new_size/2];
		for (int i = 0; i < new_size - new_size/2; ++i){
			temp[i] =  poly.coeffs[i];
		}
		delete[] poly.coeffs;
		poly.coeffs = temp;
		poly.capacity = new_size - new_size/2;
	//copy last half
	} else if (mode == 2){
		int64_t* temp = new int64_t[new_size/2];
		for (int i = 0; i < new_size/2; ++i){
			temp[i] =  poly.coeffs[i + new_size - new_size/2];
		}
		delete[] poly.coeffs;
		poly.coeffs = temp;
		poly.capacity = new_size/2;
	//shift
	} else {
		int64_t* temp = new int64_t[new_size + poly.capacity];
		for (int i = 0; i < new_size; ++i){
			temp[i] = 0;
		}
		for (int i = 0; i < poly.capacity; ++i){
			temp[i + new_size] =  poly.coeffs[i];
		}
		delete[] poly.coeffs;
		poly.coeffs = temp;
		poly.capacity = new_size + poly.capacity;
	}	
}

Polynomial::Polynomial(int num): coeffs{new int64_t[num+1]}, capacity{num+1} {
	for (int i = 0; i < capacity; ++i){
		std::cin >> coeffs[i];
	}
}

Polynomial::Polynomial(): coeffs{new int64_t[1]}, capacity{1} {
	coeffs[0] = 0;
}

void add (Polynomial& p, int64_t r, int i){
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
		coeffs{new int64_t[other.capacity]}, capacity{other.capacity} {
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
	std::swap(temp.coeffs, this->coeffs);
	std::swap(temp.capacity, this->capacity);
	return *this;
	
}


Polynomial& Polynomial::operator=(Polynomial &&other){
	std::swap(other.coeffs, this->coeffs);
	std::swap(other.capacity, this->capacity);
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

Polynomial Polynomial::half_first() const{
	Polynomial temp{*this};
	resize(temp, temp.capacity, 1);
	return temp;
}

Polynomial Polynomial::half_last() const{
	Polynomial temp{*this};
	resize(temp, temp.capacity, 2);
	return temp;
}

Polynomial Polynomial::operator*(const Polynomial &rhs) const{

	if (degree() == 0){
		Polynomial temp(*this);
		temp.coeffs[0] *= rhs.coeffs[0];
		return temp;
	}
	Polynomial half1 = half_first();
	Polynomial half2 = half_last();
	Polynomial half1r = rhs.half_first();
	Polynomial half2r = rhs.half_last();
	Polynomial sum = (half1 + half2) * (half1r + half2r);
	Polynomial sum1 = half1 * half1r;
	Polynomial sum2 = half2 * half2r;
	sum = sum - sum1 - sum2;
	resize(sum2, 2*ceil(capacity/2.0), 3);
	resize(sum, ceil(capacity/2.0), 3);
	return sum + sum1 + sum2;

/*

	int new_cap = capacity + rhs.capacity - 1;
	Polynomial temp_p = *this;
	temp_p.capacity = new_cap;
	int64_t* temp_r = new int64_t[new_cap];
	for (int i = 0; i < capacity; ++i){
		for (int j = 0; j < rhs.capacity; ++j){
			temp_r[i+j] += coeffs[i] * rhs.coeffs[j];
		}
	}
	delete[] temp_p.coeffs;
	temp_p.coeffs = temp_r;
	return temp_p;
*/
}
    //returns quotient after long division

Polynomial Polynomial::operator*(const int A) const{
	Polynomial temp_p = *this;
	int deg = degree();
	for (int i = 0; i < deg; ++i){
		temp_p.coeffs[i] = coeffs[i] * A;
	}
	return temp_p;
}


int Polynomial::degree() const{
	for (int degree = capacity - 1; degree >=0; --degree){
		if (coeffs[degree] != 0){
			return degree;
		}
	}
	return -1;
}

bool Polynomial::operator==(const Polynomial &rhs) const{
	if (degree() != rhs.degree()){
		return false;
	}
	int small = smaller(degree(), rhs.degree());
	for (int i = 0; i < small; ++i){
		if (coeffs[i] != rhs.coeffs[i]){
			return false;
		}
	}
	return true;
}

// Print with decresing exponents.
std::ostream& operator<<(std::ostream& out, const Polynomial &poly){
	bool first = true;
	bool zero = true;
	for (int i = poly.capacity - 1; i > 1; --i ){
		if ((poly.coeffs[i]) != 0){
			zero = false;
			if (first){
				first = false;
				out << '(' << poly.coeffs[i] <<  ")x^" << i;
			} else {
				out << " + (" << poly.coeffs[i] <<  ")x^" << i;
			}
		}
	}
	if (poly.capacity > 1 && (poly.coeffs[1]) != 0){
		zero = false;
		if (first){
			first = false;
			out << '(' << poly.coeffs[1] <<  ")x";
		} else {
			out << " + (" << poly.coeffs[1] <<  ")x";
		}
	}
	if (poly.capacity > 0 && (poly.coeffs[0]) != 0){
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
	int64_t temp_rational;
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


int main(){
	using namespace std;
	int polyn1;
	int polyn2;
	int A;
	cin >> polyn1;
	cin >> polyn2;
	cin >> A;
	
	Polynomial poly1(polyn1);
	Polynomial poly2(polyn2);
	//cant match
	if (2 * poly1.degree() != poly2.degree()){
		cout << "FALSE" << endl;
	} else {
		poly1 = poly1 * poly1;
		poly2 = poly2 * A;	
		if (poly1 == poly2){
			cout << "TRUE" << endl;
		} else {
			cout << "FALSE" << endl;
		}
		
	}
}
