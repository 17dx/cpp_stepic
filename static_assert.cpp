#include <vector>
#include <string>

template <class T>
void f(T t){
    static_assert( std::is_arithmetic<T>::value || 
               (std::is_pointer<T>::value && 
                std::is_class<typename std::remove_pointer<T>::type>::value), 
                "T can not be used here" );
                
}




int main(){
    {
        int  a;
        f(a); 
    }     
     
    {
        int * a;
        f(a); 
    }
    
    {
        std::vector<int> a;
        f(a); 
    }
    
    {
        std::vector<int*> a;
        f(a); 
    }
     
    {
        std::string a;
        f(a); 
    } 
    
    {
        std::string * a;
        f(a); 
    }

}
