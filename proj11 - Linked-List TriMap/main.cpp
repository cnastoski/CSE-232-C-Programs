#include<iostream>
using std::ostream; using std::cout; using std::endl;
#include<sstream>
using std::ostringstream;
#include<utility>
using std::swap;
#include<string>
using std::string;

#include "proj11_trimap.h"


int main(){
  cout<<std::boolalpha;
  // Element<int,int> e(1,2,0);
  // TriMap<int,int> m(1,2);
  //cout<<p<<endl;
  // m.insert(4,2);
  // m.insert(3,3);
  // m.insert(9,4);
  // m.insert(50,9);
  // m.insert(2,3);
  // cout<<m.remove(9)<<endl;
  // TriMap<int,int> p(m);
  // cout<<m<<endl;

  TriMap<long,long> m1;
  m1.insert(2,20);
  m1.insert(1,10);
  m1.insert(4,40);
  m1.insert(3,30);

  TriMap<long, long> m2(m1);
  m2.insert(5,50);
  cout<<m2<<endl;
  m2.remove(4);
  cout<<m1<<endl;
  cout<<m2<<endl;

}
