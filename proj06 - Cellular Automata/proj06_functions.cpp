#include<string>
using std::string;
#include<vector>
using std::vector;
#include<algorithm>
using std::transform;
#include<iterator>
using std::ostream_iterator;
#include<sstream>
using std::ostringstream;
#include<cmath>
using std::pow;
#include<fstream>
using std::ifstream;

#include "proj06_functions.h"

/*
Chris Nastoski
10/22/17
Section 012
Project 06

Cellular Automaton: http://mathworld.wolfram.com/CellularAutomaton.html

This program demonstrates the simple 1D cellular automaton created by Stephen
Wolfram.It takes in a vector<int> of length 7 and splits it up into a cell of
three elements. The middle element is the cursor for how they get split up.
The other input is a number that is the basis for the rules. The number gets
converted into binary and is lined up with the vector of the cells from 0 to 7.
the cell of each of the broken up vectors is changed based on the rule and the
inital position of the cell. The final output is an iterated vector based on the
previous vector and the rules.
*/

/*
inputs: int val - any number between 0-255

Takes in a number and converts it into a binary string.

Returns: string binary- a binary string.
*/
string to_binary(int val){
    string binary = "";//init string
    if (val>255 or val<0){//error checking
      string empty(8,'0');//if not in range, sets string to all 0's

      return empty;
    }

    for(auto i=7;i>=0;--i){//code to convert to binary
        if (val>=pow(2,i)){
            binary += '1';
            val-=pow(2,i);
        }
        else
            binary += '0';
    }//of for
    return binary;
}

/*
inputs:  vector<int> v - a size 3 vector filled with binary values
         string rule_binary_string - the converted number into binary

The function takes in the binary vector and converts it back into decimal form.
then it uses that as the index which is matched up with the index of the binary
string to determine the next value of a cell.

Returns: int - either 1 or 0
*/

int next_val(const vector<int> &v, const string &rule_binary_string){
  int index = 7 - (v[0]*pow(2,2)+v[1]*pow(2,1)+v[2]*pow(2,0));
  //finds index by converting vector to a decimal

  return rule_binary_string[index]-48;//the -48 is to change from a char to int
}

/*
Inputs: vector<int> v - a vector of binary values
        string rule_binary_string - the number converted into binary

Function iterates through the vector v, calling next_val for each cell. Adds two
zeroes, one on each side of v so that the cells match up. Runs a for loop to
create each cell block.

Returns: vector<int> iterated vector - the next vector based on the previous and
the rules.
*/
vector<int> one_iteration(const vector<int> &v,const string &rule_binary_string){
  vector<int>  mod_vec = v ,iterated_vector;
  mod_vec.push_back(0);//adds 0 to the end
  mod_vec.insert(mod_vec.begin(),0);//adds 0 to the beginning

  for(int i=0;i<=6;++i){//iterates through the length of the vector
    vector<int>::const_iterator begin = mod_vec.begin();//start of cell block
	  vector<int>::const_iterator last = mod_vec.begin() + 3;//end of cell block
    vector<int> new_vec(begin+i,last+i);//creates the cell block

    iterated_vector.push_back(next_val(new_vec,rule_binary_string));
    //adds 1 or 0 to the iterated_vector
    new_vec.clear();//resets the vector to be constructed again
  }
  return iterated_vector;
}

/*
Inputs: same as before
Converts the vector of binary ints into a string representation of binary ints
Returns: string converted - a string of binary numbers
*/
string vector_to_string(const vector<int> &v ){
  string converted = "";//init string
  for(int element : v){//iterates from start to end of v
    converted += std::to_string(element)+",";
    //converts to string and adds a comma
  }

 return converted.substr(0,converted.size()-1) ;//deletes the excess comma
}

/*
Inputs: vector<int> v - same as before
        string file_str - a string that is the name of a file
Opens a file that contains space separated binary numbers and feeds each one
to a vector v if it is empty.
Returns: nothing
*/
void read_vector(vector<int> &v, string file_str){
    ifstream in_file(file_str);//declare file to open
    if(v.size()==0)//checks to see if v is empty
      if(in_file){//checks to see if file exists
        int binary;//input of file
        while(in_file >> binary){
          v.push_back(binary);//adds each input into v
        }//of while
      }//of if
}

// a freebie!
// takes in a vector of 0,1
// outputs a string of '_' or '*'
string pretty_print(vector<int> & v){
  ostringstream oss;
  transform(v.begin(), v.end(), ostream_iterator<char>(oss),
	    [] (int i) {
	      return (i==0) ? '_' : '*';
	    }
	    );
    return oss.str();
}
