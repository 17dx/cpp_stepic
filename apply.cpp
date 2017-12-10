#include <utility> // для std::move и std::forward
#include <string> 
#include <iostream> 


//Напишите функцию apply, которая принимает некоторую функцию / функциональный объект, а так же аргументы для вызова этого объекта, и вызывает его, используя perfect forwarding.

// реализация функции apply
template<class F, typename ...Arg>
auto apply ( F f, Arg&&... args ) -> decltype(f(std::forward<Arg>(args)...)) 
{
   return f(std::forward<Arg>(args)...);
}


int main(){
    auto fun = [](std::string a, std::string const& b) { return a += b; };

    std::string s("world!");

    // s передаётся по lvalue ссылке,
    // а временный объект по rvalue ссылке 
    s = apply(fun, std::string("Hello, "), s);
    std::cout<< s ;  
}
