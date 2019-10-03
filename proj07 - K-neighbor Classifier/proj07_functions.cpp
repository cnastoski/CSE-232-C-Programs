#include<iostream>
using std::cout; using std::endl; using std::ostream;
#include<string>
using std::string;using std::stod;
#include<vector>
using std::vector;
#include<map>
using std::map;
#include<fstream>
using std::ifstream;
#include<utility>
using std::pair;
#include<sstream>
using std::istringstream; using std::ostringstream;
#include<stdexcept>
using std::invalid_argument;
#include<iomanip>
using std::setprecision;using std::fixed;
#include<cmath>
#include<algorithm>
using std::copy_if;
#include<iterator>


#include "proj07_functions.h"

/*
Chris Nastoski
10/29/17
Section 012
Project 07

This program introduces the basics of machine learning by attempting to classify
a set of data points to the type of flower by finding its nearest neighbors and
checking to see if they match the type of the point in question.
*/



/*
Inputs: string s, char delim defaulted to ' '
Returns: a vector<string> with the elements that a split by the deliminator.

Function takes in a string and a character and returns a vector who's elements
are the strings that were split by the delim.
*/
vector<string> split(const string &s, char delim){
  vector<string> split_str = {};//init vector
  int pos = 0;//position
  std::size_t found = 0;//init size type
  while(found!=string::npos){//loops while found is in the string range
    found = s.find(delim,pos);//splits string
    split_str.push_back(s.substr(pos,found-pos));//adds it to the vector
    pos = (found+1);
  }
  return split_str;
}


/*
Inputs: map m: a map of pairs of vectors and strings
        int feature_count - the number of elements in the vector<double>
        ifstream inf - the stream to get information out of

Returns: Nothing, but fills the map m with data

Function takes an empty map m and fills it with data from inf.
*/
void read_data(map<vector<double>, string> &m, unsigned int feature_count, ifstream &inf){
  string line;
  while(getline(inf,line)){//reads through each line of data
    vector<double> features;//reinitilizes a vector and pair for each line
    pair<vector<double>,string> set;
    vector<string> str = split(line,',');//splits the line by its commas

    for(auto i=0;i<=feature_count;i++){//tries to add each feature to the vector
      try{
        features.push_back(stod(str[i]));
      }
      catch(invalid_argument& e){
        //for some reason the file ends with the name of a flower type so This
        //catch block stops the code as before that so it doesnt crash
        break;
      }
    }//of for

    set.first = features;//adds the vector of doubles
    set.second = str.back();//adds the last element of the line which is the flower type
    m.insert(set);//adds the pair to the map
  }//of while

}

/*
Inputs: pair of vector<double> and string  p - a pair
Returns: string - the converted pair to a string

Function takes in a pair and returns a string full of the information of that pair
*/
string pair_to_string(const pair<vector<double>, string> &p){
  vector<double> vals = p.first;
  ostringstream oss;//initilize the output stream
  for(auto element : vals ){//iterates through each element in the vector
    oss<<fixed<<setprecision(3);//sets the format
    oss<<element<<" ";//pipes each element to the stringstream
  }
  string last = oss.str();//converts oss to a string
  last += p.second;//second value is already a string
  return last;
}

/*
Inputs: map of pairs of vectors and strings
        an output stream to pipe to
Returns: nothing, but prints out the map to whatever output stream you want

Function takes in a map and prints it out to any output stream
*/
void print_map(const map<vector<double>, string> &m, ostream &out){
  for(auto element : m){//calls fn to print out each pair line by line
    out<<pair_to_string(element)<<endl;
  }
}

/*
Inputs: two vectors v1,v2  int feature_count which is the same as before
Returns: a double

Function utilizes the distance formula to find the euclidean distance between
two points which are represented by the vectors v1 and v2.
*/
double distance(const vector<double> &v1,
                const vector<double> &v2,
                unsigned int feature_count){

  double total = 0;
  for(auto i=0 ;i<=feature_count;i++){
    total += pow(v1[i]-v2[i],2);
    //adds up all of the x,y,z... differences squared from each vector
  }
  return sqrt(total);
}

/*
Inputs: string s, char delim defaulted to ' '
Returns: a vector<string> with the elements that a split by the deliminator.

Function takes in a string and a character and returns a vector who's elements
are the strings that were split by the delim.
*/
map<vector<double>, string> k_neighbors(const map<vector<double>,
                    string> &m, const vector<double> &test,
                    int k){
                      
  map<vector<double>, string> last;//init the map to return
  int i =0;
  while(i<k+1){//loops until we get the k number of neighbors
    pair<vector<double>,string> one_pair;
    double min_dist = 35.50;//set an arbitrary minimum dist which is pretty large

    for(auto element:m){//iterate through each element in map

      if(last.count(element.first)>0){
        continue;//skips if the pair is already in the final map
      }
      double pair_dist = distance(element.first,test,k);//find the distance
      if(pair_dist<=min_dist){
        min_dist = pair_dist;//set as new min_dist
        one_pair = element;//sets this as the new candidate for the closest dist

      }//of if

    }//of for
    last.insert(one_pair);
    //remove the pair since it cant be added again
    ++i;
  }
  last.erase(test);
  return last;
}


/*
Inputs: map m
        pair test the pair we want to find the neighbors of.
        int k - the number of neighbors we want to find

returns: double -  the ratio of correct types to the amount of types given.

Function calls k_neighbrs to create a map of k_neighbors and then uses the
value of each pair to compare to the value of the test pair and returns the ratio
of how many of the values matched the value of the test pair.
*/
double test_one(const map<vector<double>, string> &m, pair<vector<double>, string> test, int k){
  map<vector<double>, string> compare;//init compare map
  compare = k_neighbors(m,test.first,k);//create the compare map
  double ratio=0,correct = 0;//init

  for(auto element : compare){//iterate through compare
    if (element.second == test.second ){
      ++correct;
    }
  }
  ratio = correct/k;
  return ratio;
}

/*
Inputs: map m
        int k - the number of neighbors we want to find

returns: double -  the ratio of correct types to the amount of types given.

Function calls test_one for all elements in the map and creates the average of
all of the averages collected.
*/
double test_all(const map<vector<double>, string> &m, int k){
  double total = 0,denom = m.size();//the denominator will be the amt of pairs in m
  double ratio = 0;
  for(auto element:m){
    pair<vector<double>, string> p;//calls test_one for all pairs in map
    p = {element.first,element.second};//sets the element as the pair
    double single_acc = test_one(m,p,k);//adds the averge of that fn to the total
    total += single_acc;
  }
  ratio = total/denom;
  return ratio;

}
