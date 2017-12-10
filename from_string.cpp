#include <iostream>
#include <string>
#include <sstream>
#include <exception>

// описание класса исключения bad_from_string
class bad_from_string: public std::exception{
    public :
        bad_from_string(const char * msg):msg(msg){}
        virtual const char * what() const noexcept {
            return msg;
        }
    private:    
        const char * msg ;
};

// функция from_string
template<class T>
T from_string(std::string const& s)
{
    std::istringstream ss(s);
    T ret;
    ss >> std::noskipws >> ret;
    if ( ss.fail()  ) throw bad_from_string("error convert to arithmetic");
    if (!ss.eof() ) throw bad_from_string("error convert to char");
    return ret;
}



int main(){
   std::string s1("123");
   int    a1 = from_string<int>   (s1); // a1 = 123
   double b1 = from_string<double>(s1); // b1 = 123.0
   std::string c1 = from_string<std::string>(s1); // c1 = "123"

   std::string s2("12.3");
   try{
       int    a2 = from_string<char>  (s2); // исключение
   }
   catch(std::exception const & e){
       std::cerr << "1";
   }
   
   double b2 = from_string<double>(s2); // b2 = 12.3
   std::string c2 = from_string<std::string>(s2); // c2 = "12.3"

   std::string s3("abc");
   try{
       int    a3 = from_string<int>   (s3); // исключение
   }
   catch(std::exception const & e){
       std::cerr << "1";
   }     
   try{
       double b3 = from_string<double>(s3); // исключение
   }
   catch(std::exception const & e){
       std::cerr << "1";
   }
   std::string c3 = from_string<std::string>(s3); // c3 = "abc"

}
