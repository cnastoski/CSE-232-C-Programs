#ifndef STUDENT
#define STUDENT

#include<initializer_list>
using std::initializer_list;
#include<algorithm>
using std::copy;

namespace student{
  template<typename T>
  class vector{
    private:
      T *data_;
      size_t capacity_ = 10;
      size_t size_ = 0;
    public:
      vector()=default;
      vector(size_t capacity): capacity_(capacity),size_(0),data_(capacity_){};

      vector(initializer_list<T> init): capacity_(init.size()),size_(init.size())
      ,data_(new T[init.size()])  {copy (init.begin(), init.end(), data_);};

      size_t capacity() const {return capacity_;};
      size_t size() const {return size_;};

      void push_back(T val){
          if (capacity_ <= size_){
            T* new_data =new T[2 * capacity_];
            copy(data_, data_ + size_, new_data);
            data_ = new_data;
            delete [] new_data;
            capacity_ = 2 * capacity_;
          }
        };
 

  };

};


#endif
