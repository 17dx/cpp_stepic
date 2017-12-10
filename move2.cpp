#include <iostream>
struct String
{
    int x;
    String(int x):x(x){
    }
    String(String & a){ 
        x = a.x;    
        std::cout<< "c"<< x << " "; 
        ++x;
    }
    
    
    String & operator=(String & a){ 
        
        std::cout<< "="<< x << " " ;
        ++x;        
        return *this;
    }
    
    String(String && a){ 
        x = a.x;     
        std::cout<< "cmove"<< x << " ";
        ++x;        
    }
    
    
    String & operator=(String && a){         
        std::cout<< "=move"<< x << " ";  
        ++x;
        return *this;
    }
};


String & fun1(String & s)
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
    return std::move(s);
}

String fun5(String s)
{
    return std::forward<String>(s);
}

String && fun6(String && s)
{
    return std::move(s);
}

String fun7(String && s)
{
    return s;
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
     s = fun6(106);
     
     std::cout<< "\nfun7 " ; 
     s = fun7(107);
     

}
