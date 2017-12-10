#include <iostream>
#include <string>


////*****************************//////
template<class Z, size_t (Z::*)() const =  &Z::size>
size_t get_size( Z const& z){
    return z.size();
}

template<class Z, size_t (Z::*) = & Z::size>
size_t get_size(Z const& z){
    return z.size;
}

/*template<class T>
struct has_Func {
    typedef bool YES; 
    typedef int NO; 
    template<class Z, size_t (Z::*)() const =  &Z::size>
    struct wrapper{ };
    
    template<class C>
    static YES funcExist(wrapper<C>*) ;
    
    template<class C>
    static NO funcExist(...);
    
    static const bool value = sizeof(YES) == sizeof(funcExist<T> (0));
};
     

template<class T, bool FuncExist>
struct get_impl{
    static  size_t get( T& x){
        return x.size();
    }
};

template<class T>
struct  get_impl<T, false>{
    static  size_t get( T& x){
        return x.size;
    }
};

template<class T>
size_t get_size( T& x){
    return get_impl<T, has_Func<T>::value >::get(x);
}*/


   
struct Struct 
{ 
    size_t size;  
};    
int main() {

    std::string s{"Hello"};
    size_t s_size = get_size(s);   // 5, вызывается метод size()

    Struct x{10};
    size_t x_size = get_size(x);  // 10, читается поле size
}