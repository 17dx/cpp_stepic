#include <iostream>
#include <list>

template<class It>
size_t max_increasing_len(It p, It q)
{
    if ( p == q ) return 0;
    size_t max_len = 1;
    size_t curr_len = 1;
    It b = p++;
    for(;p != q; b = p++){
        if( *p > *(b) ) ++curr_len;
        else curr_len = 1;
        if(max_len < curr_len) max_len = curr_len;
    }
    return max_len;
}

int main(){
    std::list<int> const l1 = {7,8,9,4,5,6,1,2,3,4};
    size_t len1 = max_increasing_len(l1.begin(), l1.end()); // 4, соответствует подотрезку 1,2,3,4 
    std::cout << len1 <<std::endl;
}
