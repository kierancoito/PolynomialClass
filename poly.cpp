#include <iostream>
#include <vector>
#include "poly.h"
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

//---------------------------------Default-Constructor-----------------------
// Description: Creates a new Poly object that is one element, the number 0
//---------------------------------------------------------------------------
Poly::Poly(){

    //set the size to one, create an array of size one and assign 0
    size = 1;
    polyArray = new int[1];
    polyArray[0] = 0;

} // end of Poly

//---------------------------------Constructor-------------------------------
// Description: Creates a new Poly object. Requires 2 int parameters,
// coeff and power, power cannot be negative
//---------------------------------------------------------------------------
Poly::Poly( int coeff, int power ){

    //if this is a new poly create a new array that is the size power+1
    //after filling it with zeroes, set the coeff and power
    if( size == 0 ){
        polyArray = new int[power];
        size = power+1;
        fill();
        setCoeff(coeff,power);

    //if this is not a new poly but the existing poly is too small
    //increase its size and then set the coeff and power
    }else if(size < power){
        increase(power);
        setCoeff(coeff,power);

    //set the coeff and power
    }else{
        setCoeff(coeff,power);

    }
} // end of Poly

//---------------------------------Constructor-------------------------------
// Description: Creates a new poly object, requiring one value that is the
// coefficient of the zero exponent value
//---------------------------------------------------------------------------
Poly::Poly( int coeff ){

    //if this is a new poly then create an array of size one
    if(size == 0){
        size = 1;
        polyArray = new int[size];
    }

    //set the 0 value of the poly to the given value
    setCoeff(0 ,coeff);

} // end of Poly

//---------------------------------Constructor-------------------------------
// Description: Creates a new poly object that is a copy of another supplied
// poly object
//---------------------------------------------------------------------------
Poly::Poly( const Poly &toCopy ){

    //copies the supplied poly object
    copy(toCopy);

} // end of Poly

//---------------------------------Destructor--------------------------------
// Description: Destroys the current poly object
//---------------------------------------------------------------------------
Poly::~Poly() {

    //deletes the array and assigns the private pointer to NULL
    delete [] polyArray;
    polyArray = NULL;

} // end of Poly

//---------------------------------getCoeff----------------------------------
// Description: Returns an int value that is the coefficient of a given
// exponent value that is the parameter
//---------------------------------------------------------------------------
int Poly::getCoeff( int power ) const{

    //if the supplied power is not within the bounds of the poly object
    //return zero
    if(power < 0 || power >= size ){
        return 0;

    }

    //return the coefficient
    return polyArray[power];

} // end of getCoeff

//---------------------------------setCoeff----------------------------------
// Description: Sets the coefficient related to a provided exponent
// Parameters are the new coefficient value and the exponent that is applies
//---------------------------------------------------------------------------
void Poly::setCoeff(int newCoeff, int power){

    //if the supplied exponent is negative the coefficient cannot be set
    //thus exit the function
    if(power < 0){
        return;

    }
    //if the supplied exponent is larger than the current poly then increase
    // the size of the current poly
    if(power >= size){
        increase(power);

    }

    //set coefficient value at the specified exponent
    polyArray[power] = newCoeff;

} // end of setCoeff

//---------------------------------operator+---------------------------------
// Description: Add 2 poly objects together and return there new added
// together value
//---------------------------------------------------------------------------
Poly Poly::operator+( const Poly& rhs ) const{

    //create a new empty poly object
    Poly added = Poly();

    //increase the size of the new poly object to whichever of the two polys
    //being added together is larger
    if(size<rhs.size){
        added.increase(rhs.size-1);

    }else{
        added.increase(size-1);

    }

    //add together the cofficients at each exponent value
    for(int i = 0; i < added.size; i++){
        added.setCoeff( (getCoeff(i) + rhs.getCoeff(i)), i );

    }

    //return the new poly object that is the two added together
    return added;

} //end of +

//---------------------------------operator+---------------------------------
// Description: Add an int value to a poly object. This int value will
// correlate to the 0 exponent in the poly object.
//---------------------------------------------------------------------------
Poly Poly::operator+( const int& rhs ) const{

    //create a copy of poly object that is being added to
    Poly added = Poly(*this);

    //add the int to the 0 exponent slot in the new poly object
    added.setCoeff(added.getCoeff(0)+rhs, 0);

    //return the new poly object
    return added;

} //end of +

//---------------------------------operator- --------------------------------
// Description: Subtract  1 poly object from another
//---------------------------------------------------------------------------
Poly Poly::operator-( const Poly& rhs ) const{

    //create a new empty poly object
    Poly subbed = Poly();

    //increase the size of the new poly object to whichever of the two polys
    //being added together is larger
    if(size<rhs.size){
        subbed.increase(rhs.size-1);

    }else{
        subbed.increase(size-1);

    }

    //subtract the right coefficient from the left at each exponent value
    for(int i = 0; i < subbed.size; i++){
        subbed.setCoeff( (getCoeff(i) - rhs.getCoeff(i)) , i);

    }

    //return the new poly object
    return subbed;

} // end of -

//---------------------------------operator- --------------------------------
// Description: Subtract an int value to a poly object. This int value will
// correlate to the 0 exponent in the poly object.
//---------------------------------------------------------------------------
Poly Poly::operator-( const int& rhs ) const{

    //create a copy of the poly object that is being subtracted from
    Poly subbed = Poly(*this);

    //subtract the int to the 0 exponent slot in the new poly object
    subbed.setCoeff(subbed.getCoeff(0)-rhs, 0);

    //return the new poly object
    return subbed;

} // end of -
//---------------------------------operator*---------------------------------
// Description: Multiply two polynomial values together
//---------------------------------------------------------------------------
Poly Poly::operator*( const Poly& rhs ) const{

    //add together the two leading coefficients from both poly obects that
    //are being multiplied together to give you the size of your new poly
    //object, then create that object
    int maxPower = (rhs.size-1) + (size-1);
    Poly multi = Poly(0, maxPower);

    //iterate through each combination of indices of the two polys, added
    //there multiplied value to the existing value in the poly
    for(int i = 0; i < size; i++){
        for(int j = 0; j < rhs.size; j++){

            multi.setCoeff( multi.getCoeff(i+j) + (getCoeff(i) * rhs.getCoeff(j)), i+j);

        }

    }

    //return the new poly
    return multi;

} // end of *

//---------------------------------operator*---------------------------------
// Description: Multiply a poly by a given int value
//---------------------------------------------------------------------------
Poly Poly::operator*( const int& rhs ) const{

    //create a copy of the poly that is being multipled
    Poly multi = Poly(*this);

    //multiply each of its coefficients by the supplied int value
    for(int i = 0; i < multi.size; i++){
        multi.setCoeff( multi.getCoeff(i) * rhs, i);

    }

    //return the new poly
    return multi;

} // end of *

//---------------------------------operator=---------------------------------
// Description: Assign one poly new values that is a copy of another supplied
// poly
//---------------------------------------------------------------------------
const Poly& Poly::operator=( const Poly& rhs ){

    //if both polys are different than delete the current poly
    //and copy over the data from the new poly
    if (&rhs != this) {
        delete [] polyArray;
        copy(rhs);

    }

    //return the current poly
    return *this;
} // end of =

//---------------------------------operator*=--------------------------------
// Description: Modify the current poly by multiplying it by another poly
//---------------------------------------------------------------------------
Poly& Poly::operator*=( const Poly& rhs ){

    //multiply this poly by the one supplied and reassign that poly to this
    *this = *this * rhs;

    //return the updated poly
    return *this;

} // end of *=

//---------------------------------operator+=--------------------------------
// Description: Modify the current poly by adding another poly from it
//---------------------------------------------------------------------------
Poly& Poly::operator+=( const Poly& rhs ){

    //added this poly to the one supplied and reassign it to this poly
    *this = *this + rhs;

    //return the updated poly
    return *this;

} // end of +=

//---------------------------------operator-=--------------------------------
// Description: Modify the current poly by subtracting another poly
// from it
//---------------------------------------------------------------------------
Poly& Poly::operator-=( const Poly& rhs ){

    //subtract the given poly from this poly and reassign the new poly to
    //this poly
    *this = *this - rhs;

    //return the updated poly
    return *this;

} // end of -=

//---------------------------------operator==--------------------------------
// Description: Compare if two poly objects are the same and true/false
//---------------------------------------------------------------------------
bool Poly::operator==( const Poly& rhs ) const{

    //if the sizes are different then they are not the same
    if(size != rhs.size){
        return false;

    }

    //compare each number, if any two in the same indice are different then
    //the two polys are different
    for(int i = 0; i < size; i++){
        if( getCoeff(i) != rhs.getCoeff(i) ){
            return false;

        }
    }

    //one completely compared if a return hasn't already been hit then the
    //two objects are the same thus return true
    return true;

} // end of ==

//---------------------------------operator!=--------------------------------
// Description: Compare if two poly objects are not the same and true/false
//---------------------------------------------------------------------------
bool Poly::operator!=( const Poly& rhs ) const{

    //if the sizes are different then they are not the same
    if(size != rhs.size){
        return true;

    }

    //compare each number, if any two in the same indice are different then
    //the two polys are different
    for(int i = 0; i < size; i++){
        if( getCoeff(i) != rhs.getCoeff(i) ){
            return true;

        }

    }

    //one completely compared if a return hasn't already been hit then the
    //two objects are the same thus return false
    return false;

} // end of !=

//---------------------------------operator+---------------------------------
// Description: Create a poly object with given inputs from the user.
// User is restricted to positive int exponents, and int coefficients.
// 2 values have to be entered at a time, single value polynomials cannot be
// created this way. If two pairs are entered with the same exponent the
// the second pair will override the first
// To exit the input the user must type -1 -1
//---------------------------------------------------------------------------
istream& operator>>( istream &in, Poly &rhs ){

    //get the two first values from the user
    int coeff, power;
    in >> coeff;
    in >> power;


    while(coeff != -1 && power != -1){
        //increase the size of the poly if a entered exponent value is greater
        //than the current array
        if(rhs.size-1 < power){
            rhs.increase(power);

        }

        //set the input values to there respective place in the poly array
        rhs.setCoeff(coeff, power);

        //get 2 new values from the user
        //and continue the process until -1 -1 is entered
        in >> coeff;
        in >> power;

    }

    //return input stream
    return in;

} // end of >>

//---------------------------------operator<<--------------------------------
// Description: Print the poly array to the users screen
//---------------------------------------------------------------------------
ostream& operator<<( ostream &out, const Poly &rhs ){

    //flag the keeps track if the poly is empty
    //which is a special print circumstance
    bool zeroFlag = true;

    //iterate through each indice in the poly array, starting at the largest
    //as that is how polynomials are written
    for( int i = rhs.size ; i > 0; i-- ){
        //if the coefficient is zero it is not printed
        if(rhs.getCoeff(i-1) != 0){

            //flag is flipped once at least one value in the poly
            //is going to be printed
            zeroFlag = false;

            //all positive numbers have a + added before the numeral
            //to create a proper looking polynomial

            //exponent 0 is a special case and does not include x or the
            //exponent when printed
            if(i-1 == 0){
                if(rhs.getCoeff(i-1) >= 0){
                    out << "+" << rhs.getCoeff(i-1) << " ";

                }else{
                    out << rhs.getCoeff(i-1) << " ";

                }
            //exponent 1 is a special case and does not include the
            //exponent when printed
            }else if(i-1 == 1){
                if(rhs.getCoeff(i-1) >= 0){
                    out << "+" << rhs.getCoeff(i-1) << "x" << " ";

                }else{
                    out << rhs.getCoeff(i-1) << "x" << " ";

                }
            //all other values that have have both coefficient, x, and there
            //exponent printed
            }else{
                if(rhs.getCoeff(i-1) >= 0){
                    out << "+" << rhs.getCoeff(i-1) << "x^" << i-1 << " ";

                }else{
                    out << rhs.getCoeff(i-1) << "x^" << i-1 << " ";

                }

            }
        }



    }
    //if the flag isn't flipped then it is an empty poly whose value is 0
    //thus only 0 is printed to the user
    if(zeroFlag == true){
        out <<" 0";

    }
    //return ostream
    return out;

} // end of <<

//---------------------------------increase----------------------------------
// Description: Increases the size of a poly object to a new size (int power)
//---------------------------------------------------------------------------
void Poly::increase(int power){

    //if the given value is smaller than the poly object then nothing happens
    if(power < size){
        return;

    }

    //create a copy of the old poly array and size for future copying
    int* oldArray = polyArray;
    int oldSize = size;

    //create the new poly array and fill it with 0's
    size = power + 1;
    polyArray = new int[power];
    fill();

    //fill the new poly array with the value from the old array
    for(int i = 0; i < oldSize; i++){
        polyArray[i] = oldArray[i];

    }

    //delete the old array
    delete [] oldArray;
    oldArray = NULL;

} // end of increase

//---------------------------------fill--------------------------------------
// Description: Assigns 0 to all indices of a poly array
//---------------------------------------------------------------------------
void Poly::fill() {

    //iterates through each indice and sets its value to 0
    for( int i = 0; i < size; i++ ){
        setCoeff(0, i);

    }

} // end of fill

//---------------------------------copy--------------------------------------
// Description: Creates a deep copy of a supplied poly object
//---------------------------------------------------------------------------
void Poly::copy(const Poly& copy) {

    //copies size of the given poly and creates a new array of that size
    size = copy.size;
    polyArray = new int[size];

    //copies each element of the given poly to the new poly
    for (int i = 0; i < size; i++) {
        setCoeff(copy.getCoeff(i), i);

    }

} // end of copy