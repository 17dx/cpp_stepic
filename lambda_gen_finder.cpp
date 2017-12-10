#include <iostream>

auto gen_finder = [](int * begin, int * end){
    return [=](int x)  {
        for(int * curr = begin; curr != end; ++curr )
           if ( x == *curr) return true;
        return false;
    };
};

template<class F>
bool find_if(int * p, int * q, F f)
{
    for ( ; p != q; ++p )
        if (f(*p))
            return true;
    return false;
}

int main(){
    int primes[5] = {2,3,5,7,11};

    int m[10] = {0,0,1,1,4,6,7,8,9,10};

    // has_primes будет истиной, т.к. в m есть число 7
    bool has_primes = find_if(m, m + 10, gen_finder(primes, primes + 3));
    std::cout<< has_primes;
}
