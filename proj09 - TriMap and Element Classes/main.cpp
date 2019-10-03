#include<string>
using std::string;
#include<iostream>
using std::ostream;
#include<vector>
using std::vector;
#include<initializer_list>
using std::initializer_list;
#include<iostream>
using std::cin;using std::cout;using std::endl;
using std::boolalpha;

#include "proj09_trimap.h"



int main(){
  //Element e("my man","my boy",0);
  //TriMap m({e,{"hey","man",2},{"zed","is",1}});
  TriMap m;
  m.insert("w","x");
  m.insert("c", "d");
  m.insert("a","b");
  m.insert("y","z");
  m.insert("g","f");
  m.insert("j","d");
  Element* result = m.find_key("c");

  cout<<*result<<endl;
  cout<<m<<endl;

  cout<<boolalpha;

}
