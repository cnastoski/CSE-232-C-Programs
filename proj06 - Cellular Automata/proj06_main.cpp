#include<iostream>
using std::cout; using std::endl; using std::boolalpha;
#include<string>
using std::string;
#include<vector>
using std::vector;

#include "proj06_functions.h"

int main (){
  cout << boolalpha;
  vector<int> v{0,0,0,1,0,0,0};
  cout<<next_val(v, "00011110")<<endl;


}
