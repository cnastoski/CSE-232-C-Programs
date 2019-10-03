#ifndef STUDENT
#define STUDENT

#include<initializer_list>
using std::initializer_list;


namespace student{
  template<typename T>
  class vector{
    private:
      T *data_;
      size_t capacity_ = 10;
      size_t size_ = 0;
    public:
      vector(size_t capacity): capacity_(capacity),size_(0),data_(*capacity_){};

      vector(initializer_list<T> init): capacity_(init.size()),size_(init.size())
      data_(*init.size())  {};

      size_t capacity(): return capacity_ {};
      size_t size(): return size_ {};


  };

};


#endif
