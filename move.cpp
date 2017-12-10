#include <iostream>
struct String
{
    String(int x){
    }
    String(String & a){
        std::cout<< "c "; 
    }
    
    
    String & operator=(String & a){ 
        std::cout<< "= " ;  
        return *this;
    }
    
    String(String && a){
        std::cout<< "cmove "; 
    }
    
    
    String & operator=(String && a){ 
        std::cout<< "=move " ;  
        return *this;
    }
};


String& fun1(String & s)
{
    return s;
}

String && fun2(String & s)
{
    return std::move(s);
}

String fun3(String & s)
{
    return std::move(s);
}

String fun4(String s)
{
    return s;
}

String fun5(String s)
{
    return std::move(s);
}

String fun6(String s)
{
    return std::forward<String>(s);
}

String && fun7(String && s)
{
    return std::move(s);
}

String fun8(String && s)
{
    return s;
}

String fun9(String s)
{
    return std::move(s);
}
int main(){
     String  s(0);
     
     std::cout<< "\nfun1 " ;  
     s = fun1(s);
     
     std::cout<< "\nfun2 " ; 
     s = fun2(s);
     
     std::cout<< "\nfun3 " ; 
     s = fun3(s);
     
     std::cout<< "\nfun4 " ; 
     s = fun4(s);
     
     std::cout<< "\nfun5 " ; 
     s = fun5(s);
     
     std::cout<< "\nfun6 " ; 
     s = fun6(s);
     
     std::cout<< "\nfun7 " ; 
     s = fun7(7);
     
     std::cout<< "\nfun8 " ; 
     s = fun8(8);
     
     std::cout<< "\nfun9 " ; 
     s = fun9(s);
}
