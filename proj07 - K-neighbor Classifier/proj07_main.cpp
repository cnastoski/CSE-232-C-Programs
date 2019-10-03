#include<iostream>
using std::cout; using std::endl; using std::ostream;
#include<string>
using std::string;
#include<vector>
using std::vector;
#include<map>
using std::map;
#include<fstream>
using std::ifstream;
#include<utility>
using std::pair;

#include "proj07_functions.h"

int main (){
  pair<vector<double>,string> p;
  string s = "6.3,2.9,5.6,1.8,Iris-virginica";
  map<vector<double>,string> m,n;
  ifstream file,file_2;
  file.open("little.txt");
  file_2.open("iris.data.txt");
  read_data(m,4,file);
  read_data(n,4,file_2);
  p = {{6.3,2.9,5.6,1.8},"Iris-virginica"};
  print_map(k_neighbors(m,p.first,4),cout);
  cout<<test_one(m,p,3)<<endl;
  cout<<test_all(m,3)<<endl;
  cout<<test_all(n,3)<<endl;
  return 0;
}
