#include<string>
using std::string;
#include<vector>
#include<sstream>
using std::ostringstream;
#include<cmath>
#include<iomanip>
using std::setprecision;
#include<iostream>
using std::fixed;

#include "proj08_twod.h"

/*
Chris Nastoski
11/3/17
Section 012
Project 08

This Program introduces the basics of classes and structures in c++. It utilizes
them to tackle a fundamental physics problem in gaming and many other physics
intensive projects. A class called TwoD is created and represents a two-dimensional
vector. The class inclues several vector manipulation techniqus such as dot product,
scalar multiplication, difference and magnitude squared.

*/


//constructor with two variables
TwoD::TwoD(double xval, double yval){
    x = xval;
    y = yval;
}

//represents the object as a string
string TwoD::to_string(){
  ostringstream oss;
  oss<<fixed<<setprecision(2);
  oss<<"("<<x<<", "<<y<<')';
  return oss.str();
}

//takes two vectors and subracts one from the other
TwoD TwoD::diff(TwoD v2){
  TwoD diff_vector;
  diff_vector.x = x - v2.x;//x1 - x2
  diff_vector.y = y - v2.y;//y1 - y2

  return diff_vector;
}

//multiplies each component of the vector by a scalar
TwoD TwoD::mult(double scalar){
    TwoD mult_vector;
    mult_vector.x = this->x * scalar;
    mult_vector.y = this->y * scalar;

    return mult_vector;
}

//performs the dot product of two vectors.
//Dot Product: https://en.wikipedia.org/wiki/Dot_product
double TwoD::dot_product(TwoD v2){
    double scalar = 0;
    scalar += this->x * v2.x;
    scalar += this->y * v2.y;
    return scalar;
}


//uses the pythagorean's theorem to find the magnitude of the vector and then
//squares it
double TwoD::magnitude_squared(){
    double pythag;
    pythag = pow(x,2)+pow(y,2);//only the radicand is needed for magnitude_squared 
    return pythag;
}
