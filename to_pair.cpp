#include <tuple>
#include <iostream>

/*template<int item1, int item2, typename T>      
std::pair<typename std::tuple_element<item1, T>::type,
          typename std::tuple_element<item2, T>::type >
 to_pair (T& t ){
    return  std::make_pair(std::get<item1> (t), std::get<item2> (t) ) ;
}*/

template<int item1, int item2, typename T>      
auto to_pair (T& t ) -> decltype( std::make_pair(std::get<item1> (t), std::get<item2> (t) ) ){
    return  std::make_pair(std::get<item1> (t), std::get<item2> (t) ) ;
}


//c++14
/*template<int item1, int item2, typename T>
auto to_pair (T& t ){
    return  std::make_pair(std::get<item1> (t), std::get<item2> (t) ) ;
}*/

int main(){

    auto t = std::make_tuple(0, 3.5, "Hello");
    std::pair<double, char const *> p = to_pair<1,2>(t); 


}
