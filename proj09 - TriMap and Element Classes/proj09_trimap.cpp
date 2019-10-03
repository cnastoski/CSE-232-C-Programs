/*
Chris Nastoski
11/18/17
Section 012
Project 09

This program demonstrates the use of classes and introduces the TriMap. Another
class, "Element", is made and contains 3 members which are keys, values and indicies.
The TriMap sorts the Elements by their keys, but also keeps track of their values
and indicies, so that the user can look up an element by any of the three values.

*/

#include<string>
using std::string;
#include<iostream>
using std::ostream;using std::cin;using std::cout;using std::endl;
using std::boolalpha;
#include<vector>
using std::vector;
#include<initializer_list>
using std::initializer_list;
#include<sstream>
using std::ostringstream;
#include<algorithm>
using std::sort; using std::find_if;using std::upper_bound;
using std::binary_search;

#include "proj09_trimap.h"

//<< operator friend function for an Element. Takes in an element and an ostream.
//converts the element into a string and pipes it out to an ostrem.
ostream& operator<<(ostream& out, const Element &e){
  ostringstream oss;
  oss<<e.key_<<':'<<e.value_<<':'<<e.index_;
  string s = oss.str();
  out << s;//sends the ostringstream to the output stream
  return out;
}

//same as above operator funtion, but with an entire TriMap
ostream& operator<<(ostream& out, const TriMap &m){
  ostringstream oss;
  for(auto e : m.vec_){//pipes each element into oss with a comma
    oss<<e<<", ";
  }
  string s = oss.str();
  out << s.substr(0,s.size()-2);//gets rid of the unwanted excess punctuation
  return out;
}

//constructor using only one element
TriMap::TriMap(const Element& e){
  vec_.push_back(e);//adds to an empty vec_
  sz_ = vec_.size();
}

//constructor using a list of elements
TriMap::TriMap(initializer_list<Element> elem){
  sz_ = elem.size();

  size_t i = 0;//beginning index
  for(auto e : elem){
    e.index_ = i;//sorts each element's insertion order by the index
    vec_.push_back(e);
    ++i;
  }

  //uses a lambda to sort the vector<Element> by its keys in ascending order
  sort(vec_.begin(),vec_.end(),
      [] (const Element &elem1, const Element &elem2)
      {return elem1.key_ < elem2.key_;} );

}

//returns the size of the vector
size_t TriMap::size(){
  return sz_;
}

/*
Inputs: string k - key of the Element, string v - value of the Element
  Checks each element in the vector to see if there are conflicting keys, if not,
  creates and adds the new element.

Returns: bool inserted - whether or not the new element was succesfully inserted

*/
bool TriMap::insert(string k, string v){
  bool inserted = true;//init the bool
  for (auto elem : vec_){//iterates through each Element
    if(k == elem.key_){//does nothing if the key is already taken
      inserted = false;
      return inserted;
    }
    else{
      inserted == true;
    }

  }
  //if there are no confliting keys, makes a new Element
  sz_ += 1;//adds one to the size of TriMap
  Element e(k,v,vec_.size());//creates a new Element
  vec_.push_back(e);
  sort(vec_.begin(),vec_.end(),//re-sorts the vector by key
      [] (const Element &elem1, const Element &elem2)
      {return elem1.key_ < elem2.key_;} );

  return inserted;
}

/*
Inputs: string k - key of the Element in question
  Checks to see if the key is in the map, then removes it if it is

Returns bool removed - whether or not the element was removed
*/
bool TriMap::remove(string k){
  bool removed = false;
  for (auto i = vec_.begin();i != vec_.end();++i){//uses an iterator to parse through the vec
    if(k == i->key_){//checks what the iterator points to
      removed = true;
      sz_ -= 1;//adjusts the size

      size_t ind = i->index_;//sets the bottom index to be changed
      for(auto ptr = vec_.begin(); ptr != vec_.end();++ptr){
        //changes all the indicies above the one removed to compensate for insertion order
        if(ind < ptr->index_){
          ptr->index_-=1;
        }
      }
      vec_.erase(i);//removes the Element
      return removed;
    }

  }

   return removed;
}


/*
Inputs: string k - the key to find
  Uses the upper_bound algorithm to find the upper bound of the key, and then uses
  that to find the key if it exists.


Returns: * (&iter) a pointer to the position of the found key
*/
Element* TriMap::find_key(const string& k){
  Element m(k,"a",99);//random element with the wanted key
  vector<Element>::iterator iter;//iterator init
  iter = upper_bound(vec_.begin(),vec_.end(),m,
  [] (const Element &lhs,const Element &rhs) {return lhs.key_ < rhs.key_;});
  //use upper_bound to find they key
 --iter;//since it finds he upper_bound, the key will be the one before the upper_bound

  if(iter->key_ == k ){//if the key is the one we want
    return  &(*iter);
  }
  else{
    return nullptr;//if it isnt, we return a 0 pointer
  }
}

/*
Input: string val - the value of the Element
  Uses find_if to find the Element with the wanted value.

Returns -  A pointer to the Element with the wanted value
*/
Element* TriMap::find_value(const string& val){
  vector<Element>::iterator iter = find_if(vec_.begin(),vec_.end(),
          [val] (const Element &elem) {return elem.value_ == val; });
  //Iterates though each vec value until it finds the one with the value we want
  if(iter != vec_.end()){
    return  &(*iter);//returns the pointer to that position if it finds it

  }
  else{
    return nullptr;
  }

}


/*
Input: size_t idx - the index of the Element
  Uses find_if to find the Element with the wanted index.

Returns -  A pointer to the Element with the wanted index
*/
Element* TriMap::find_index(size_t idx){
  vector<Element>::iterator iter = find_if(vec_.begin(),vec_.end(),
          [idx] (const Element &elem) {return elem.index_ == idx; });

  //same as before but with index

  if(iter != vec_.end()){
    return  &(*iter);
  }

  else{
    return nullptr;
  }

}
