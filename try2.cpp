#include <iostream>
#include <exception>
#include <stdexcept>


struct MyError : std::runtime_error
{
    MyError(char const* s, bool b) 
        : std::runtime_error(s)
    {
        if (b)
            throw std::logic_error("Logic error");
    }
    ~MyError(){
        std::cerr << "1";
    }
};

void foo( bool b)
{
    throw MyError("My error", b);
}



int main(){
  try{
      foo(true);
  } 
  catch(const MyError& e){
      std::cerr << "eeee";
  }  
  catch(...){
      std::cerr << "xxxx";
  }
  std::cout << "2";
  try{
      foo(false);
  } 
  catch(const MyError& e){
      std::cerr << "eeee";
  } 
  catch(...){
      std::cerr << "yyyy";
  }
   

}
