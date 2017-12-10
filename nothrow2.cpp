#include <iostream>
#include <utility>
#include <type_traits>
#include <string>

#include <utility> // std::declval

struct X{
    //X()  = delete;
    X() noexcept {
       
    }; 
    //X(const X& x)  = delete;  //default
     X(const X& x) noexcept{
       
    };  
     
   // X(X&& x) = delete;
    X(X&& x) noexcept {
        
    } 
    
    // X & operator=(const X & x) = delete;    
       X & operator=(const X & x) noexcept {             
        return *this;
    }  
    
    // X & operator=(X && x) = delete;
      X & operator=(X && x) noexcept{             
        return *this;
    }  
    
    X & operator+(const X & x) {             
        return *this;
    }
    
    X & operator+(X && x) noexcept{             
        return *this;
    }
};

// внутри do_math объекты типа T
// - копируются
// - присваиваются
// - складываются оператором +
template<class T>
void do_math() noexcept( ( !std::is_default_constructible<T>::value ||
                            std::is_nothrow_default_constructible<T>::value 
                         ) &&
                         ( !std::is_copy_constructible<T>::value ||
                            std::is_nothrow_copy_constructible<T>::value 
                         ) &&
                         ( !std::is_copy_assignable<T>::value ||
                           std::is_nothrow_copy_assignable<T>::value
                         ) &&
                         ( !std::is_move_constructible<T>::value ||
                           std::is_nothrow_move_constructible<T>::value
                         ) &&
                         ( !std::is_move_assignable<T>::value||
                           std::is_nothrow_move_assignable<T>::value
                         ) &&
                         noexcept( std::declval<T>() + std::declval<T>() )  )
{
    // тело функции нужно оставить пустым
}



struct Foo { int n; };
int main() {
    //std::cout << noexcept(do_math<int>()); // true
    //std::cout << noexcept(do_math<std::string>()); // false
    std::cout << noexcept(do_math<X>()); // false
    
 
   /* std::cout << std::boolalpha 
              << std::is_copy_constructible<X>::value  << '\n' 
              << std::is_nothrow_copy_constructible<X>::value  << '\n' 
              << std::is_nothrow_destructible<X>::value << '\n' 
              << std::is_nothrow_constructible<X, X&>::value << '\n' 
              << std::is_nothrow_assignable<X&, X>::value << '\n' 
              << std::is_nothrow_assignable<X&&, X>::value << '\n' 
              << std::is_nothrow_assignable<X&&, X&>::value << '\n' 
              << std::is_nothrow_move_constructible<X>::value  << '\n' 
              << std::is_nothrow_move_assignable<X>::value  << '\n' 
              << noexcept( std::declval<X>() + std::declval<X>()) << '\n' 
              << (!std::is_copy_constructible<X>::value ||
                          std::is_nothrow_copy_constructible<X>::value 
                         ) << '\n';*/
   
}