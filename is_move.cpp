#include <iostream>
#include <algorithm>

struct String
{
    char const * c;
    String(): c(nullptr){
        
    }
    String(char const * c): c(c){
        
    }
    
    String(const String& s) {
        std::cout<< "c " << s.c << " " ;
    }
    
    String(String&& s) {
        std::cout<< "mc " << s.c << " " ;
    }
    
    ~String() {
    }
    
    String & operator=(String && s){
        std::cout<< "m=" << s.c << " "  ;        
        return *this;
    }
    
};

int main(void) {
    String s1 = String("Hello"); // 1
    
    String s2("world"); // 2

    String s3 = "000";//s1 + ", " + s2 + "!"; // 3

    String s4 = s3; // 4

    s1 = std::move(s4); // 5

    s2 = String(s1); // 6   
}