//
// Created by Kieran Coito on 2019-01-14.
//

#ifndef ASSIGNMENT1_POLY_H
#define ASSIGNMENT1_POLY_H
#include <iostream>
using namespace std;



class Poly {

    friend istream& operator>>( istream &in, Poly &rhs );
    friend ostream& operator<<( ostream &out, const Poly &rhs );

public:

    //constructors
    Poly();
    Poly( int coeff, int power );
    Poly( int coeff );
    Poly( const Poly &copy );

    //destructor
    ~Poly();

    //Getter
    int getCoeff( int power ) const;

    //Setter
    void setCoeff(int power, int newCoeff);

    //Common operators
    Poly operator+( const Poly& rhs ) const;
    Poly operator-( const Poly& rhs ) const;
    Poly operator*( const Poly& rhs ) const;

    const Poly &operator=( const Poly& rhs );

    Poly &operator*=( const Poly& rhs );
    Poly &operator+=( const Poly& rhs );
    Poly &operator-=( const Poly& rhs );

    //Logical Binary Operators
    bool operator==( const Poly& rhs ) const;
    bool operator!=( const Poly& rhs ) const;

private:

    int* PolyArray;
    int size;

};


#endif //ASSIGNMENT1_POLY_H
