#include "header2.h"
#include <iostream>
#include <typeinfo>


int f2(){
    
    Test test;
    std::cout<< test.data << std::endl;
    
    std::cout<< foo() << std::endl;
    std::cout<< bar() << std::endl;
    std::cout<< foobar() << std::endl;
    //std::cout<< std::hex << &foobar << std::endl;

}