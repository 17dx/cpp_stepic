#include <iostream>

struct String
{
    char const * s;
    String(char const * s): s(s){
        
    }
    ~String(){delete s;}
    explicit operator char const *() const{
        return s;
    };
};

int main(void) {
   String s("Hello");
   delete s;    // 1

   if (s) { }   // 2
   char const * p1 = s;  // 3
   char const * p2 = (char const*)s;  // 4
   char const * p3 = static_cast<char const*>(s);  // 5
   char const * s2 = s + 4;  // 6

}