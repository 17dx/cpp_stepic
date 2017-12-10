#include <typeinfo>
#include <iostream>

template<class T, typename R>
bool compare ( const T & a, const T & b, 
               R (T::*pm)() const ){
    return  (a.*pm)() < (b.*pm)();
}


int main(){

    std::string s1("Elf");
    std::string s2("Archer");

    // сравнение строк по длине
    bool r1 = compare(s1, s2, &std::string::size); // true
    bool r2 = compare(s1, s1, &std::string::size); // false
   
    std::cout<< r1 << std::endl;
    std::cout<< r2 << std::endl;

}
