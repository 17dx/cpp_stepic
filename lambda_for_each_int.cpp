#include <iostream>

auto square_fun = [](int& x){x = x*x;};

template<class F>
void for_each_int(int * p, int * q, F f)
{
    for ( ; p != q; ++p )
        f(*p);
}

int main(){
    int m[10] = {1,2,3,4,5,6,7,8,9,10};
    for_each_int(m, m + 10, square_fun);
    for(int x: m){
        std::cout<< x << " ";
    }
}
