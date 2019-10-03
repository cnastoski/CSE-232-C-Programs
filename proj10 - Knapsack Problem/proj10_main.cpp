#include<iostream>
using std::cout; using std::endl;
#include<vector>
using std::vector;
#include<algorithm>
using std::copy;
#include<iterator>
using std::ostream_iterator;
#include<string>
using std::string; using std::to_string;
#include<iomanip>
using std::boolalpha;
#include<cassert>
#include "proj10_package.h"
#include "proj10_knapsack.h"

int main(){

  cout << boolalpha;


  Knapsack ks2(51, 3);

  solve_KS("packages.txt", ks2);
  cout << ks2 << endl;
  cout << "Weight:"<<ks2.weight() << endl;
  cout << "Priority:"<<ks2.priority() << endl;

}
