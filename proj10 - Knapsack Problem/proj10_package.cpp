/*
Chris Nastoski
11/29/17
Section 012
Project 10


A class that represents a Package object that has a weight and a priority. It is
used with the Knapsack class to represent packages and boxes.
*/


#include<iostream>
using std::cin;using std::cout;using std::endl;using std::ostream;
#include<sstream>
using std::ostringstream;
#include<string>
using std::string;

#include "proj10_package.h"


//Inputs: ostream& out - the stream to send the Package contents.
//        Package&p - the Package to format.
//Pipes the formatted Package to a stream.
//Output ; ostream out- the stream to send the Package through
ostream& operator<<(ostream& out, Package& p){
  ostringstream oss;
  oss<<p.weight_<<":"<<p.priority_;//formatting of the Package
  string s = oss.str();
  out<<s;
  return out;

}


//Inputs: Package p1, Package p2: Two packages to compare
// Compares two packages based on their priority to weight ratio and returns
//a bool if the left one is bigger.
//Outputs: bool - whether or not the lhs package has a bigger ratio than the rhs
bool package_compare(const Package &p1, const Package &p2){
  double r1,r2;
  r1 = (double)p1.priority_/(double)p1.weight_;
  r2 = (double)p2.priority_/(double)p2.weight_;
  return (r1>r2);
}
