#include <iostream>
#include <algorithm>

template<class T>
struct Array
{
    // все объявленные ниже методы уже реализованы
    explicit Array(size_t size = 0){
        size_ = size;
        data_ = new T [size];
    };
    /*Array(Array const& a);
    Array & operator=(Array const& a);
    ~Array();

    size_t size() const;
    T &         operator[](size_t i);
    T const&    operator[](size_t i) const;*/

    // реализуйте перемещающий конструктор
    Array(Array && a):size_(a.size_),data_(a.data_){
        std::cout<< "mc ";
        a.size_ = 0;
        a.data_ = nullptr;
    }
    
    // реализуйте перемещающий оператор присваивания
    Array & operator=(Array && a){

        std::swap(data_,a.data_);
        std::swap(size_,a.size_);
                
        return *this;
    }
//private:    
    size_t  size_;
    T *     data_;    
};

int main(void) {
   Array<int> array1(10);
   Array<int> array2(std::move(array1));
   std::cout<< (int)array1.data_ ;;
   
   
   

}