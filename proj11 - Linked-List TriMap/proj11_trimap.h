/*
Chris Nastoski
12/06/17
Section 012
Project 10

A header file containing the templated classes Element and TriMap. This program
is another take at the TriMap container, but this time the underlying
structure is a single linked list. A data cell called an Element is linked together
by a pointer to its next cell, which is all encased between the head_ and the tail_
of the TriMap. An element in the TriMap can be searched up by any of it's three
data members and is sorted in key order.
*/

#ifndef SINGLELINK_H
#define SINGLELINK_H

#include<iostream>
using std::ostream; using std::cout; using std::endl;
#include<sstream>
using std::ostringstream;
#include<utility>
using std::swap;
#include<string>
using std::string;

// forward declaration so we can make Element a friend of TriMap
template<typename K, typename V>
class TriMap;

// private Element, friend of TriMap class
template <typename K, typename V>
class Element{

private:
  K key_;
  size_t index_ = 0;
  Element *next_ = nullptr;

public:
  V value_;

  Element() = default;
  Element(K key, V val, size_t i) : key_(key),index_(i), next_(nullptr), value_(val) {};

  // *defined* in the class, makes templating easier.
  friend ostream& operator<<(ostream& out, Element& e){
    out <<e.key_ << ":" << e.value_ << ":" << e.index_;
    return out;
  }
  friend class TriMap<K,V>;
};


template<typename K, typename V>
class TriMap{

private:
  Element<K,V> *head_ = nullptr;
  Element<K,V> *tail_ = nullptr;
  size_t size_ = 0;

  // a private function, used by operator<<
  void print_list(ostream& out);

public:
  TriMap() = default;
  TriMap(K, V);
  TriMap(const TriMap&);
  TriMap& operator=(TriMap);
  ~TriMap();
  long size();
  bool insert(K,V);
  bool remove(K);
  Element<K,V>* find_key(K);
  Element<K,V>* find_value(V);
  Element<K,V>* find_index(size_t);

  // *defined* in the class, makes templating easier.
  // uses private method print_list
  //returns whatever print_list returns.
  friend ostream& operator<<(ostream& out, TriMap<K,V>& sl){
    sl.print_list(out);
    return out;
  };
};

//double arg constructor for TriMap
//takes in one Element and creates a TriMap with it
template<typename K, typename V>
TriMap<K,V>::TriMap(K key, V value){
  Element<K,V> elem(key,value,0);//makes the key and value into an Element
  Element<K,V>* ptr = new Element<K,V>(key,value,0);//creates a cell with the Element
  head_ = ptr;
  tail_ = ptr;
  ++size_ ;//size grows
};

/*
Inputs: TriMap tm - a trimap to be copied.

If the TriMap is not empty, it will make a pointer that walks down the line of
cells, copying each one into the other TriMap.

Returns: another Trimap with the exact same elements as the input.
 */
template<typename K, typename V>
TriMap<K,V>::TriMap(const TriMap& tm){
  if(tm.head_ != nullptr){//if it's not empty
    size_ = tm.size_;//copies size_
    head_ = new Element<K,V>(*(tm.head_));//creates the head_
    tail_ = head_;//starts out as size 1
    Element<K,V> *tm_ptr = tm.head_ -> next_;
    Element<K,V> *new_elem;
    while (tm_ptr != nullptr){//copies each cell until the end
	    new_elem = new Element<K,V>(*(tm_ptr));
	    tail_->next_ = new_elem;
	    tm_ptr = tm_ptr->next_;
	    tail_ = new_elem;
	}

  }
  else{//if the TriMap is empty, creates another empty one
    head_ = nullptr;
    tail_ = nullptr;
  }


}


//assignment operator for Trimap
template<typename K, typename V>
TriMap<K,V>& TriMap<K,V>::operator=(TriMap tm){
  swap(head_,tm.head_);//swaps each data member
  swap(tail_,tm.tail_);
  swap(size_,tm.size_);
  return(*this);//returns the swapped TriMap
}


// walk down the list using head_ , keeping a trailer pointer called to_del
// delete what to_del points to
// move head_ and to_del to the next node.
template<typename K, typename V>
TriMap<K,V>::~TriMap(){
  Element<K,V>* to_del = head_;
  while (to_del != nullptr){//deletes each cell as is goes along
    head_ = head_->next_;
    delete to_del;
    to_del = head_;
  }//resets the TriMap
  head_ = nullptr;
  tail_ = nullptr;

}


template<typename K, typename V>
long TriMap<K,V>::size(){
  return (long)size_;//cast the size_t to a long
}


/*
Inputs: K key - The key of the Element
        V value -  The value of the Element

Creates an Element from the key and value, and then puts it into the TriMap
if the key isn't already in it.

Returns: bool whether it was inserted or not
*/
template<typename K, typename V>
bool TriMap<K,V>::insert(K key, V value){
  Element<K,V> elem(key,value,size_);//creates element
  if(head_ == nullptr){//if the TriMap is empty
    head_ = new Element<K,V>(elem);//sets the Element as the first cell
    tail_ = head_;
    ++size_;//each insert raises the size of TriMap by 1
    return true;
  }

  else{
    TriMap<K,V> ref(*this);//a reference Trimap using *this
    if(ref.find_key(key)){
      return false;//if it is already inside TriMap
    }
    else{
      Element<K,V>* ptr = head_;//This will be the ptr before the cell
      Element<K,V>* front_ptr = ptr;//this will be the pointer to the cell
      int i = 0;//for the front_ptr

      for(ptr = head_; ptr != nullptr; ptr = ptr-> next_){
        if(i>1){//we want to have the pointer point to the cell before the pointer
          //so we start iterating after the first loop
          front_ptr= front_ptr -> next_;
        }

        if((*ptr).key_>key){
          //we loop through until we find the spot to put it in
          if(ptr == head_){
            elem.next_ = ptr;
            head_ = new Element<K,V>(elem);
            ++size_;
            return true;
            //we set the new Element as the head_ if it is inserted into the first pos
          }

          else{
            //if it is inserted somewhere in the middle
            elem.next_ = ptr;
            front_ptr -> next_ = new Element<K,V>(elem);
            ++size_;
            return true;

          }
        }

        if(ptr == tail_){
          //if it is inserted at the end
          ptr -> next_ = new Element<K,V>(elem);
          tail_  = tail_ -> next_;
          ++size_;
          return true;
        }
        ++i;//for the front_ptr
      }

    }
  }
  return false;

}


/*
Inputs: K key - the key we want to remove

Removes an Element based on it's key if it is in the TriMap

Returns: A bool wether we removed it or not
*/
template<typename K, typename V>
bool TriMap<K,V>::remove(K key){
  TriMap<K,V> &ref(*this);//reference TriMap
  if(ref.find_key(key)){//if it's in the TriMap
    Element<K,V>* target(ref.find_key(key));//makes a pointer to the Element
    if(head_ == target && tail_ == target){//if the Trimap is size 1
      delete target;//resets the TriMap
      head_ = nullptr;
      tail_ = nullptr;
      --size_;
      return true;
    }
    else{
      size_t tgt_size = target -> index_;//used to correct the indicies
      Element<K,V>* ptr = head_;//ptr to cell
      Element<K,V>* front_ptr = ptr;//ptr to one behind cell
      int i = 0;
      //this for loop is to correct the indicies of each Element
      for(ptr = head_; ptr != nullptr; ptr = ptr-> next_){
        if(ptr -> index_ > tgt_size){
          --(*ptr).index_;
        }
      }
      //this for loop is to remove the Element
      for(ptr = head_; ptr != nullptr; ptr = ptr-> next_){
        if(i>1){
          front_ptr  = front_ptr -> next_;
        }//for the front_ptr

        //sets the head as the next one in the TriMap
        if(target == head_){
          head_ = ptr-> next_;
          delete target;
          --size_;//size decreases
          return true;
        }
        //somwhere in the middle or end of the TriMap
        if(ptr == target){
          if(ptr == tail_){//if its the end we need to adjust the tail_
            delete target;
            front_ptr -> next_ = nullptr;
            tail_ = front_ptr;
            --size_;
            return true;
          }
          else{
            //if it's in the middle we need to adjust the next_ pointer for the one
            //before the removed cell
            front_ptr -> next_ = ptr -> next_;
            delete target;
            --size_;
            return true;
          }

        }
        ++i;
      }
    }
  }
  else{//if it isn't in the TriMap
    return false;
  }
  return false;//just in case all of the other cases didn't work
  //this one is just for debugging
}


//finds the Element based on key
template<typename K, typename V>
Element<K,V>* TriMap<K,V>::find_key(K key){
  Element<K,V>* ptr;
  //iterates through each cell in TriMap
  for(ptr = head_; ptr != nullptr; ptr = ptr-> next_){
    if(ptr->key_==key){
      return ptr;
    }
  }
  return nullptr;
  //returns nothing if it can't find it
}

//finds Element based on value
template<typename K, typename V>
Element<K,V>* TriMap<K,V>::find_value(V val){
  Element<K,V>* ptr;
  //same as before
  for(ptr = head_; ptr != nullptr; ptr = ptr-> next_){
    if(ptr->value_==val){
      return ptr;
    }
  }
  return nullptr;

}

//returns Element based on Insertion order
//same as above
template<typename K, typename V>
Element<K,V>* TriMap<K,V>::find_index(size_t i){
  Element<K,V>* ptr;
  for(ptr = head_; ptr != nullptr; ptr = ptr-> next_){
    if(ptr->index_==i){
      return ptr;
    }
  }
  return nullptr;

}

//This funtion gets used by the << operator
template<typename K, typename V>
void TriMap<K,V>::print_list(ostream &out){
  ostringstream oss;
  Element<K,V>* ptr;
  //sends each element from head_ to tail_ to oss
  for(ptr = head_; ptr != nullptr ; ptr =  ptr->next_){
    oss<<*ptr<<", ";
  };
  string s = oss.str();
  out<<s.substr(0,s.size()-2);//formatting
};


#endif
