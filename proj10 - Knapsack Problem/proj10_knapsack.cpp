
/*
Chris Nastoski
11/29/17
Section 012
Project 10


A class the represents a knapsack that is used to hold Packages. The Knapsack uses
dynamically allocated arrays to hold the packages and has a set weight limit that
cannot be surpassed.
*/


#include<iostream>
using std::cout; using std::endl;using std::ostream;
#include<vector>
using std::vector;
#include<algorithm>
using std::copy; using std::sort;
#include<iterator>
using std::ostream_iterator;
#include<string>
using std::string; using std::to_string;using std::stol;
#include<iomanip>
using std::boolalpha;
#include<cassert>
#include<array>
using std::array;
#include<sstream>
using std::ostringstream;
#include<stdexcept>
using std::runtime_error;
#include<fstream>
using std::ifstream;

#include "proj10_knapsack.h"
#include "proj10_package.h"

//ctor with one arg.
//creates an empty Knapsack with a set weight limit
Knapsack::Knapsack(size_t limit){
  weight_limit_ = (long)limit;
  capacity_ = 10;
  size_ = 0;
  data_ = new Package[capacity_];//sets the array
}

//ctor with 2 args
//creates an empty knapsack with a set weight limit and a beginning capacity that
//can be upgraded to hold more packages
Knapsack::Knapsack(size_t wlimit, size_t cap){
  weight_limit_ = (long)wlimit;
  capacity_ = (long)cap;
  size_ = 0;
  data_ = new Package[capacity_];
}

//copy ctor with another Knapsack
//copies contents of one Knapsack to a new Knapsack
Knapsack::Knapsack(const Knapsack& bag){
  weight_limit_ = bag.weight_limit_;
  capacity_ = bag.capacity_;
  size_ = bag.size_;
  data_ = new Package[capacity_];
  copy(bag.data_,bag.data_+capacity_,data_);//copy of the array to the new Knapsack
}

//dtor of a Knapsack
Knapsack::~Knapsack(){
  delete [] data_;
}

//Inputs: Knapsack bag - the knapsack to swap data with
//Takes in a Knapsack and swaps it with another
void Knapsack::swap(Knapsack& bag){
  //swaps each data member
  std::swap(bag.weight_limit_,weight_limit_);
  std::swap(bag.capacity_,capacity_);
  std::swap(bag.size_,size_);
  std::swap(bag.data_,data_);
}

//uses a copy ctor to create another Knapsack with the same data members as
//another Knapsack
Knapsack& Knapsack::operator=(const Knapsack bag){
  Knapsack cpy_bag(bag);//copy a Knapsack
  cpy_bag.swap( *this);//swap contents with current Knapsack

  return *this;//returns the derefrenced ptr which is the Knapsack
}

//returns the current Knapsack capacity
long Knapsack::capacity() const{
 return capacity_;
}

//returns the current Knapsack size
long Knapsack::size() const{
 return size_;
}

//returns the current Knapsack weight limit
long Knapsack::weight_limit() const{
  return weight_limit_;
}

//returns a bool saying if the Knapsack has any Packages inside of it or not
bool Knapsack::empty() const{
  return size_== 0;
}

//sums all of the package weights inside of the Knapsack
long Knapsack::weight() const{
  if(size_ == 0){//weightless if it it empty
    return 0;
  }

  else{
    long sum = 0, i;
    for(i=0; i<size_; ++i){//iterates through all Packages
      sum += data_[i].weight_;//adds the weights to the total

    }
    return sum;

  }

}

//same as the Weight() fn, but with the priorites
long Knapsack::priority() const{
  if(size_ == 0){
    return 0;
  }
  else{
    long sum = 0, i;
    for(i=0; i<size_; i++){
      sum += data_[i].priority_;

    }
    return sum;
  }

}

//Inputs: const Package& bag - the Package to add
//checks to see if the package can fit inside of the Knapsack and returns a bool
//pertaining to whether it was added or not
bool Knapsack::add(const Package& bag){
  Knapsack k(*this);//used as a refrence for the current Knapsack
  long new_wght = k.weight() + bag.weight_;//the modified weight
  if(new_wght > weight_limit_){//if it cannot fit the Package
    return false;
  }
  else{
    if(k.capacity_ > (k.size())){//if there is enough space in the array
      data_[size_] = bag;//sets the next open mem location to the new Package
      ++size_;
      return true;
    }
    else{//if the array cannot fit another Package
      Package *new_data = new Package[2 * capacity_];//creates a new array that is bigger
      copy(data_, data_+capacity_, new_data);//copies all data from old to new ary
      capacity_  = 2 * capacity_;//new capacity_
      std::swap(data_,new_data);//new data becomes data member
      delete [] new_data;//no need for old data
      data_[size_] = bag;//adds the Package
      ++size_;
      return true;
    }

  }

}

//Inputs: string file - the file name to open
//        Knapsack bag - The Knapsack to fill with items from file
//Opens a file full of packages and adds them to a vector and sorts them, then
//adds the most valuble ones to the knapsack until it hits a Package that is too
//big
void solve_KS(string file , Knapsack& bag){
  ifstream input;
  input.open(file);
  if(!input.is_open()){//error checking to see if the file opened
    throw runtime_error("");
  }

  long weight,priority;
  vector<Package> temp;
  while(input>>weight>>priority){//iterates through the file
    Package pkg(weight,priority);//creates a new Package per line
    temp.push_back(pkg);//adds them all to a temporary vector
  }

  sort(temp.begin(),temp.end(),package_compare);
  //sorts the vector based on the Package priority/weight ratio


  for(auto i = 0; i<= temp.size();++i){//iterates through each Package
    bag.add(temp[i]);
    if(bag.weight_limit_<bag.weight()+temp[i].weight_){
      //this is the only way I could get the code to stop without any
      //extraneous errors, i'm not sure why
      i = temp.size()+1;
      break;
    }

  }

}


//Prints out the contents of the Knapsack
ostream& operator<<(ostream& out, Knapsack& bag){
  ostringstream oss;
  for(long i = 0; i< bag.size_; ++i){//iterates through all items in Knapsack
    oss<<bag.data_[i]<<", ";
  }
  string s = oss.str();//turns the oss into a string
  out<<s.substr(0,s.size()-2);
  return out;
}
