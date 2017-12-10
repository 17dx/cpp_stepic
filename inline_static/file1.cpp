#include "header1.h"
#include <iostream>
#include <typeinfo>

int f2();

int main(){

    Test test;
    std::cout<< test.data << std::endl;
    
    std::cout<< foo() << std::endl;
    std::cout<< bar() << std::endl;
    std::cout<< foobar() << std::endl;
     
    f2();
}
