#include <iostream>
#include <exception>
#include <stdexcept>

#define X   true
#define Y   true

void bar() ;
struct B{
     B() {
      //   throw std::runtime_error("B()");
         }
};
struct A
{
    A() {
      //  throw std::runtime_error("A()"); 
    }

    ~A() 
    {
         try 
         {
             bar();
         } 
         catch (std::exception const & e) 
         {
             //log("~A()", e.what());
         }
    }
    B b;
};

void foo() 
{
    A a;
    if (X)
        throw std::runtime_error("Some message1");
}

void bar() 
{
    if (Y)
        throw std::logic_error("Some message2");
}




int main(){
   foo();

}
