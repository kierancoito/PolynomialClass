//
// Created by Kieran Coito on 2019-01-14.
//
#include <iostream>
#include <vector>
#include "Poly.h"
using namespace std;

// ---------------------------------------------------------------------------
//
Poly::Poly(){

    size = 1;
    PolyArray = new int[1];
    PolyArray[0] = 0;
}

// ---------------------------------------------------------------------------
//
Poly::Poly( int coeff, int power ){

    if( size == 0 ){
        PolyArray = new int[power+1];
        PolyArray[power] = coeff;
    }else if(size < power){

    }
}

// ---------------------------------------------------------------------------
//
Poly::Poly( int coeff ){

    size = 1;
    PolyArray = new int[size];
    PolyArray[0] = coeff;
}

// ---------------------------------------------------------------------------
//
Poly::Poly( const Poly &copy ){

    size = copy.size;
    PolyArray = new int[size];
    for(int i = 0; i < size; i++){
        PolyArray[i] = copy.PolyArray[i];
    }
}

// ---------------------------------------------------------------------------
//
//destructor
Poly::~Poly(){

}

// ---------------------------------------------------------------------------
//
//Getter
int Poly::getCoeff( int power ) const{
    return PolyArray[power];
}

// ---------------------------------------------------------------------------
//
//Setter
void Poly::setCoeff(int power, int newCoeff){
    PolyArray[power] = newCoeff;
}

// ---------------------------------------------------------------------------
//
//
Poly Poly::operator+( const Poly& rhs ) const{

}

// ---------------------------------------------------------------------------
//
Poly Poly::operator-( const Poly& rhs ) const{

}

// ---------------------------------------------------------------------------
//
Poly Poly::operator*( const Poly& rhs ) const{

}

// ---------------------------------------------------------------------------
//
const Poly& Poly::operator=( const Poly& rhs ){
    PolyArray = rhs.PolyArray;
    return rhs;
}

// ---------------------------------------------------------------------------
//
Poly& Poly::operator*=( const Poly& rhs ){

}

// ---------------------------------------------------------------------------
//
Poly& Poly::operator+=( const Poly& rhs ){

}

// ---------------------------------------------------------------------------
//
Poly& Poly::operator-=( const Poly& rhs ){

}

// ---------------------------------------------------------------------------
//
bool Poly::operator==( const Poly& rhs ) const{
    if(size != rhs.size){
        return false;
    }

    for(int i = 0; i < size; i++){
        if( getCoeff(i) != rhs.getCoeff(i) ){
            return false;
        }
    }

    return true;

}

// ---------------------------------------------------------------------------
//
bool Poly::operator!=( const Poly& rhs ) const{

    if(size == rhs.size){
        return false;
    }

    for(int i = 0; i < size; i++){
        if( getCoeff(i) == rhs.getCoeff(i) ){
            return false;
        }
    }

    return true;

}

// ---------------------------------------------------------------------------
//
istream& operator>>( istream &in, Poly &rhs ){

    int coeff, power;
    in >> coeff;
    in >> power;
    while(coeff != -1 && power != -1){
        Poly(coeff, power);

    }

    return in;

}

// ---------------------------------------------------------------------------
//
ostream& operator<<( ostream &out, const Poly &rhs ){


    for( int i = rhs.size ; i >= 0; i-- ){

        out << rhs.getCoeff(i) << "x^" << i << " ";

    }
    //return ostream
    return out;

}