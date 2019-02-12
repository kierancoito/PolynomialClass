

#ifndef ASSIGNMENT1_POLY_H
#define ASSIGNMENT1_POLY_H
#include <iostream>
using namespace std;

//---------------------------------------------------------------------------
// Kieran Coito CSS343A
// 13/01/2018
// 15/01/2018
//---------------------------------------------------------------------------
// Poly class:
// This programs purpose is to create and store a polynomial string in an
// Array. There are 4 ways to construct this object, either with a single
// coefficient, a coefficient and its exponent, another Poly object, or the
// default constructor which requires nothing.
// This program intends to be able to perform basic manipulation of
// the polynomial (+,-,*, +=, -=, *=), assignment  (=), and boolean
// truths (!=, ==).
//---------------------------------------------------------------------------
// Assumptions:
// -This program can only accept positive integer value as the exponent for
// a given value in a polynomial.
// -Coefficients must be integer values and cannot be anything else
//---------------------------------------------------------------------------
class Poly {

    //input and output
    friend istream& operator>>( istream &in, Poly &rhs );
    friend ostream& operator<<( ostream &out, const Poly &rhs );

public:

    //constructors
    Poly();
    Poly( int coeff, int power );
    Poly( int coeff );
    Poly( const Poly &toCopy );

    //destructor
    ~Poly();

    //getter
    int getCoeff( int power ) const;

    //setter
    void setCoeff(int newCoeff, int power);

    //common operators
    Poly operator+( const Poly& rhs ) const;
    Poly operator+( const int& rhs ) const;
    Poly operator-( const Poly& rhs ) const;
    Poly operator-( const int& rhs ) const;
    Poly operator*( const Poly& rhs ) const;
    Poly operator*( const int& rhs ) const;

    //assignment
    const Poly &operator=( const Poly& rhs );

    //additional common operators
    Poly &operator*=( const Poly& rhs );
    Poly &operator+=( const Poly& rhs );
    Poly &operator-=( const Poly& rhs );

    //logical Binary Operators
    bool operator==( const Poly& rhs ) const;
    bool operator!=( const Poly& rhs ) const;

private:

    //pointer to the array that will contain the polynomial
    int* polyArray;
    //size of the array that holds the polynomial
    int size = 0;

    //helper methods
    void increase(int power);
    void fill();
    void copy(const Poly& copy);

};


#endif //ASSIGNMENT1_POLY_H
