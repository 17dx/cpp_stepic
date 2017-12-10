#include <vector>
#include <iostream>

#include <algorithm>

template<class FwdIt>
FwdIt remove_nth(FwdIt p, FwdIt q, size_t n)
{
    if (p == q) return q;
    FwdIt back = p++; 
    for (;p != q; back = p++){
        if (n == 0){
            std::swap(*back, *p);
        }else{
            --n;
        }
    }  
    if (n == 0) return back;
    return q;
}

void f(int i){
    std::vector<int> v = {0,1,2};
    v.erase(remove_nth(v.begin(), v.end(), i), v.end());
    for(int x: v){
        std::cout << x << " ";
    }
}

int main(){
    for(int i=0; i <= 3; ++i){
        f(i);
        std::cout << std::endl;
    }
}
